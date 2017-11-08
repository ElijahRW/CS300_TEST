#include "main.h"

int main()
{
	char * query;
	char buffer[100];
	s_cgi *cgi;
	FILE *fp;
	FILE *fp2;
	Player player;
	Map map;
	int i, j, len, diamond_found;

	diamond_found = 0;

	cgi = cgiInit();

	strcpy(buffer,cgiGetValue(cgi,"query"));
	len = strlen(buffer) + 1;
	query = malloc(len * sizeof(char));
	strcpy(query, buffer);

	printf("Content-Type: text/html;charset=us-ascii\n\n");

	initialize_player(&player);
	read_file(&player, &map, fp);

	if(strcmp(query, "N") == 0 || strcmp(query, "S") == 0 || strcmp(query, "E") == 0 || strcmp(query, "W") == 0) {
		move_player(query, &player, &map);
	}

	//temp location for diamond at coordinates (0,0). Fill in these values when location of diamond is placed. 
	int diamondx = 0;
	int diamondy = 0;
	
	
	//If statement to check coordinates that the player has moved into and the coordiantes of the diamonds
	if(map.tiles[diamondx][diamondy].x == player.x && map.tiles[diamondx][diamondy].y == player.y)
	{
			map.tiles[diamondx][diamondy].visibility = 1;
	}


	if(map.tiles[diamondx][diamondy].visibility && strcmp(map.tiles[diamondx][diamondy].content, "DIAMOND"))
	{
		resetstate(fp,fp2);
		free_memory(&player, &map); // free memory before reading info into the structs
		read_file(&player, &map, fp);
		diamond_found = 1; // diamond has been found
	}


	// START - PRINT ALL INFO FOR HTML TO PARSE
	printf("%d:%d:%d:%d:%d:", diamond_found, player.x, player.y, player.energy, player.money);
	for(int i = 0; i < 10; i++) {
		printf("%s,", player.inventory[i]);
	}
	printf(":%d:", map.size);
	
	/*for(int i = 0; i < map.size; i++) {
		for(int j = 0; j < map.size; j++) {
			if(map.tiles[i][j].visibility == 1) {
				printf("%d,%d,%d,%d,%s;", i, j, map.tiles[i][j].visibility, map.tiles[i][j].terrain, map.tiles[i][j].content);
			}
		}
	}*/
	printf(":");

	// END - PRINT ALL INFO FOR HTML TO PARSE
	write_file(&player, &map, fp); // write all info to the game state
	
	free(query); // free memory for the query string
	free_memory(&player, &map); // free the player and map memory


	//Writes Formated HTML to game map to display
	write_html(&player, &map);

  return 0;
}

void initialize_player(Player *player)
{
	int i;

	player->x = 0;
	player->y = 0;
	player->energy = 0;
	player->money = 0;
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
