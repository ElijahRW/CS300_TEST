#include "main.h"

int main()
{
	char * query;
	char buffer[100];
	s_cgi *cgi;
	FILE *fp;
	Player player;
	Map map;
	int i, j, len;

	cgi = cgiInit();

	strcpy(buffer,cgiGetValue(cgi,"query"));
	len = strlen(buffer) + 1;
	query = malloc(len * sizeof(char));
	strcpy(query, buffer);

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

	if(strcmp(query, "N") == 0 || strcmp(query, "S") == 0 || strcmp(query, "E") == 0 || strcmp(query, "W") == 0) {
		move_player(query, &player, &map);
	}

	write_file(&player, &map, fp);

	printf("%d, %d\n", player.x, player.y);
	
	return 0;
}
