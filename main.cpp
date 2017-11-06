#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>

using namespace std;



void print_table();

int main ()
{
	char protocolString[160];
	strncpy(protocolString, getenv("QUERY_STRING"),159);
	cout << "Content-Type: text/html;charset=us-ascii\n\n";
	//cout << protocolString << "\n\n\n\n";
	print_table();
  return 0;
}

//This function  is a demonstration of how a program would output a map (currently in text format)
//Theoretically, the actual content of each cell would be handled by an external class.
//This function should theoretically be callable either dirrectly, or via the game logic
void print_table()
{
	int x_lim = 10;
	int y_lim = 10;
	for(int x  = 0; x < x_lim; ++x)
	{
		cout <<"<tr>";
		for(int y = 0; y < y_lim; ++y)
		{
			cout <<"<th>testing</th>";
		}
		cout << "</tr>";
	
	}
}

