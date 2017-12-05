// WeiWei
//File that will be called when the user steps on a tile with a useful item and attempts to buy it
//Contributors: Caameron Nakasone

/*
--Name: GROUP A
--Class: CS 300
--Assignment: Frupal Project
--File: buy_item.c
--Description: This function handles IO from the game html page when the player makes a move or displays a map.
*/

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
	read_file(&player, &map, game_map_fp, 1);        // Read in player and map data
	cgi = cgiInit();			
	strcpy(item, cgiGetValue(cgi, "item"));       // Obtain the item


	//--PURCHASE CHECKS!!!--
	//If the item is a matches then decrement the right amount of money and add item to user inventory if there is room
	//This is done in the function call: purchaseItem)
	//purchase result is returned to send the html cga call
	int purchase_result = 0;
	if(strcmp(item, "Energy") == 0)
	{
		if(purchaseItem(&player, item, 1))
			purchase_result = 1;
	}
	else if(strcmp(item, "Hatchet") == 0)
	{
		if(purchaseItem(&player, item, 15))
			purchase_result = 1;
		
	}
	else if(strcmp(item, "Boat") == 0)
	{
		if(purchaseItem(&player, item, 500))
			purchase_result = 1;
	}
	else if(strcmp(item, "Axe") == 0)
	{
		if(purchaseItem(&player, item, 30))
			purchase_result = 1;
	}
	else if(strcmp(item, "Chainsaw") == 0)
	{
		if(purchaseItem(&player, item, 60))
			purchase_result = 1;
	}
	else if(strcmp(item, "Chisel") == 0)
	{
		if(purchaseItem(&player, item, 5))
			purchase_result = 1;
	}
	else if(strcmp(item, "Sledge") == 0)
	{
		if(purchaseItem(&player, item, 25))
			purchase_result = 1;
	}
	else if(strcmp(item, "Jackhammer") == 0)
	{
		if(purchaseItem(&player, item, 100))
			purchase_result = 1;
	}
	else if(strcmp(item, "Machete") == 0)
	{
		if(purchaseItem(&player, item, 25))
			purchase_result = 1;
	}
	else if(strcmp(item, "Shears") == 0)
	{
		if(purchaseItem(&player, item, 35))
			purchase_result = 1;
	}
	else if(strcmp(item, "Binoculars") == 0)
	{
		if(purchaseItem(&player, item, 50))
			purchase_result = 1;
	}
	if(purchase_result)
	{
		strcpy((map.tiles[player.x][player.y]).content, "None");
		sprintf(message, "You have successfully purchased a %s", item);  
	}
	else
	{
		sprintf(message, "You could not purchase a %s", item);  
	}

	// JSON output (Writes to cgi return string)
	json_output = add_name_value_pair(json_output, "energy", &player.energy, INTEGER);
	json_output = add_name_value_pair(json_output, "noEnergy", &noEnergy, INTEGER);
	json_output = add_name_value_pair(json_output, "Xcoor", &player.x, INTEGER);
	json_output = add_name_value_pair(json_output, "Ycoor", &player.y, INTEGER);
	json_output = add_name_value_pair(json_output, "money", &player.money, INTEGER);
	json_output = add_name_value_pair(json_output, "mapSize", &map.size, INTEGER);
	json_output = add_name_value_pair(json_output, "message", message, STRING);

	
	//Output the inventory of the player
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
