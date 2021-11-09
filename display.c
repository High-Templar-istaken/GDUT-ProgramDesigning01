#include "mycheck.h"

// -3 function run failed
int display(int argc, char *argv[])
{
	// grammar check & arguments set
	showcode=false;
	for(int i = 2; i < argc; ++i)
	{
		if(strcmp(argv[i],"-c")==0) // -v argument stands for 'show inVisible'
		{
			showcode = true;
		}
		else
		{
			printf("Fatal Error: In function 'Display': Unknown argument '%s'\n",argv[i]);
			return -3;
		}
	}
	
	ReadTable("./.mycheck/working.txt");
	
	//start to display all stuff
	DebugPrintTable();
	printf("------Current Working Table------\n");
	ReleasePrintTable();
	
	if(DEBUG) printf("debug: Display safely\n");
	return 0;
}
