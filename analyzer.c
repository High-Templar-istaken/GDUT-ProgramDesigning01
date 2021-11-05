#include "mycheck.h"

void analyze_init(char *put[])
{
	int tmp=0;
	#define add put[++tmp]=
	add"refresh";
	add"display";
	add"help";
	add"init";
	add"header";
	add"row";
	add"query";
	add"sort";
	add"veryend";
	return;
}

/*
Analyze function[public]
return code:
-1 -> no argument input
-2 -> unknown command type
-3 -> failed to get return
*/
int analyze(int argc, char *argv[])
{
	// robustness
	if(argv[0] == NULL || argv[1] == NULL) return -1;
	
	//init
	char *command_set[101],*endsymbol="veryend";
	analyze_init(command_set);
	
	//detect command type
	int i;
	
	for(i=1;strcmp(endsymbol,command_set[i])!=0;++i)
	{
		if(strcmp(command_set[i],argv[1])==0)
		{
			int back=-3;
			switch(i)
			{
				case 1:printf("debug: refresh!\n");
					break;//refresh
				case 2:printf("debug: display!\n");
					break;//display
				case 3:
					break;//help
				case 4:
					break;//init
				case 5:
					break;//header
				case 6:
					break;//row
				case 7:printf("query: display!\n");
					break;//query
				case 8:
					break;//sort
				default:
					break;//WTF
			}
			return back;
		}
	}
	
	return -2;
}
