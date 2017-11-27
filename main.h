#ifndef MAIN_H
#define MAIN_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <cgi.h>

// Data types used in json.c
#define INTEGER 0
#define STRING  1
// Constants used to index into
// obstacle_name and enery arrays
// (ex char* tree_name = obstacle_name[TREE]
//     int tree_energy = obstacle_energy[TREE])
#define TREE    0
#define BOULDER 1
#define BUSH	  2 

// names and energies of obstacles
extern const char* obstacle_name[];
extern const int obstacle_energy[];


typedef struct {
	int x;
	int y;
	int energy;
	int visibility; //This is the default visibility
	int money;
	char hasBinocs; //1 if true, 0 if false
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

int read_file(Player *player, Map *map, FILE *fp, int map_selection);
int write_file(Player *player, Map *map, FILE *fp);
int move_player(char *query, Player *player, Map *map);
void resetstate(FILE *fp, FILE *fp2);
void free_memory(Player *player, Map *map);
void initialize_player(Player *player);

int viewTiles(); //Reveals everything around the player's view range
int checkPassable(Map * myMap, Player * myPlayer, char * query); //checks to see if inpassable terrain exists.
void check_item(Player * player, Map * map, char * useful_item); 

int decrementenergy(Player* player, Map* map);


//HTML IO functions
int write_html(Player *player, Map *map);
void write_tile(Tile * tile_index);
void write_content(Tile *tile);


//Player Inventory Functionality
int purchaseItem(Player * player, char input);


// From json.c
// This function adds a name-value pair to the current json string. The data
// types of value can either be INTEGER or STRING. Remember to pass pointers to integers
// (i.e &myint). it will return a pointer to the new json string. This caller is repsonsible
// for freeing this newly allocated string. The curr_json string, that is passed in, is freed in the function since for our purposes
// we will not be using it anymore, so its just convienient.
char* add_name_value_pair(char* curr_json, const char* name, const void* value, int data_type);
// from obstacle.c. It will check if the player is in 
// a tile that contains an object, in which it will remove 
// that object, decrement the players energy and 
// return the object index into the global
// arrays for object names and energy value
// if not object if found it will return -1
int check_for_obstacle(Player* player, Map* map);
#endif /* MAIN_H */
