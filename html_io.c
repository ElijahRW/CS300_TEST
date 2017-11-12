#include "main.h"



int write_html(Player *player, Map *map)
{
	
	viewTiles(player, map);
	int playerx = player->x;
	int playery = player->y;
	printf("<table cellpadding='0'>");
	int size = map->size;
	for(int y = size-1; y >= 0; --y)//awkward initialization (Will consider reworking
	{
		printf("<tr>");
		for(int x = 0; x<size; ++x)//awkward initialization (Will consider reworking
		{
			if(playerx==x && playery==y)
			{
				printf("<th><img height='25' width='25' src='assets/hero.jpg' align='middle'></img></th>");
			}
			else
			{
				printf("<th>");
				write_tile(&((map->tiles)[x][y]));
				printf("</th>");
			}
		}
		printf("</tr>");
	}
	printf("</table>");
	return 1;
}
void write_tile(Tile *tile)
{
	//Immage references:(0=meadow/grass, 1=forest, 2=water, 3=wall, 4=bog, 5=swamp)
	//Additionally, content such as trees should be taken into account: 
	const char * formatting = "height='30'";
	if(tile->visibility == 0)
	{
		printf("<img %s src='assets/fog.jpg' align='middle'></img>", formatting);
	}
	else
	{
		int terrain = tile->terrain;
		switch(terrain)
		{
			case 0:
				printf("<img %s src='assets/grass.jpg'></img>", formatting);//implementation of specific content (Such as chests) may be handled here...
				break;
			case 1:
				printf("<img %s src='assets/forest.jpg'></img>", formatting);//implementation of specific content (Such as chests) may be handled here...
				break;
			case 2:
				printf("<img %s src='assets/water.jpg'></img>", formatting);//implementation of specific content (Such as chests) may be handled here...
				break;
			case 3:
				printf("<img %s src='assets/wall.jpg'></img>", formatting);//implementation of specific content (Such as chests) may be handled here...
				break;
			case 4:
				printf("<img %s src='assets/bog.jpg'></img>", formatting);//implementation of specific content (Such as chests) may be handled here...
				break;
			case 5:
				printf("<img %s src='assets/swamp.jpg'></img>", formatting);//implementation of specific content (Such as chests) may be handled here...
				break;
		}
		
	}	
}