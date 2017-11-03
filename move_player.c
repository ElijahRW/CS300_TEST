#include "main.h"

int move_player(char *query, Player *player, Map *map)
{
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

	--player->energy;
}
