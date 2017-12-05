#include "../main.h"

void write_terrain(Tile * tile);
/*(Written By Elijah Rich-Wimmer)
--Name: write_html
--Input: Player structure to read in player coordinates, Map structure pointer contains all of the relevent information for the map output
--Output: The correctly formatted, html table with immage tags and content is printed to the console 
*/
int write_html(Player *player, Map *map)
{
	//Visibility function is called. (Unhides tiles the player should see.
	viewTiles(player, map);
	//assign local variables for player's location
	int playerx = player->x;
	int playery = player->y;
	//Print table opening tag.
	printf("<table cellpadding='0'>");
	int size = map->size;
	for(int y = size-1; y >= 0; --y)//steps through every row of map top to bottom.
	{
		for(int x = 0; x<size; ++x)//steps through every column in the left to right.
		{
			printf("<th><div class='parent'>");//row tab opener.
			if(playerx==x && playery==y)//if tile of player location is printed, then display hero without content.
			{
				write_terrain(&(map->tiles)[x][y]);//prints terrain tile behind player.
				printf("<img class='image2' height='30' src='assets/hero.png'></img>");
				//printf("<th><img height='25' width='25' src='assets/hero.jpg' align='middle'></img></th>");
				
			}
			else
			{
				//calls function to print immage tags
				write_tile(&((map->tiles)[x][y]));
			}
			printf("</div></th>");//closing collumn (content tag
		}
		printf("</tr>");//closing row tag
	}
	//print table closing tag.
	printf("</table>");
	return 1;
}

/*(Written By Elijah Rich-Wimmer
--Name: write_tile
--Input: Tile structure pointer will contain all of the information for the tile to be printed
--Output: if the tile is set to invisible. then a fog tile is printed. otherwise, the write terrain and write_content_functions are called
*/
void write_tile(Tile *tile)
{
	const char * formatting = "class='image1' height='30'";
	//printf("<div class='parent'>");
	//Immage reference (KEY):(0=meadow/grass, 1=forest, 2=water, 3=wall, 4=bog, 5=swamp)
	//Additionally, content such as trees should be taken into account: 
	if(tile->visibility == 0)
	{
		printf("<img %s src='assets/fog.jpg'></img>", formatting);
	}
	else
	{
		write_terrain(tile);
		write_content(tile);//implements specific content (if any are to be found).

	}
		//printf("</div>");	
}

/*(Written By Elijah Rich-Wimmer
--Name: write_terrain
--Input: Tile structure pointer will contain all of the information for the printed tile
--Output: The correctly formatted immage tag for the terrain will be printed to the console
*/
void write_terrain(Tile * tile)
{
		const char * formatting = "class='image1' height='30'";
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
}


/*(Written By Elijah Rich-Wimmer)
--Name: write_content
--Purpose: This function prints the content immage on top of the terrain map (allowing various combinations of content and terrain)
--Input: tile is a pointer to the tile structur that is to be printed
--Output: if tile has content, a properly formated html immage tag is printed to the console/cgi
*/
void write_content(Tile *tile)
{
	const char * formatting = "class='image2' height='30'";
	char * content = tile->content;
	if(strcmp(content,"None")!=0)//looks at the tile structures content coordinates 
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
		else if(strcmp(content, "TYPE1")==0)
		{
			printf("chest");
		}
		else if(strcmp(content, "TYPE2")==0)
		{
			printf("chest");
		}
		else if(strcmp(content, "CLUE1")==0)
		{
			printf("clue");
		}
		else if(strcmp(content, "CLUE2")==0)
		{
			printf("clue");
		}    
		else if(strcmp(content, "Binoculars")==0)
		{
			printf("binocs");
		}
		
    printf(".png'></img>");//ends tag

	}
	
}
