
/*   CN
This file will be called when we want to add an item to the players inventory
*/

#include "../main.h"


/*

*/
int purchaseItem(Player * player, const char * item, int price)
{
	int result = 0;
	if(player->money >= price && add_item(player, item)!=0)
	{
			(player->money) -= price;
			result = 1;
	}
	return result;
}


/*
--Purpose: Adds an item to the first inventory slot available
--Input: Player structure and the character array
--Output: Returns 1 if insertion successful returns 0 otherwise
*/
int add_item(Player * player, const char * item)
{
	char ** inventory = player->inventory;
	int result =0;
	for (int i = 0; i < 10; ++i)
		{
			//If there is an empty spot in the users inventory copy the item over
			if(strcmp(player->inventory[i], "None") == 0)
			{
				strcpy(inventory[i], item);
				i = 10;
				result = 1;
			}
		}
	return result;
}


void check_item(Player * player, Map * map, char * useful_item)
{
	char tile_item[100];
	

	//Copy over the content of the tile to a temporary variable. Then compare that to all the items
	// which could be there. If one is found then have useful_item variable passed in be the name
	//of the item so that it can be purchased
	strcpy(tile_item, map->tiles[player->x][player->y].content);

	if(strcmp(tile_item, "Hatchet") == 0)
	{

		strcpy(useful_item, "Hatchet");
	}
	else if(strcmp(tile_item, "Boat") == 0)
	{

		strcpy(useful_item, "Boat");
	}
	else
	{
		strcpy(useful_item, "None");
		return;
	}


}

//{"hip","hip"}
// hip hip array!

