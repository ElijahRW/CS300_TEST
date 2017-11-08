#include "main.h"

int write_html(Player *player, Map *map)
{
	int playerx = player->x;
	int playery = player->y;
	printf("<table>");
	for(int y = (map->size)-1; y >= 0; --y)//awkward initialization (Will consider reworking
	{
		printf("<tr>");
		for(int x = (map->size)-1; x >=0; --x)//awkward initialization (Will consider reworking
		{
			if(playerx==x && playery==y)
			{
				printf("<th>|PLAYER| </th>");
			}
			
			printf("<th>|%i| </th>",  x+y/*(map->tiles[x][y]).terrain*/);
		}
		printf("</tr>");
	}
	printf("</table>");
	return 1;
}