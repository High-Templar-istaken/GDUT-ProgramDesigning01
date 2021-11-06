#include "mycheck.h"

void getheader_n_mode(char id, char displayname)
{
	
}

void getheader_argument(int argc,char *argv[])
{
	char *arg1 = NULL, *arg2 = NULL;
	for(int i = 2 ; argv[i] != NULL ; ++i)
	{
		if(strcmp(argv[i],"-n") == 0)
		{
			if(argv[i+1] == NULL || argv[i+2] == NULL)
			{
				printf("Error: In function 'getheader': Wrong format of argument '-n'\n");
				exit(0);
			}
			getheader_n_mode(argv[i+1],argv[i+2]);
			i+=2;
		}
		else if(strcmp(argv[i],"-m") == 0)
		{
			if(argv[i+1] == NULL || argv[i+2] == NULL)
			{
				printf("Error: In function 'getheader': Wrong format of argument '-m'\n");
				exit(0);
			}
			arg1 = argv[i+1];
			arg2 = argv[i+2];
			i+=2;
		}
		else if(strcmp(argv[i],"-d") == 0)
		{
			if(argv[i+1] == NULL)
			{
				printf("Error: In function 'getheader': Wrong format of argument '-d'\n");
				exit(0);
			}
			arg1 = argv[i+1];
			++i;
		}
		else if(strcmp(argv[i],"-r") == 0)
		{
			if(argv[i+1] == NULL || argv[i+2] == NULL)
			{
				printf("Error: In function 'getheader': Wrong format of argument '-r'\n");
				exit(0);
			}
			arg1 = argv[i+1];
			arg2 = argv[i+2];
			i+=2;
		}
		else
		{
			printf("Error: In function 'getheader': Unknown argument '%s'\n", argv[i]);
			exit(0);
		}
	}
}

int getheader(int argc,char *argv[])
{
	getheader_argument(argc, argv);
	
	return 0;
}
