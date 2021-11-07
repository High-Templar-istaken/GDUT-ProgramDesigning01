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
	add"sum";
	add"modify";
	add"clean";
	add"veryend";
	return;
}

/*
Analyze function[public]
return code:
-1 -> no argument input
-2 -> unknown command type
-3 -> failed to get function return
*/
int analyze(int argc, char *argv[])
{
	// robustness
	if(argv[0] == NULL || argv[1] == NULL) return -1;
	
	//init
	char *command_set[101];
	analyze_init(command_set);
	
	//detect command type
	int i;
	
	for(i=1;strcmp("veryend",command_set[i])!=0;++i)
	{
		if(strcmp(command_set[i],argv[1])==0)
		{
			int back=-3;
			switch(i)
			{
				case 1:if(DEBUG) printf("debug: refresh!\n");
					 back = refresh(argc, argv);
					break;//refresh
				case 2:if(DEBUG) printf("debug: display!\n");
		  			 back = display(argc, argv);
					break;//display
				case 3:if(DEBUG) printf("debug: help\n");
					 back = gethelp(argc, argv);
					break;//help
				case 4:if(DEBUG) printf("debug: init\n"); 
					 back = getinit(argc, argv);
					break;//init
				case 5:if(DEBUG) printf("debug: header\n");
					 back = getheader(argc,argv);
					break;//header
				case 6:
					break;//row
				case 7:
					break;//query
				case 8:
					break;//sort
				case 9:
					break;//sum
				case 10:
					break;//modify
				case 11:
					break;//clean
				default:printf("Error: In function 'analyze': Unknown command '%s'\n",argv[1]);
					break;//WTF
			}
			return back;
		}
	}
	
	return -2;
}
