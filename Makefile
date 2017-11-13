all:
	gcc *.c -g -lcgi -o main.cgi
	chmod o+r *.html assets/*.jpg
	chmod 755 assets
