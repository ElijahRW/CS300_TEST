#ifndef MAIN_H
#define MAIN_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <cgi.h>

// Data types used in json.c
#define INTEGER 0
#define STRING 1

typedef struct {
	int x;
	int y;
	int energy;
	int visibility;
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

int viewTiles(); //Reveals everything around the player's view range

int decrementenergy(Player* player, Map* map);



int write_html(Player *player, Map *map);
void write_tile(Tile * tile_index);


// From json.c
// This function adds a name-value pair to the current json string. The data
// types of value can either be INTEGER or STRING. Remember to pass pointers to integers
// (i.e &myint). it will return a pointer to the new json string. This caller is repsonsible
// for freeing this newly allocated string. The curr_json string, that is passed in, is freed in the function since for our purposes
// we will not be using it anymore, so its just convienient.
char* add_name_value_pair(char* curr_json, const char* name, const void* value, int data_type);
#endif /* MAIN_H */
