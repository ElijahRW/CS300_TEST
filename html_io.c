#include "main.h"

int write_html(Player *player, Map *map)
{
	int playerx = player->x;
	int playery = player->y;
	printf("<table>");
	int size = map->size;
	for(int y = size-1; y >= 0; --y)//awkward initialization (Will consider reworking
	{
		printf("<tr>");
		for(int x = size-1; x >=0; --x)//awkward initialization (Will consider reworking
		{
			if(playerx==x && playery==y)
			{
				printf("<th>P</th>");
			}
			
			printf("<th>");
			write_tile(&((map->tiles)[x][y]));
			printf("</th>");
		}
		printf("</tr>");
	}
	printf("</table>");
	return 1;
}
void write_tile(Tile *tile)
{
	//if(tile->visibility == 0)
	//{
		printf("INVIS");
	//}
	//else
	//{
		printf("TILE");
		
	//}	
}