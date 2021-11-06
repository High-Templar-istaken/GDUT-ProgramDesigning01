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
	DEBUGShowAllHeader();
	
	// fill the in-program row
 	ReadAllRow(WorkReader);
	
	//debug: display all row
	DEBUGShowAllRow();
	
	//start to display all stuff
	PROW nowrow = rowbegin;
	PHEADER nowheader = headerbegin;
	PKEY nowkey = NULL;
	
	while(nowheader != NULL)
	{
		printf("%-20s",(*nowheader).name);
		nowheader = (*nowheader).nxtheader;
	}
	putchar('\n');
	
	nowrow = rowbegin;
	nowheader = headerbegin;
	nowkey = NULL;
	while(nowrow != NULL)
	{
		nowheader = headerbegin;
		
		while(nowheader != NULL)
		{
			nowkey = (*nowrow).keybegin;
			while(nowkey != NULL)
			{
				if(strcmp((*nowheader).id, (*nowkey).header) == 0)
				{
					printf("%-20s",(*nowkey).value);
					break;
				}
				nowkey = (*nowkey).nxtkey;
			}
			nowheader = (*nowheader).nxtheader;
		}
		putchar('\n');
		nowrow = (*nowrow).nxtrow;
	}
	
	if(DEBUG) printf("debug: Display safely\n");
	return 0;
}
