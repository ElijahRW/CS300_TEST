#include "main.h"

int write_html(Player *player, Map *map)
{
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
	if(tile->visibility == 0)
	{
		printf("<img height='25' width='25' src='assets/fog.jpg' align='middle'></img>");
	}
	else
	{
		int terrain = tile->terrain;
		switch(terrain)
		{
			case 0:
				printf("<img height='25' width='25' src='assets/grass.jpg' align='middle'></img>");//implementation of specific content (Such as chests) may be handled here...
				break;
			case 1:
				printf("R");
				break;
			case 2:
				printf("T");
				break;
			//ETC Fill 
			
			
		}
		
	}	
}