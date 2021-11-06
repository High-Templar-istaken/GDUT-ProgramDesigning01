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
	char *firstline = NULL;
	_templar_GetTightString_Getline(&firstline, WorkReader);//firstline end with '\n'
	
	//devide the headers
	HeaderDevide(firstline);
	
	if(DEBUG)
	{
		printf("-----debug----\nHEADER that read\n");
		struct header* workinglist = headerbegin;
		while(workinglist!=NULL)
		{
			printf("id:%s WHILE name=%s\n", (*workinglist).id , (*workinglist).name);
			workinglist = (*workinglist).nxtheader;
		}
		printf("---debugend---\n");
	}
	
	if(DEBUG) printf("debug: Display safely\n");
	return 0;
}
