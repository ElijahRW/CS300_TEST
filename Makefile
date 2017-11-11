all:
	gcc *.c -g -lcgi -o main.cgi
	chmod o+r home.html
	chmod 755 assets
	chmod o+r assets/*.jpg
