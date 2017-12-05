#include "../main.h"
//Sunanth Sakthivel
//resets state back to original for restoring file back to default map values. 
void resetstate(FILE *fp, FILE *fp2)
{
	char c;
	
	fp = fopen("def_state.txt", "r");
	fp2 = fopen("game_state.txt", "w"); 
	//overwrite with def_state.txt information. 
	while(1)
	{
		c = fgetc(fp);
		if(c == EOF)
		{
			break;
		}
		else
		{
			putc(c, fp2);
		}
	}

	fclose(fp);
	fclose(fp2);
}
