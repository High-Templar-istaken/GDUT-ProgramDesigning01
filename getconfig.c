#include "mycheck.h"

void getconfig_m_mode(int argc, char *argv[])
{
	initconfig();
	
	if(argv[3] == NULL || argv[4] == NULL)
	{
		printf("Error: In function 'getconfig': Wrong input of '-m' argument!\n");
		exit(0);
	}
	if(strcmp(argv[3],"Debug") == 0 || strcmp(argv[3],"1") == 0)
	{
		if(_templar_JudgeStringIsNumber(argv[4]) == false)
		{
			printf("Error: In function 'getconfig': '%s' is not a number!\n",argv[4]);
			exit(0);
		}
		DEBUG = _templar_StringToNumber(argv[4]);
	}
	else if(strcmp(argv[3],"Max_Input_Cache") == 0 || strcmp(argv[3],"2") == 0)
	{
		if(_templar_JudgeStringIsNumber(argv[4]) == false)
		{
			printf("Error: In function 'getconfig': '%s' is not a number!\n",argv[4]);
			exit(0);
		}
		MAX_INPUT_CACHE = _templar_StringToNumber(argv[4]);
	}
	else if(strcmp(argv[3],"Always_Show_Table") == 0 || strcmp(argv[3],"3") == 0)
	{
		if(_templar_JudgeStringIsNumber(argv[4]) == false)
		{
			printf("Error: In function 'getconfig': '%s' is not a number!\n",argv[4]);
			exit(0);
		}
		AlwaysShowtable = _templar_StringToNumber(argv[4]);
	}
	else if(strcmp(argv[3],"MuteTheExitMessage") == 0 || strcmp(argv[3],"4") == 0)
	{
		if(_templar_JudgeStringIsNumber(argv[4]) == false)
		{
			printf("Error: In function 'getconfig': '%s' is not a number!\n",argv[4]);
			exit(0);
		}
		ExitMute = _templar_StringToNumber(argv[4]);
	}
	else
	{
		printf("Error: In function 'getconfig': Wrong input '%s' of '-m' argument!\n",argv[3]);
		exit(0);
	}
	FILE *config = fopen("./.mycheck/config.txt","w");
	fprintf(config,"%d\n%d\n%d\n%d\n",DEBUG,MAX_INPUT_CACHE,AlwaysShowtable,ExitMute);
	fclose(config);
}

void getconfig_list_mode()
{
	initconfig();
	printf("Debug(1) = %d\n",DEBUG);
	printf("Max_Input_Cache(2) = %d\n",MAX_INPUT_CACHE);
	printf("Always_Show_Table(3) = %d\n",AlwaysShowtable);
	printf("MuteTheExitMessage(4) = %d\n",ExitMute);
}

void getconfig_reset_mode()
{
	FILE *config = fopen("./.mycheck/config.txt","w");
	fprintf(config,"0\n10001\n1\n0\n");
	fclose(config);
}

int getconfig(int argc, char *argv[])
{
	ReadTable("./.mycheck/working.txt"); 
	
	if(argc <= 2)
	{
		printf("ERROR: In function 'getconfig': No arguments!\n");
		exit(0);
	}
	
	if(strcmp(argv[2],"-list") == 0)
	{
		getconfig_list_mode();
	}
	else if(strcmp(argv[2],"-m") == 0)
	{
		getconfig_m_mode(argc,argv);
	}
	else if(strcmp(argv[2],"-reset") == 0)
	{
		getconfig_reset_mode();
	}
	else
	{
		printf("Error: In function 'getconfig': Unrecognized argument '%s'!\n",argv[2]);
		exit(0);
	}
	return 0;
}
