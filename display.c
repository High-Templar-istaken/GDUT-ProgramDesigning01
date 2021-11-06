#include "mycheck.h"

// -3 function run failed
int display(int argc, char *argv[])
{
	// grammar check & arguments set
	bool ShowInvisible=false;
	for(int i = 2; i < argc; ++i)
	{
		if(strcmp(argv[i],"-v")==0) // -v argument stands for 'show inVisible'
		{
			ShowInvisible=true;
		}
		else
		{
			printf("Fatal Error: In function 'Display': Unknown argument '%s'\n",argv[i]);
			return -3;
		}
	}
	
	// create a filereading stream
	FILE *WorkReader = fopen("./.mycheck/working.txt", "r");
	
	// reading the header of this file 
	ReadTheHeader(WorkReader);
	
	//debug: output all header
	ShowAllHeader();
	
	// fill the in-program row
 	ReadAllRow(WorkReader);
	
	//debug: display all row
	ShowAllRow();
	
	if(DEBUG) printf("debug: Display safely\n");
	return 0;
}
