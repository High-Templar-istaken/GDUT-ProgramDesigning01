#include "mycheck.h"

int refresh(int argc,char *argv[])
{
	ReadTable("./.mycheck/working.txt");
	
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
	
	printf("Check \"Mycheck manual.chm\" in the same directory to get more information.\n");
	return 0;
}

int getinit(int argc,char *argv[])
{
	for(int i = 2; argv[i] != NULL ; ++i)
	{
		printf("Error: In function 'getinit': Unknown input argument '%s'\n", argv[i]);
		exit(0);
	}
	
	system("rd /s /q .mycheck");
	system("mkdir .mycheck");
	
	FILE *storage = fopen("./.mycheck/storage.txt","w");
	fprintf(storage,"0\n##:## \n##:## \nrowend\n \n \n");
	FILE *working = fopen("./.mycheck/working.txt","w");
	fprintf(working,"0\n##:## \n##:## \nrowend\n \n \n");
	FILE *config = fopen("./.mycheck/config.txt","w");
	fprintf(config,"0\n10001\n1\n0\n");
	fclose(working);fclose(storage);fclose(config);
	
	return 0;
}
