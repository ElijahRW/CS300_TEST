all:
	gcc *.c -g -lcgi -o main.cgi
	chmod o+r home.html
