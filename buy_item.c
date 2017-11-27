//CN
//File that will be called when the user steps on a tile with a useful item and attempts to buy it

#include "main.h"


int main()
{
	Player player;  			// Player state read in from game_state.txt
	Map map;			        // Map state read in from game_state.txt
	s_cgi* cgi;         			// used for retrieving QUERY_STRING arguments
	FILE* game_map_fp;  			// file pointer to game state text file
	FILE* fp2; 			
	char item[100]; 			 // Name of the item
	char* json_output = NULL;  		// JSON output
	int noEnergy = 0;
	
	initialize_player(&player);		
	read_file(&player, &map, game_map_fp, 1);        // Read in player and map data
	cgi = cgiInit();			
	strcpy(item, cgiGetValue(cgi, "item"));       // Obtain the item


	//If the item is a hatchet then decrement the right amount of money and add item to user inventory if there is room	
	if(strcmp(item, "Hatchet") == 0)
	{
		//for loop to check if there is an empty spot in the users inventory
		//if there is then decrement money, add item to inventory, and replace content of that tile to None
		//so the player may not purchase it again
		for(int i = 0; i < 10; ++i)
		{
			if(strcmp(player.inventory[i], "None") == 0)
			{
				player.money -= 50;
				strcpy(player.inventory[i], "Hatchet");
				strcpy(map.tiles[player.x][player.y].content, "None");
				i = 10;
			}
		}
	}

	// JSON output
	json_output = add_name_value_pair(json_output, "energy", &player.energy, INTEGER);
	json_output = add_name_value_pair(json_output, "noEnergy", &noEnergy, INTEGER);
	json_output = add_name_value_pair(json_output, "Xcoor", &player.x, INTEGER);
	json_output = add_name_value_pair(json_output, "Ycoor", &player.y, INTEGER);
	json_output = add_name_value_pair(json_output, "money", &player.money, INTEGER);
	json_output = add_name_value_pair(json_output, "mapSize", &map.size, INTEGER);

	
	//what does this do?
	char item_name[] = "Aitem"; 
	for(int i = 0; i < 10; ++i){
		json_output = add_name_value_pair(json_output, item_name, player.inventory[i], STRING);
		++item_name[0];
	}

	// Print data to front end (necessary since some purchases will update the player's vision.)
	printf("Content-Type: text/html;charset=us-ascii\n\n");
	printf("%s;", json_output);
	write_html(&player, &map);              

	write_file(&player, &map, game_map_fp); // Write map/player data to game state file 
	free_memory(&player, &map);             // free the player and map memory
	free(json_output);

	return 0;
}


/*
void initialize_player(Player *player)
{
	int i;

	player->x = 0;
	player->y = 0;
	player->energy = 0;
	player->money = 0;
	player->visibility = 1;
	for(i = 0; i < 10; i++) {
		player->inventory[i] = malloc(5 * sizeof(char));
		strcpy(player->inventory[i], "None");
	}
}

void free_memory(Player *player, Map *map)
{
	int i, j;

	// Free all dynamic memory of the map
	for(i = 0; i < map->size; i++) {
		for(j = 0; j < map->size; j++) {
			if(map->tiles[i][j].content) {
				free(map->tiles[i][j].content);
			}
			map->tiles[i][j].content = NULL;
		}
		if(map->tiles[i]) {
			free(map->tiles[i]);
		}
		map->tiles[i] = NULL;
	}
	if(map->tiles) {
		free(map->tiles);
	}
	map->tiles = NULL;

	// Free all dynamic memory for the player
	for(i = 0; i < 10; i++) {
		if(player->inventory[i]) {
			free(player->inventory[i]);
		}
	}
}
*/
