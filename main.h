// This file declares global data structures and functions
// used in the cgi files
// Contributors: Dumitru Mitaru-Berceanu

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
// obstacle_name and energies arrays
// (ex char* tree_name = obstacle_name[TREE]
//     int tree_energy = obstacle_energy[TREE])
#define TREE    0
#define BOULDER 1
#define BUSH	  2 
// Constants used to index into 
// tool_name and energies arrays
#define HATCHET    0
#define AXE        1
#define CHAINSAW   2
#define CHISEL     3
#define SLEDGE     4
#define JACKHAMMER 5
#define MACHETE    6
#define SHEARS     7

// names and energies of obstacles
extern const char* obstacle_names[];
extern const int obstacle_energies[];
// names and energies of tools used to remove obstalces
extern const char* tool_names[];
extern const int tool_energies[];


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

//FILE IO Functions
int read_file(Player *player, Map *map, FILE *fp, int map_selection);
int write_file(Player *player, Map *map, FILE *fp);
//PLAYER MOVEMENT FUNCTIONS
int move_player(char *query, Player *player, Map *map);
int has_boat(Player * player);
int has_binoc(Player * player);


//MEMORY FUNCTIONS
void resetstate(FILE *fp, FILE *fp2);
void free_memory(Player *player, Map *map);
void initialize_player(Player *player);

int viewTiles(); //Reveals everything around the player in his/her view range
int checkPassable(Map * myMap, Player * myPlayer, char * query); //checks to see if inpassable terrain exists.
//checks for content in a given tile 
void check_item(Player * player, Map * map, char * useful_item); 
//checks logic for chests as well as interaction with bog. 
int decrementenergy(Player* player, Map* map);


//HTML IO FUNCTIONS
int write_html(Player *player, Map *map);
void write_tile(Tile * tile_index);
void write_content(Tile *tile);


//Player Inventory Functionality
int add_item(Player * player, const char * item);
int purchaseItem(Player * player, const char * item, int price);

// From json.c
// This function adds a name-value pair to the current json string. The data
// types of value can either be INTEGER or STRING. Remember to pass pointers to integers
// (i.e &myint). it will return a pointer to the new json string. This caller is repsonsible
// for freeing this newly allocated string. The curr_json string, that is passed in, is freed in the function since for our purposes
// we will not be using it anymore, so its just convienient.
char* add_name_value_pair(char* curr_json, const char* name, const void* value, int data_type);

// from obstacle.c. 

// This function will remove an obstacle from the map at the players
// location with their choice of tool to use
// It will decrement the players energy, remove the obstacle from the map
// and remove the tool of choice from the players inventory
void remove_obstacle(Player*, Map*, int tool_index);
// Return the obstacle index, -1 if not found 
int get_obstacle_index(Player*, Map*);
// Return the tool index, -1 if not found
int get_tool_index(char* tool_name);
// Remove the obstacle from the map
void remove_obstacle_from_map(Player*, Map*);
// Remove the tool from the player inventory
void remove_tool_from_inventory(Player*, int);
// Check if the obstacle to remove and the tool
// chosen to remove it matches. 1 for match, 0 otherwise 
int check_obstacle_tool_match(int, int);

//from clue.h
//this function will check for appropriate clue and recieve information regarding distance from diamonds.
int check_for_clue(Player*, Map*, int*, int*, int*, int*);
#endif /* MAIN_H */
