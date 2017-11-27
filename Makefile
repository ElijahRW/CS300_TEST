all:
	gcc main.c ./dependancies/*.c  player_inventory.c -g -lcgi -o main.cgi
	gcc remove_obstacle.c dependancies/*.c -g -lcgi -o remove_obstacle.cgi
	gcc main.c ./dependancies/*.c player_inventory.c -g -lcgi -o main.cgi
	gcc buy_item.c ./dependancies/*.c -g -lcgi -o buy_item.cgi
	chmod o+r *.html assets/*.jpg
	chmod 755 assets
