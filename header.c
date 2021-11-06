#include "mycheck.h"

void DEBUGShowAllHeader()
{
	if(DEBUG)
	{
		printf("-----debug----\nHEADER that read\n");
		PHEADER workinglist = headerbegin;
		while(workinglist != NULL)
		{
			printf("id:%s WHILE name=%s\n", (*workinglist).id , (*workinglist).name);
			workinglist = (*workinglist).nxtheader;
		}
		printf("---debugend---\n");
	}
}

void ReadTheHeader(FILE *stream)
{
	char *line = NULL;
	_templar_GetTightString_Getline(&line, stream);//firstline end with '\n'
	
	if(DEBUG) printf("debug: In function 'ReadTheHeader': source=%s",line);
	
	PHEADER now = NULL;
	char tmp[10001];
	bool firstheader = true;
	
	int j = 0, i = 0;
	while(line[j] != '\n')
	{
		// create a new node
		if(firstheader != true)
		{
			(*now).nxtheader = (struct header*) malloc(sizeof(struct header));
			(*(*now).nxtheader).lasheader = now;
			now = (*now).nxtheader;
			(*now).nxtheader = NULL;
		}
		else
		{
			now = (struct header*) malloc(sizeof(struct header));
			(*now).nxtheader = NULL;
			(*now).lasheader = NULL;
			headerbegin = now;
			
			firstheader = false;
		}
		
		// read first chapter
		i = 0;
		while(line[j]!=':')
		{
			tmp[i++]=line[j++];
			if(line[j]==' '||line[j]=='\n')
			{
				printf("Error: In function 'HeaderDevide' Wrong format in the header of Working list!\n");
				exit(0);
			}
		}
		tmp[i]='\0';
		if(strlen(tmp) == 0)
		{
			printf("Error: In function 'HeaderDevide' Empty Header ID!\n");
			exit(0);
		}
		(*now).id = (char*) malloc(sizeof(char)*(strlen(tmp)+1));
		strcpy((*now).id, tmp);
		while(line[j] == ' ' || line[j] == ':') ++j; //skip the devide char ' '&':'
		
		//read second chapter
		i = 0;
		while(line[j] != ' '&&line[j] != '\n')
		{
			tmp[i++]=line[j++];
		}
		tmp[i]='\0';
		(*now).name = (char*) malloc(sizeof(char)*(strlen(tmp)+1));
		strcpy((*now).name, tmp);
		while(line[j] == ' ' || line[j] == ':') ++j; //skip the devide char ' '&':'
	}
	
	return;
}
