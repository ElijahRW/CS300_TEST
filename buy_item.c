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
	char message[200];

	
	initialize_player(&player);		
	read_file(&player, &map, game_map_fp);        // Read in player and map data
	cgi = cgiInit();			
	strcpy(item, cgiGetValue(cgi, "item"));       // Obtain the item


	//--PURCHASE CHECKS!!!--
	//If the item is a matches then decrement the right amount of money and add item to user inventory if there is room	
	int purchase_result = 0;
	if(strcmp(item, "Hatchet") == 0)
	{
		if(purchaseItem(&player, item, 50))
			purchase_result = 1;
		
	}
	else if(strcmp(item, "Boat") == 0)
	{
		if(purchaseItem(&player, item, 500))
			purchase_result = 1;
	}
	
	if(purchase_result)
	{
		sprintf(message, "You have successfully purchased a %s", item);  
	}
	else
	{
		sprintf(message, "You could not purchase a %s", item);  
	}

	// JSON output
	json_output = add_name_value_pair(json_output, "energy", &player.energy, INTEGER);
	json_output = add_name_value_pair(json_output, "noEnergy", &noEnergy, INTEGER);
	json_output = add_name_value_pair(json_output, "Xcoor", &player.x, INTEGER);
	json_output = add_name_value_pair(json_output, "Ycoor", &player.y, INTEGER);
	json_output = add_name_value_pair(json_output, "money", &player.money, INTEGER);
	json_output = add_name_value_pair(json_output, "mapSize", &map.size, INTEGER);
	json_output = add_name_value_pair(json_output, "message", message, STRING);

	
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
