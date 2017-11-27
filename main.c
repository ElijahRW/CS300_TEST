#include "main.h"

int main()
{
	//variable declarations
	char * query;
	char buffer[100];
	s_cgi *cgi;
	FILE *fp;
	FILE *fp2;
	Player player;
	Map map;
	int i, j, len, diamond_found, noEnergy, chest, map_selection;
	char* json_output = NULL;
	char message[200];
	int obstacle_index;
	int energymessage;
	diamond_found = 0;
	noEnergy = 0;
	map_selection = 1;
	
	
	//EPRW Purchase IO
	char purchase_request = ' ';

	//Default message
	sprintf(message, "WALKING...");  

	//Initializing cgi parser
	cgi = cgiInit();

	strcpy(buffer,cgiGetValue(cgi,"query"));
	len = strlen(buffer) + 1;

	// [JMC] - 26NOV2017
	// The following is for loading a specific map 
	// This if statement isn't the prettiest since it checks char by char
	// but it was easy to implement. 
	if(buffer[0] == 'L' && buffer[1] == 'O' && buffer[2] == 'A' && buffer[3] =='D') { 
		// If query is for loading...
		// buffer[4] is skipped because it is the '-' in the query "LOAD-##"
		map_selection = (buffer[5]-'0')*10 + (buffer[6]-'0');
		query = malloc(5 * sizeof(char));
		strcpy(query, "LOAD");
	}
	else { 
		// else, do the normal allocation...
		query = malloc(len * sizeof(char));
		strcpy(query, buffer);
	}
	// [/JMC]

	printf("Content-Type: text/html;charset=us-ascii\n\n");

	initialize_player(&player);
	read_file(&player, &map, fp, map_selection);
	
	if(strcmp(query, "LOAD") == 0) {
		sprintf(message, "Welcome back to Frupal");
	}
	else
	{
		//IF QUERY INPUT is equivalent to Direction (Attempt to move the player)
		if(strcmp(query, "N") == 0 || strcmp(query, "S") == 0 || strcmp(query, "E") == 0 || strcmp(query, "W") == 0) {
			energymessage = move_player(query, &player, &map);
			if(energymessage == 2 || energymessage == 5 || energymessage ==6)//Bog Check   --CONSIDER MOVING THIS CHECK INTO THE MOVE PLAYER FUNCTION--
				sprintf(message, "You've just run into a bog, lost extra energy point");
			if(energymessage == 3 || energymessage == 5)
				chest = 1;
			if(energymessage == 4 || energymessage == 6)
				chest = 2;	
			//-- --
			//We have to check if the player is standing on a purchase location
			// Adjust the char purchase_request and the char[] message in order to prompt user input (y/n)
			//if purchase_request == ' ', then no output is given
		}
		else
		{
			//
			if(strcmp(query, "C") == 0 || strcmp(query, "E") == 0 || strcmp(query, "B") == 0 || strcmp(query, "W") == 0)
			{
				purchaseItem(&player, query[0]);
			}
		}
	}


	
	
	//If statement to check coordinates that the player has moved into and the coordiantes of the diamonds
	//if(map.tiles[diamondx][diamondy].x == player.x && map.tiles[diamondx][diamondy].y == player.y)
	if(strcmp(map.tiles[player.x][player.y].content, "DIAMOND") == 0)
	{
		resetstate(fp,fp2);
		free_memory(&player, &map); // free memory before reading info into the structs
		read_file(&player, &map, fp, map_selection);
		diamond_found = 1; // diamond has been found

	}

	// Check if the player has encountered an obstacle and decrement the energy appropriatley
	if((obstacle_index = check_for_obstacle(&player, &map)) != -1){
		sprintf(message, "You've hit a %s and lost %d energy points removing it", obstacle_name[obstacle_index], obstacle_energy[obstacle_index]);
	}
	
	//ENERGY CHECK
	//Code to check whether the player has used up all of their energy. The code will alert the player that the game is over
	//when the player is at 0 energy and tries to move again, not when it immediately hits 0.
	if(player.energy < 1)
	{
		resetstate(fp,fp2);
		free_memory(&player, &map);//free memory
		read_file(&player, &map, fp, map_selection);	
		noEnergy = 1;  //Player has run out of energy
	}

	// Append all data to json output
	json_output = add_name_value_pair(json_output, "diamondFound", &diamond_found, INTEGER);
	json_output = add_name_value_pair(json_output, "Xcoor", &player.x, INTEGER);
	json_output = add_name_value_pair(json_output, "Ycoor", &player.y, INTEGER);
	json_output = add_name_value_pair(json_output, "energy", &player.energy, INTEGER);
	json_output = add_name_value_pair(json_output, "money", &player.money, INTEGER);
	json_output = add_name_value_pair(json_output, "noEnergy", &noEnergy, INTEGER);
	json_output = add_name_value_pair(json_output, "mapSize", &map.size, INTEGER);
	json_output = add_name_value_pair(json_output, "message", message, STRING);
	json_output = add_name_value_pair(json_output, "chest", &chest, INTEGER);

	// instead of appending the inventory as an array (which could be done but I was a bit lazy)
	// just add each item as a new name-value pair. This is probably ok since our inventory is
	// going to stay fixed at 10 items. 
	char item_name[] = "Aitem"; 
	for(int i = 0; i < 10; ++i){
		json_output = add_name_value_pair(json_output, item_name, player.inventory[i], STRING);
		++item_name[0];
	}

	// print out the json and a ';' to separate the json from
	// the map that will be printed later
	printf("%s;", json_output);
	free(json_output);
	

	//Prints map to Table
	write_html(&player, &map);


	// END - PRINT ALL INFO FOR HTML TO PARSE
	write_file(&player, &map, fp); // write all info to the game state
	
	free(query); // free memory for the query string
	free_memory(&player, &map); // free the player and map memory

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
