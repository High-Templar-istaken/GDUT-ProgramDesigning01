#include "mycheck.h"

void getrow_n_mode(char *filename, int argc, char* argv[])
{
	FILE *stream = fopen(filename,"r");
	ReadTable(stream);
	fclose(stream); stream = NULL;
	
	int argcnt=0;
	for(int i = 3; argv[i] != NULL ; ++i) ++argcnt;
	
	if(DEBUG) printf("debug: In function 'getrow_n_mode': cntinput=%d WHILE needinput=%d\n",argcnt,(*headerend).code);
	
	if(argcnt != (*headerend).code)
	{
		printf("ERROR: In function 'getrow_n_mode': input value(s) don't match the header(s) ONE BY ONE\n");
		exit(0);
	}
	
	PHEADER nowheader = headerbegin;
	while(nowheader != NULL)
	{
		
		
		nowheader = (*nowheader).nxtheader;
	}
}

void getrow_argument(int argc,char *argv[])
{
	for(int i = 2 ; argv[i] != NULL ; ++i)
	{
		if(strcmp(argv[i],"-n") == 0)
		{
			if(argv[i+1] == NULL || argv[i+2] == NULL)
			{
				printf("Error: In function 'getrow': Wrong format of argument '-n'\n");
				exit(0);
			}
			//operating both lists
			getrow_n_mode("./.mycheck/working.txt",argc,argv);
//			getheader_n_mode("./.mycheck/storage.txt",argv[i+1],argv[i+2],(argv[i+3] == '\0')?"#":argv[i+3]);
			return;
		}
		/*
		else if(strcmp(argv[i],"-c=default") == 0 || strcmp(argv[i],"-c=name") == 0)
		{
			if(argv[i+1] == NULL || argv[i+2] == NULL)
			{
				printf("Error: In function 'getrow': Wrong format of argument '-c'\n");
				exit(0);
			}
			int changecode = 0;
			if(strcmp(argv[i],"-c=default") == 0) changecode = 1;
			else if(strcmp(argv[i],"-c=name") == 0) changecode = 2;
			
			getheader_c_mode("./.mycheck/working.txt",changecode,argv[i+1],argv[i+2]);
			getheader_c_mode("./.mycheck/storage.txt",changecode,argv[i+1],argv[i+2]);
			return;
		}
		*/
		else
		{
			printf("Error: In function 'getrow': Unknown argument '%s'\n", argv[i]);
			exit(0);
		}
	}
}

int getrow(int argc,char *argv[])
{
	getrow_argument(argc, argv);
	
	return 0;
}
