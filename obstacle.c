#include "main.h"


// Define obstacle names and enery values
const char* obstacle_name[] = {
	[TREE]    "Tree", 
	[BOULDER] "Boulder",
	[BUSH]	  "Bush",
};

const int obstacle_energy[] = {
	[TREE]     10, 
	[BOULDER]  16,
	[BUSH]	   4,
};

// Function will check the current if the player is 
// in a tile that has an obstacle. It found, it will decrement
// the players energy (can go negative), remove the obstacle
// from the map and return the index of the obstacle in the
// obstacle_name and obstacle_energy arrays defined in main.h
int check_for_obstacle(Player* player, Map* map){
	
	// the content of the current tile the player is on
	char** tile_content = &(map->tiles[player->x][player->y].content);
  // the index into the global obstacle arrays in obstacle.h, initialize to obstacle not found
	int obstacle_index = -1; 

  // if the player should already be dead then just return
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
	}

  return obstacle_index;	
}
