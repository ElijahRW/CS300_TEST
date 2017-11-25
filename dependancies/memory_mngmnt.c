#include "../main.h"

void initialize_player(Player *player)
{
	int i;

	player->x = 0;
	player->y = 0;
	player->energy = 0;
	player->money = 0;
	player->visibility = 1;
	for(i = 0; i < 10; i++) {
		player->inventory[i] = malloc(5 * sizeof(char));
		strcpy(player->inventory[i], "None");
	}
}

void free_memory(Player *player, Map *map)
{
	int i, j;

	// Free all dynamic memory of the map
	for(i = 0; i < map->size; i++) {
		for(j = 0; j < map->size; j++) {
			if(map->tiles[i][j].content) {
				free(map->tiles[i][j].content);
			}
			map->tiles[i][j].content = NULL;
		}
		if(map->tiles[i]) {
			free(map->tiles[i]);
		}
		map->tiles[i] = NULL;
	}
	if(map->tiles) {
		free(map->tiles);
	}
	map->tiles = NULL;

	// Free all dynamic memory for the player
	for(i = 0; i < 10; i++) {
		if(player->inventory[i]) {
			free(player->inventory[i]);
		}
	}
}
