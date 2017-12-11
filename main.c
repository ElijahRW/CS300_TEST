/* This file contains the frame for the backend of Frupal
// Contributors: (All group memebers) Jacob Collins, Caameron Nakasone, Sunanth Sakthivel, Elijah Rich-Wimmer, Dumitru Mitaru-Berceanu, Brady Testa, Weiwei Chen
*/
/*
--Name: GROUP A
--Class: CS 300
--Assignment: Frupal Project
--File: main.c
--Description: This function handles IO from the game html page when the player makes a move or displays a map.
*/

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
	int i, j, len, diamond_found, noEnergy, chest, map_selection=1, clue;
	char* json_output = NULL;
	char message[200];
	int obstacle_index;
	char obstacle[100];
	int energymessage;
	char useful_item[100];
	diamond_found = 0;
	noEnergy = 0;
	int northaway, eastaway, southaway, westaway;
	
	
	//EPRW Purchase IO
	char purchase_request = ' ';

	//Default message
	strcpy(message, "WALKING...");  
	//Default obstacle
	strcpy(obstacle, "None");

	//Initializing cgi parser
	cgi = cgiInit();

	strcpy(buffer,cgiGetValue(cgi,"query"));
	len = strlen(buffer) + 1;

	// [JMC] - 26NOV2017
	// The following is for loading a specific map 
	// If query is for loading, figure out the map selection
	// else, do the normal allocation...
	if(buffer[0] == 'L' && buffer[1] == 'O' && buffer[2] == 'A' && buffer[3] =='D') { 
		// buffer[4] is skipped because it is the '-' in the query "LOAD-##"
		map_selection = (buffer[5]-'0')*10 + (buffer[6]-'0');
		query = malloc(5 * sizeof(char));
		strcpy(query, "LOAD");
	}
	else { 
		query = malloc(len * sizeof(char));
		strcpy(query, buffer);
	}
	// [/JMC]

	//DEFAULT HTML formating output
	printf("Content-Type: text/html;charset=us-ascii\n\n");

	//initializes player structure to default values
	initialize_player(&player);
	//reads player & map information for designated file
	read_file(&player, &map, fp, map_selection);
	
	//If player has called load function, then 
	if(strcmp(query, "LOAD") == 0) {
		sprintf(message, "Welcome back to Frupal");
	}
	else
	{
		query[1]='\0';//this is an input (quickfix) that the querry string creates
		//IF QUERY INPUT is equivalent to Direction (Attempt to move the player)
		if(strcmp(query, "N") == 0 || strcmp(query, "S") == 0 || strcmp(query, "E") == 0 || strcmp(query, "W") == 0) {
			//Sunanth Sakthivel
			//logic to check for bog interactions as well as chest interactions (also includes instance of chest and bog interactions). 
			energymessage = move_player(query, &player, &map);
			if(energymessage == 2 || energymessage == 5 || energymessage == 6)//Bog Check   
				sprintf(message, "You've just run into a bog, lost extra energy point");
			if(energymessage == 3 || energymessage == 5)
				chest = 1;	//run into type 1 chest.
			if(energymessage == 4 || energymessage == 6)
			{
				chest = 2;	//run into type 2 chest. 
			}
			//-- --
		}

	}


	//CN
	//Check if the player has stepped on a useful item. If they have then the name of that item will be passed as a JSON
	//to the html file, where a function will then be called that will allow the user to purchase the item
	check_item(&player, &map, useful_item);	

	//CN,WW,SS
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
	if((obstacle_index = get_obstacle_index(&player, &map)) != -1){
		strcpy(obstacle, obstacle_names[obstacle_index]);
	}

	//SS
	//Check for the appropriate clue and set clue variable to appropriate type of clue. 
	//Retrieve information about diamond location from the check for clue function. 
	clue = check_for_clue(&player, &map, &northaway, &eastaway, &southaway, &westaway); 
	if(!clue || player.energy < 1)
	{
		clue = 0;	//set clue to 0 if no clue found. 
	}

	//CN	
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
	json_output = add_name_value_pair(json_output, "obstacle", obstacle, STRING);
	json_output = add_name_value_pair(json_output, "chest", &chest, INTEGER);
	json_output = add_name_value_pair(json_output, "clue", &clue, INTEGER);
	json_output = add_name_value_pair(json_output, "useful_item", &useful_item, STRING);
	json_output = add_name_value_pair(json_output, "northaway", &northaway, INTEGER);
	json_output = add_name_value_pair(json_output, "eastaway", &eastaway, INTEGER);
	json_output = add_name_value_pair(json_output, "southaway", &southaway, INTEGER);
	json_output = add_name_value_pair(json_output, "westaway", &westaway, INTEGER);





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
