/*
--Name: GROUP A
--Class: CS 300
--Contributors: Caameron Nakasone, Weiwei, Caameron Nakasone, Brady Testa (Added Binoculars)
--Assignment: Frupal Project
--File: add_item.c
--Description: --This file will be called when we want to add an item to the players inventory
				--if the item is a powerbar, we don't add it into the player's inventory
*/


#include "../main.h"



//Decrements the amount of whiffles for the specified item but only does so if the player has enough money
//If they do not have enough money then the function returns a 0, if they have enough it will return a 1
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
--Written by Elijah Rich-Wimmer: edited by Weiwei
--Purpose: Adds an item to the first inventory slot available
--Input: Player structure and the character array
--Output: Returns 1 if insertion successful returns 0 otherwise
*/
int add_item(Player * player, const char * item)
{
	char ** inventory = player->inventory;
	int result =0;
	//If it is a powerbar, we decrease energy by 20, we don't add it into inventory (Weiwei)
	if (strcmp(item, "Energy") == 0)
					{
						(player->energy) += 20;
						result = 1;
					}
	else
	{
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
	}
	return result;
}

//Written by (Cameron?)
//Checks if the item that the player has stepped on is a useful item that is purchasable. If it is the function
//will place that item's name in usful_item that will start the purchasing process, if not then "None" will be
//placed in useful_item, which will make sure the purchasing process does not start.
void check_item(Player * player, Map * map, char * useful_item)
{
	char tile_item[100];
	

	//Copy over the content of the tile to a temporary variable. Then compare that to all the items
	// which could be there. If one is found then have useful_item variable passed in be the name
	//of the item so that it can be purchased
	strcpy(tile_item, map->tiles[player->x][player->y].content);

	if(strcmp(tile_item, "Energy") == 0)
	{
		strcpy(useful_item, "Energy");
	}
	else if(strcmp(tile_item, "Hatchet") == 0)
	{

		strcpy(useful_item, "Hatchet");
	}
	else if(strcmp(tile_item, "Boat") == 0)
	{

		strcpy(useful_item, "Boat");
	}
	else if(strcmp(tile_item, "Axe") == 0)
	{

		strcpy(useful_item, "Axe");
	}
	else if(strcmp(tile_item, "Chainsaw") == 0)
	{

		strcpy(useful_item, "Chainsaw");
	}
	else if(strcmp(tile_item, "Chisel") == 0)
	{

		strcpy(useful_item, "Chisel");
	}
	else if(strcmp(tile_item, "Sledge") == 0)
	{

		strcpy(useful_item, "Sledge");
	}
	else if(strcmp(tile_item, "Jackhammer") == 0)
	{

		strcpy(useful_item, "Jackhammer");
	}
	else if(strcmp(tile_item, "Machete") == 0)
	{

		strcpy(useful_item, "Machete");
	}
	else if(strcmp(tile_item, "Shears") == 0)
	{

		strcpy(useful_item, "Shears");
	}
	else if(strcmp(tile_item, "Binoculars") == 0)
	{
		strcpy(useful_item, "Binoculars");
	}
	
	else
	{
		strcpy(useful_item, "None");
		return;
	}


}

//{"hip","hip"}
// hip hip array!

