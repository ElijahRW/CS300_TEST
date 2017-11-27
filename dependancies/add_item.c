
/*   CN
This file will be called when we want to add an item to the players inventory
*/

#include "../main.h"



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


		/*	
		for (int i = 0; i < 10; ++i)
		{
			//If there is an empty spot in the users inventory copy the item over and get
			//rid of the item on the map
			if(strcmp(player->inventory[i], "None") == 0)
			{
				//strcpy(player->inventory[i], "Hatchet");
				//strcpy(map->tiles[player->x][player->y].content, "None");	
				strcpy(useful_item, "Hatchet");
				i = 10;
			}
		}
		*/
	}
	else
	{
		strcpy(useful_item, "None");
		return;
	}


}

