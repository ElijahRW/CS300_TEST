#ifndef MAIN_H
#define MAIN_H
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
int move_player(char *query, Player *player, Map *map);
void resetstate(FILE *fp, FILE *fp2);
void free_memory(Player *player, Map *map);
void initialize_player(Player *player);

int write_html(Player *player, Map *map);
void write_tile(Tile * tile_index);


#endif /* MAIN_H */
