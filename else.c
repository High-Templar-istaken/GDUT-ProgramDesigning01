#include "mycheck.h"

int refresh(int argc,char *argv[])
{
	for(int i = 2; argv[i] != NULL ; ++i)
	{
		printf("Error: In function 'refresh': Unknown input argument '%s'\n", argv[i]);
		exit(0);
	}
	
	char *tmp = (char*) malloc (sizeof(char)*MAX_INPUT_CACHE);
	FILE *storage = fopen("./.mycheck/storage.txt","r");
	FILE *working = fopen("./.mycheck/working.txt","w");
	
	while(fgets(tmp,MAX_INPUT_CACHE,storage) != NULL)
	{
		fprintf(working,"%s",tmp);
	}
	
	fclose(storage);fclose(working);
	free(tmp);
	return 0;
}

int gethelp(int argc,char *argv[])
{
	for(int i = 2; argv[i] != NULL ; ++i)
	{
		printf("Error: In function 'gethelp': Unknown input argument '%s'\n", argv[i]);
		exit(0);
	}
	
	printf("to be finished...\n");
	return 0;
}

int getinit(int argc,char *argv[])
{
	bool confirm = false;
	for(int i = 2; argv[i] != NULL ; ++i)
	{
		if(strcmp(argv[i],"-y") == 0)
		{
			confirm = true;
		}
		else
		{
			printf("Error: In function 'getinit': Unknown input argument '%s'\n", argv[i]);
			exit(0);
		}
	}
	if(confirm == true)
	{
		system("rd /s /q .mycheck");
		system("mkdir .mycheck");
		
		system("type nul > ./.mycheck/working.txt");
		system("echo.>> ./.mycheck/working.txt");
		system("echo.>> ./.mycheck/working.txt");
		
		system("type nul > ./.mycheck/storage.txt");
		system("echo.>> ./.mycheck/storage.txt");
		system("echo.>> ./.mycheck/storage.txt");
	}
	if(confirm == false)
	{
		system("rd .mycheck");
		system("mkdir .mycheck");
		
		system("type nul >> ./.mycheck/working.txt");
		system("echo.>> ./.mycheck/working.txt");
		system("echo.>> ./.mycheck/working.txt");
		
		system("type nul >> ./.mycheck/storage.txt");
		system("echo.>> ./.mycheck/storage.txt");
		system("echo.>> ./.mycheck/storage.txt");
	}
	system("cls");
	printf("Initialize complete\n");
	
	return 0;
}
