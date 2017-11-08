#include "main.h"


/*
--NOTE FOR CONVENTION:
----x is left/right (east west)
----y is up/down (north south)
*/

int move_player(char *query, Player *player, Map *map)
{
	int max = map->size - 1;

	// Check which coordinate to update.
	if(strcmp(query, "N") == 0) {
		++player->y;
	}
	else if(strcmp(query, "S") == 0) {
		--player->y;
	}
	else if(strcmp(query, "E") == 0) {
		++player->x;
	}
	else if(strcmp(query, "W") == 0) {
		--player->x;
	}

	// Check x bounds
	if(player->x > max) {
		player->x = 0;
	}
	else if(player->x < 0) {
		player->x = max;
	}

	// Check y bounds
	if(player->y > max) {
		player->y = 0;
	}
	else if(player->y < 0) {
		player->y = max;
	}

	// Decrement energy due to movement
	--player->energy;
	// Make the tile visible
	map->tiles[player->x][player->y].visibility = 1;
}
