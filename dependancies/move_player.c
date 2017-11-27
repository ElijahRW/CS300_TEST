#include "../main.h"
#define BOG 4
#define WALL 3 
#define WATER 2

/*
--NOTE FOR CONVENTION:
----x is left/right (east west)
----y is up/down (north south)
*/

int move_player(char *query, Player *player, Map *map)
{
	int max = map->size - 1;
	int energymessage = 0;

	// Check which coordinaAte to update.
	if(checkPassable(map,player, query) == 0)
{
		if(strcmp(query, "N") == 0) {
			++player->y;
		}
		else if(strcmp(query, "S") == 0) {
			--player->y;
		}
		else if(strcmp(query, "E") == 0) {
			++player->x;
		}
		else if(strcmp(query, "W") == 0) {
			--player->x;
		}

		// Check x bounds
		if(player->x > max) {
			player->x = 0;
		}
		else if(player->x < 0) {
			player->x = max;
		}

		// Check y bounds
		if(player->y > max) {
			player->y = 0;
		}
		else if(player->y < 0) {
			player->y = max;
		}

		// Decrement energy due to movement
		energymessage = decrementenergy(player,map);
		
		// Make the tile visible (Needs to be expanded to show player's vision

		//map->tiles[player->x ][player->y ].visibility = 1;

}
	viewTiles(player, map);
	return energymessage;
}


/*
--Purpose: This function will set to visible all tiles that are within the player's vision
--Input: Player pointer to the main player structure. Map pointer to the map structure.
--Output: the map structure will be updated
*/
int viewTiles(Player *player, Map *map)
{
	int viewRange = player->visibility;
	int map_range = map->size;
	
	for (int i = -viewRange; i <= viewRange; i++)
	{
		for (int j = -viewRange; j<= viewRange; j++)
		{
			if( (player->x)+i >= 0 && (player->y)+j >= 0 && (player->y)+j < map_range && (player->x)+i < map_range)
			{
				map->tiles[player->x + i][player->y + j ].visibility = 1;
			}
		}
	} 
	return 1;	
}


//this function decrements energy of player while also checking for terrain such as bogs and instances of chests and clues. 
//information about the player is updated here and a return code is sent back to main.c that will determine what
//type of message to be displayed in the html. 
int decrementenergy(Player* player, Map* map)
{
	//going to add checks for water and treasure chests here. 
	int flag = 0;
	
	
	//what is this doing here?
	if(strcmp(map->tiles[player->x][player->y].content, "Type1") == 0)
	{
		player->money += 100;
		free(map->tiles[player->x][player->y].content);
		map->tiles[player->x][player->y].content = (char*)malloc(sizeof(char) * strlen("None") + 1);
		strcpy(map->tiles[player->x][player->y].content, "None");
		flag = 3;
	}	
	if(strcmp(map->tiles[player->x][player->y].content, "Type2") == 0)
	{
		player->money = 0;
		free(map->tiles[player->x][player->y].content);
		map->tiles[player->x][player->y].content = (char*)malloc(sizeof(char) * strlen("None") + 1);
		strcpy(map->tiles[player->x][player->y].content, "None");
		flag = 4;
	}
	if(map->tiles[player->x][player->y].terrain == BOG)
	{
		(player->energy) -= 2;
		if(!flag)
			return 2;
		else
			return 2+flag;
	}
	else
	{
		--player->energy;
		if(!flag)
			return 1;
	}
	return flag;
} 


int checkPassable(Map * myMap,Player *myPlayer, char* query) //Only returns true if the terrain is passable.
{
	int x= myPlayer->x;
	int y = myPlayer->y;
	int max = myMap->size -1;
	
	if(strcmp(query, "N") == 0) {
		y++;
	}
	else if(strcmp(query, "S") == 0) {
		y--;
	}
	else if(strcmp(query, "E") == 0) {
		x++;
	}
	else if(strcmp(query, "W") == 0) {
		x--;
	}

	// Check x bounds
	if(x > max) {
		x = 0;
	}
	else if(x < 0) {
		x = max;
	}

	// Check y bounds
	if(y > max) {
		y = 0;
	}
	else if(y < 0) {
		y = max;
	}

	if(myMap->tiles[x][y].terrain == WATER)
{
		--myPlayer->energy;
		return 1;
		
}
	if(myMap->tiles[x][y].terrain == WALL)
{
		--myPlayer->energy;
		return 1;
		
}
	
	else
		return 0;
}
