#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <cgi.h>

typedef struct {
	int x;
	int y;
	int energy;
	int money;
	char * inventory[10];
} Player; 

typedef struct {
	int x;
	int y;
	int visibility;
	int terrain;
	char * content;
} Tile; 

typedef struct {
	int size;
	Tile ** tiles;
} Map;

int read_file(Player *player, Map *map, FILE *fp);
int write_file(Player *player, Map *map, FILE *fp);

int main()
{
	char direction[1];
	s_cgi *cgi;
	FILE *fp;
	Player player;
	Map map;
	int i, j;

	cgi = cgiInit();

	strcpy(direction,cgiGetValue(cgi,"direction"));

	printf("Content-Type: text/html;charset=us-ascii\n\n");

	player.x = 0;
	player.y = 0;
	player.energy = 0;
	player.money = 0;
	for(i = 0; i < 10; i++) {
		player.inventory[i] = malloc(5 * sizeof(char));
		strcpy(player.inventory[i], "None");
	}

	read_file(&player, &map, fp);

	if(strcmp(direction, "N") == 0) ++player.y;
	else if(strcmp(direction, "S") == 0) --player.y;
	else if(strcmp(direction, "E") == 0) ++player.x;
	else if(strcmp(direction, "W") == 0) --player.x;

	write_file(&player, &map, fp);

	printf("%d, %d\n", player.x, player.y);
	
	return 0;
}

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
	fscanf(fp, "%d,%d\n", &(player->x), &(player->y));
	fscanf(fp, "%d\n", &(player->energy));
	fscanf(fp, "%d\n", &(player->money));

	for(i = 0; fscanf(fp, "%s\n", buffer) && i < 10; i++) {
		len = strlen(buffer) + 1;
		player->inventory[i] = malloc(len * sizeof(char));
		strcpy(player->inventory[i], buffer);
	}

	while(fscanf(fp, "%d,%d,%d,%d,%s", &i, &j, &vis, &terrain, buffer) != EOF) {
		(map->tiles[i][j]).x = i;
		(map->tiles[i][j]).y = j;
		(map->tiles[i][j]).visibility = vis;
		(map->tiles[i][j]).terrain = terrain;
		len = strlen(buffer) + 1;
		(map->tiles[i][j]).content = malloc(len * sizeof(char));
		strcpy((map->tiles[i][j]).content, buffer);
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
