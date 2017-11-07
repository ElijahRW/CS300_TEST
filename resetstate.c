#include "main.h"

//resets state back to original.
void resetstate(FILE *fp, FILE *fp2)
{
	char c;
	
	fp = fopen("def_state.txt", "r");
	fp2 = fopen("game_state.txt", "w"); 

	while(1)
	{
		c = fgetc(fp);
		if(c == EOF)
		{
			break;
		}
		else
		{
			putc(c, fp);
		}
	}

	fclose(fp);
	fclose(fp2);
}
