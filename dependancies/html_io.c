#include "../main.h"


/*(Written By Elijah Rich-Wimmer
--Name: write_html
--Input: Player structure to read in player coordinates, Map structure pointer contains all of the relevent information for the map output
--Output: The correctly formatted, html table with immage tags and content 
*/
int write_html(Player *player, Map *map)
{
	
	viewTiles(player, map);
	int playerx = player->x;
	int playery = player->y;
	printf("<table cellpadding='0'>");
	int size = map->size;
	for(int y = size-1; y >= 0; --y)//awkward initialization (Will consider reworking)
	{
		printf("<tr>");
		for(int x = 0; x<size; ++x)//awkward initialization (Will consider reworking)
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

/*(Written By Elijah Rich-Wimmer
--Name: write_tile
--Input: Tile structure pointer will contain all of the information 
--Output: The correctly formatted immage tag will be printed to the console
*/
void write_tile(Tile *tile)
{
	printf("<div class='parent'>");
	//Immage reference (KEY):(0=meadow/grass, 1=forest, 2=water, 3=wall, 4=bog, 5=swamp)
	//Additionally, content such as trees should be taken into account: 
	const char * formatting = "class='image1' height='30'";
	if(tile->visibility == 0)
	{
		printf("<img %s src='assets/fog.jpg' align='middle'></img>", formatting);
	}
	else
	{
		printf("<img %s src='assets/", formatting);
		switch(tile->terrain)
		{
			case 0:
				printf("grass");
				break;
			case 1:
				printf("forest");
				break;
			case 2:
				printf("water");
				break;
			case 3:
				printf("wall");
				break;
			case 4:
				printf("bog");
				break;
			case 5:
				printf("swamp");
				break;
		}
		//write_content(tile);//implements specific content (if any are to be found).
		printf(".jpg'></img>");//ends tag
		write_content(tile);//implements specific content (if any are to be found).

	}
		printf("</div>");	
}



void write_content(Tile *tile)
{
	const char * formatting = "class='image2' height='30'";
	char * content = tile->content;
	if(strcmp(content,"None")!=0)
	{
		printf("<img %s src='assets/", formatting);
		//printf("_");
		if(strcmp(content,"Tree")==0)
		{
			printf("tree");
		}
		else if(strcmp(content,"DIAMOND")==0)
		{
			printf("diamonds");
		}
		else if(strcmp(content,"Boulder")==0)
		{
			printf("boulder");
		}
		else if(strcmp(content,"Bush")==0)
		{
			printf("bush");
		}
		else if(strcmp(content,"Energy")==0)
		{
			printf("energy");
		}
		
		//Purchasable Items
		else if(strcmp(content, "Boat")==0)
		{
			printf("boat");
		}
		else if(strcmp(content, "Hatchet")==0)
		{
			printf("hatchet");
		}
		else if(strcmp(content, "Axe")==0)
		{
			printf("axe");
		}
		else if(strcmp(content, "Chainsaw")==0)
		{
			printf("chainsaw");
		}
		else if(strcmp(content, "Chisel")==0)
		{
			printf("chisel");
		}
		else if(strcmp(content, "Sledge")==0)
		{
			printf("sledge");
		}
		else if(strcmp(content, "Jackhammer")==0)
		{
			printf("jackhammer");
		}
		else if(strcmp(content, "Machete")==0)
		{
			printf("machete");
		}
		else if(strcmp(content, "Shears")==0)
		{
			printf("shears");
		}
    
		else if(strcmp(content, "Binoculars")==0)
		{
			printf("binocs");
		}
		
    printf(".png'></img>");//ends tag

	}
	
}
