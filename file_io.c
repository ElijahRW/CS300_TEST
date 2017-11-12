#include "main.h"
/*
--FILE WRITTEN BY: Jacob Collins

--Edited by: ELIJAH RICH-WIMMER
		Purpose: 1. Fix certain logic errors and added location range invalid input exceptions
*/
//THIS FUNCTION can't currently handle invalid input (CONSIDER Changing this) [EPRW]
int read_file(Player *player, Map *map, FILE *fp)
{
	int len = 0;
	int i = 0;
	int j = 0;
	int vis = 0;
	int terrain = 0;
	char buffer[100];

	fp = fopen("game_state.txt", "r");

	if(!fp) return 0;

	// Create the map matrix based off the size given, and initialize 
	fscanf(fp, "%d\n", &(map->size));
	map->tiles = (Tile **) malloc(map->size * sizeof(Tile*));
	for(i = 0; i < map->size; i++) {
		map->tiles[i] = (Tile *) malloc(map->size * sizeof(Tile));
		for(j = 0; j < map->size; j++) {
			(map->tiles[i][j]).x = i;
			(map->tiles[i][j]).y = j;
			(map->tiles[i][j]).visibility = 0;
			(map->tiles[i][j]).terrain = 0;
			(map->tiles[i][j]).content = NULL;
		}
	}


	fscanf(fp, "#####\n");
	fscanf(fp, "%i,%i\n", &(player->x), &(player->y));
	fscanf(fp, "%d\n", &(player->energy));
	fscanf(fp, "%d\n", &(player->money));

	for(i = 0; i < 10; i++) {
		fscanf(fp, "%s\n", buffer);
		len = strlen(buffer) + 1;
		player->inventory[i] = malloc(len * sizeof(char));
		strcpy(player->inventory[i], buffer);
	}
	
	//THIS SHOULD HAVE BEEN TESTED FOR FILE IO WAS NOT FULLY FUNCTIONAL UNTIL THIS LINE WAS ADDED [EPRW]
	fscanf(fp, "#####\n");

	//reads in custom information from the file (SEQUENCE IS NOT necessary for this read!! ORDER IS) [EPRW]
	//Code didn't have range check....
	while(fscanf(fp, "%i,%i,%i,%i,%s", &i, &j, &vis, &terrain, buffer) != EOF) {
		if(i < map->size && j < map->size)//bounds check (checking for impropper input [EPRW]
		{
				//(map->tiles[i][j]).x = i;//is this necessary?
				//(map->tiles[i][j]).y = j;//is this necessary? (This was already defined during the implementation function call and SHOULDN"T BE CHANGED [EPRW]
				(map->tiles[i][j]).visibility = vis;
				(map->tiles[i][j]).terrain = terrain;
				len = strlen(buffer) + 1;
				(map->tiles[i][j]).content = malloc(len * sizeof(char));
				strcpy((map->tiles[i][j]).content, buffer);
		}
	}


	fclose(fp);
	return 1;
}

int write_file(Player *player, Map *map, FILE *fp)
{
	int i, j;

	fp = fopen("game_state.txt", "w");

	if(!fp) return 0;

	fprintf(fp, "%d\n", map->size);
	fprintf(fp, "#####\n");
	fprintf(fp, "%d,%d\n", player->x, player->y);
	fprintf(fp, "%d\n", player->energy);
	fprintf(fp, "%d\n", player->money);
	for(i = 0; i < 10; i++) {
		fprintf(fp, "%s\n", player->inventory[i]);
	}
	fprintf(fp, "#####\n");
	for(i = 0; i < map->size; i++) {
		for(j = 0; j < map->size; j++) {
			fprintf(fp, "%d,", map->tiles[i][j].x);
			fprintf(fp, "%d,", map->tiles[i][j].y);
			fprintf(fp, "%d,", map->tiles[i][j].visibility);
			fprintf(fp, "%d,", map->tiles[i][j].terrain);
			if(map->tiles[i][j].content) {
				fprintf(fp, "%s\n", map->tiles[i][j].content);
			}
			else {
				fprintf(fp, "%s\n", "None");
			}
		}
	}

	fclose(fp);
}
