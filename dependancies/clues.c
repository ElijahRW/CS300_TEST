#include "../main.h"


int check_for_clue(Player* player, Map* map, int* north, int* east, int* south, int* west){
	
	int diax = -1;
	int diay = -1;
	int playx = player->x;
	int playy = player->y;
	//int north, east, south, west;
	int tempnorth, tempeast, tempsouth, tempwest;
	int distance;
	int max = map->size;


//check to find clue.
	if (strcmp(map->tiles[player->x][player->y].content, "CLUE1") != 0 && strcmp(map->tiles[player->x][player->y].content, "CLUE2") != 0)
	{
		return 0;
	}
	if (strcmp(map->tiles[player->x][player->y].content, "CLUE2") == 0)
	{
		return 2;
	}

//find coordinates of diamond.
	for(int i = 0; i < map->size; i++) 
	{
		for(int j = 0; j < map->size; j++) 
		{
			if(strcmp(map->tiles[i][j].content, "DIAMOND") == 0)
			{
				diax = i;
				diay = j;
				break;
			}	
		}
	}
//if no diamond return.
	if (diax == -1 && diay == -1)
	{
		return 0;
	}
//find the shortest path.
	else
	{
		//NE case
		*north = diay - playy;
		*south = 0;
		*west = 0;
		if(*north < 0)
		{
			*north += max;
		}
		*east = diax - playx;
		if(*east < 0)
		{
			*east += max;
		}
		distance = *north + *east;

		//NW case
		tempnorth = diay - playy;
		if(tempnorth < 0)
		{
			tempnorth += max;
		}
		tempwest = playx - diax;
		if(tempwest < 0)
		{
			tempwest += max;
		}
		if((tempnorth + tempwest) < distance)
		{
			distance = tempnorth + tempwest;
			*north = tempnorth;
			*west = tempwest;
			*east = 0;
			*south = 0;
		}

		//SE case
		tempsouth = playy - diay;
		if(tempsouth < 0)
		{
			tempsouth += max;
		}
		tempeast = diax - playx;
		if(tempeast < 0)
		{
			tempeast += max;
		}	
		if((tempsouth + tempeast) < distance)
		{
			distance = tempsouth + tempeast;
			*south = tempsouth;
			*east = tempeast;
			*north = 0;
			*west = 0;
		}

		//SW case
		tempsouth = playy - diay;
		if(tempsouth < 0)
		{
			tempsouth += max;
		}
		tempwest = playx - diax;
		if(tempwest < 0)
		{
			tempwest += max;
		}
		if((tempsouth + tempwest) < distance)
		{
			distance = tempsouth + tempwest;
			*south = tempsouth;
			*west = tempwest;
			*north = 0;
			*east = 0;
		}
		return 1;
	}
}
