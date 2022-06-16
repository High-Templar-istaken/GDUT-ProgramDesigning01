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
	
	/*bat again oops*/
	system("\".\\MANUAL\\UTF8 Boost.html\"");
	printf("A browser is required.\n");
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

int getport(int argc,char *argv[])
{
	if(argv[2] == NULL || argv[3] == NULL){
		printf("Error: In function 'getport': argument 2 is required.\n");
		exit(0);
	}
	for(int i = 4; argv[i] != NULL ; ++i)
	{
		printf("Error: In function 'getport': Unknown input argument '%s'\n", argv[i]);
		exit(0);
	}
	
	if(strcmp("-e",argv[2])==0){
		char tmps[]="copy /a /v .\\.mycheck\\working.txt ";
		char *command1 = (char*)malloc(sizeof(argv[3])+sizeof(tmps));
		memset(command1,'\0',sizeof(command1));
		
		
		strcat(command1,tmps);
		strcat(command1,argv[3]);
		
		/*Using Windows' bash due to potential bugs and i dont want to debug*/
		system(command1);
	}
	else if(strcmp("-i",argv[2])==0){
		
		char tmps1[]="copy /a ";
		char tmps2[]=" .\\.mycheck\\working.txt";
		
		char *command2 = (char*)malloc(sizeof(argv[3])+sizeof(tmps1)+sizeof(tmps2));
		memset(command2,'\0',sizeof(command2));
		
		
		strcat(command2,tmps1);
		strcat(command2,argv[3]);
		strcat(command2,tmps2);
		
		system(command2);
	}
	else{
		printf("Error: In function 'getport': Unknown input argument '%s'\n", argv[2]);
		exit(0);
	}
	
	return 0;
}
