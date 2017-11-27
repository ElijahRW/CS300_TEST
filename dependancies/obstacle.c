#include "../main.h"


#define NUM_OBS 3 	// Number of obstacles in obstacle arrays
#define NUM_TOOLS 8 // Number of tools in tools arrays

// Define obstacle names and energy values
const char* obstacle_names[] = {
	[TREE]    "Tree", 
	[BOULDER] "Boulder",
	[BUSH]	  "Bush"
};
const int obstacle_energies[] = {
	[TREE]     10, 
	[BOULDER]  16,
	[BUSH]	   4
};

// Define tool names and energy values
const char* tool_names[] = {
[HATCHET]    "Hatchet",
[AXE]        "Axe",
[CHAINSAW]   "Chainsaw",
[CHISEL]     "Chisel",
[SLEDGE]     "Sledge",
[JACKHAMMER] "Jackhammer",
[MACHETE]    "Machete",
[SHEARS]     "Shears"
};
const int tool_energies[] = {
[HATCHET]    8,
[AXE]        6,
[CHAINSAW]   2,
[CHISEL]     15,
[SLEDGE]     12,
[JACKHAMMER] 4,
[MACHETE]    2,
[SHEARS]     2
};

// This array defines which obstacle each tool is used to remove.
// The index of each element represents the tool and 
// the value represents the obstacle index.
// This is mainly used to check that the right 
// tool is being used to remove the right obstacle!
const int tool_purpose[] = {
[HATCHET] 	 TREE,
[AXE]     	 TREE,
[CHAINSAW]   TREE,
[CHISEL]     BOULDER,
[SLEDGE]     BOULDER,
[JACKHAMMER] BOULDER,
[MACHETE] 	 BUSH,
[SHEARS] 		 BUSH
};

// This function will remove the obstacle that the player has encountered
// and will decrement the players energy based on which tool they chose to use
void remove_obstacle(Player* player, Map* map, int tool_index){
	
	int energy_used; 																			// energy that the player will loose in removal 
	int obstacle_index = get_obstacle_index(player, map); // index of obstacle that the player stands on

  // if the right tool was chosen to remove the obstacle
	if(check_obstacle_tool_match(tool_index, obstacle_index) == 1)
		energy_used = tool_energies[tool_index];
	else // if the wrong tool was chosen
		energy_used = obstacle_energies[obstacle_index]; 
 
	player->energy -= energy_used;
	remove_obstacle_from_map(player, map);
	remove_tool_from_inventory(player, tool_index);
	
}

// Since each tool can only remove one obstacle 
// i.e. Hatchet can remove a tree for 8 energy pointer but not a boulder,
// then check to see if the tool chosen matches the obstace to remove.
// If they match return 1, otherwise 0
int check_obstacle_tool_match(int tool_index, int obstacle_index){

  // if no tool or no obstacle is selected 
  if(tool_index == -1 || obstacle_index == -1)
		return 0;
	// if the tool and obstacle match
	if(tool_purpose[tool_index] == obstacle_index)
		return 1;

  // if the tool and obstacle DO NOT match
	return 0;
}

// This function will return the index of the obstacle
// that the player has encountered. The index is used to 
// index into the global obstacle_name and obstacle_energy arrays
// it will return -1 if no obstacle is found
int get_obstacle_index(Player* player, Map* map){
	
	// the content of the current tile the player is on.
	char* tile_content = map->tiles[player->x][player->y].content;
	int obstacle_index = -1; 

<<<<<<< HEAD
	for(int i = 0; i < NUM_OBS && obstacle_index != 1; ++i){
		if(strcmp(tile_content, obstacle_names[i]) == 0)
			obstacle_index = i;
=======
  // if the player should already be dead then just return (WHY are we doing this?)
	if(player->energy < 0)
		return obstacle_index;

	if(strcmp(*tile_content, obstacle_name[TREE]) == 0)
		obstacle_index = TREE;	
	else if(strcmp(*tile_content, obstacle_name[BOULDER]) == 0)
		obstacle_index = BOULDER;
	else if(strcmp(*tile_content, obstacle_name[BUSH]) == 0)
		obstacle_index = BUSH;

	// if obstacle is found, decrement player energy
	// and remove obstacle from map
	if(obstacle_index != -1){
		player->energy -= obstacle_energy[obstacle_index];
		free(*tile_content);
		*tile_content = (char*)malloc(sizeof(char) * strlen("None") + 1);
		strcpy(*tile_content, "None");
>>>>>>> master
	}

  return obstacle_index;	
}

<<<<<<< HEAD
// This function will return the index of the tool
// that the player has chosen. The index is used to index
// into the tool_name and tool_energy arrays. It will return
// -1 if no tool is found
int get_tool_index(char* tool_name){
	
	int tool_index = -1;

	for(int i = 0; i < NUM_TOOLS && i != -1; ++i){
		if(strcmp(tool_name, tool_names[i]) == 0)
			tool_index = i;
	}

	return tool_index;
}

// This function removes the obstacle at the players
// location from the map
void remove_obstacle_from_map(Player* player, Map* map){

  // Needs to be char** so that I can remove the obstacle
	char** tile_content = &(map->tiles[player->x][player->y].content);

	// Remove obstacle from map
	free(*tile_content);
	*tile_content = malloc(sizeof(char) * strlen("None") + 1);
	sprintf(*tile_content, "None");
}

// This function will remove the tool indicated by tool_index
// From the players inventory
void remove_tool_from_inventory(Player* player, int tool_index){

	// if not tool was used, then just return
	if(tool_index == -1)
		return;

	// search for the tool that was used
	for(int i = 0; i < 10; ++i){
		// if the tool name was found in the players inventory
		if(strcmp(tool_names[tool_index], player->inventory[i]) == 0){
			free(player->inventory[i]);
			player->inventory[i] = malloc(sizeof(char) * strlen("None") + 1);
			strcpy(player->inventory[i], "None");
		}
	}
}
=======

>>>>>>> master
