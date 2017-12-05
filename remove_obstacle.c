// This file is meant to be called when a player hits an obstacle
// and chooses to remove it using one of thier inventory items
// Contributors: Dumitru Mitaru-Berceanu, 

#include "main.h"

#define MAX_STR 100  // Size of static strings 

int main()
{
	Player player;  					 // Player state read in from game_state.txt
	Map map;					  			 // Map state read in from game_state.txt
	s_cgi* cgi;         			 // used for retrieving QUERY_STRING arguments
	FILE* game_map_fp;  			 // file pointer to game state text file
	FILE* fp2; 								 // I have no idea what this is used for but I need an empty one for resetState call
	char tool[MAX_STR]; 			 // Name of the tool the player chose to use. "None" if not chosen
	int tool_index; 				   // index of tool that the player has chosen, -1 if not chosen
	char* json_output = NULL;  // JSON output
	int noEnergy = 0;
	

	
	initialize_player(&player);									  // Init the player 
	read_file(&player, &map, game_map_fp, 1);        // Read in player and map data
	cgi = cgiInit();															// Init cgi
	strcpy(tool, cgiGetValue(cgi, "tool"));  			// Get the tool name the player chose

  // Remove the obstacle with the chosen tool
	tool_index = get_tool_index(tool);
	remove_obstacle(&player, &map, tool_index);

	noEnergy = (player.energy <= 0) ? 1 : 0;

	// If player is dead then reset
	if(noEnergy == 1){
		resetstate(game_map_fp,fp2); 
		free_memory(&player, &map); 
		read_file(&player, &map, game_map_fp, 1);
	}

	// Create JSON blob
	json_output = add_name_value_pair(json_output, "energy", &player.energy, INTEGER);
	json_output = add_name_value_pair(json_output, "noEnergy", &noEnergy, INTEGER);
	json_output = add_name_value_pair(json_output, "Xcoor", &player.x, INTEGER);
	json_output = add_name_value_pair(json_output, "Ycoor", &player.y, INTEGER);
	json_output = add_name_value_pair(json_output, "money", &player.money, INTEGER);
	json_output = add_name_value_pair(json_output, "mapSize", &map.size, INTEGER);

	// instead of appending the inventory as an array (which could be done but I was a bit lazy)
	// just add each item as a new name-value pair. This is probably ok since our inventory is
	// going to stay fixed at 10 items. 
	char item_name[] = "Aitem"; 
	for(int i = 0; i < 10; ++i){
		json_output = add_name_value_pair(json_output, item_name, player.inventory[i], STRING);
		++item_name[0];
	}

	// Print data to front end
	printf("Content-Type: text/html;charset=us-ascii\n\n");
	printf("%s;", json_output);
	write_html(&player, &map);              

	write_file(&player, &map, game_map_fp); // Write map/player data to game state file 
	free_memory(&player, &map);             // free the player and map memory
	free(json_output);

	return 0;
}

