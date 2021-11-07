#include "mycheck.h"

struct header* QueryHeader(char *targetheader)
{
	if(noheader == true)
	{
		if(DEBUG) printf("debug: In function 'debug': No Header!\n");
		return NULL;
	}
	
	PHEADER nowheader = headerbegin;
	
	while(nowheader != NULL)
	{
		if(strcmp((*nowheader).id, targetheader) == 0) break;
		nowheader = (*nowheader).nxtheader;
	}
	return nowheader;
}

void ReleaseShowAllHeader()
{
	PROW nowrow = rowbegin;
	PHEADER nowheader = headerbegin;
	PKEY nowkey = NULL;
	
	if(noheader == true)
	{
		printf("No Header!\n");
		return;
	}
	
	while(nowheader != NULL)
	{
		printf("%s",(*nowheader).name);
		if(showcode == true) printf("(%d)",(*nowheader).code);
		nowheader = (*nowheader).nxtheader;
		putchar('\t');
	}
	putchar('\n');
}

void DEBUGShowAllHeader()
{
	if(DEBUG)
	{
		printf("-----debug----\nHEADER that read\n");
		if(noheader == true)
		{
			printf("No Header!\n");
			printf("---debugend---\n");
			return;
		}
		
		PHEADER currentlist = headerbegin;
		while(currentlist != NULL)
		{
			printf("id:%s WHILE name=%s", (*currentlist).id , (*currentlist).name);
			if(showcode) printf("(%d)",(*currentlist).code);
			currentlist = (*currentlist).nxtheader;
			putchar('\n');
		}
		printf("---debugend---\n");
	}
}

void ReadAllHeader(FILE *stream)
{
	char *line = NULL;
	_templar_GetTightString_Getline(&line, stream);//firstline end with '\n'
	
	if(strcmp(line,"\n") == 0 || strcmp(line," \n") == 0)
	{
		if(DEBUG) printf("debug: In function 'ReadAllHeader': no header!\n");
		noheader = true;
		headerbegin = NULL;
	}
	else noheader = false;
	
	if(DEBUG) printf("debug: In function 'ReadAllHeader': source=%s",line);
	
	PHEADER now = NULL;
	char *tmp = (char*) malloc (sizeof(char)*MAX_INPUT_CACHE);
	bool firstheader = true;
	
	int j = 0, i = 0;
	while(line[j] == ' ') ++j;
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
		
		// read first line
		i = 0;
		while(line[j]!=':')
		{
			tmp[i++]=line[j++];
			if(line[j]==' '||line[j]=='\n')
			{
				printf("Error: In function 'ReadAllHeader' Wrong format in the header of Working list!\n");
				exit(0);
			}
		}
		tmp[i]='\0';
		if(strlen(tmp) == 0)
		{
			printf("Error: In function 'ReadAllHeader' Empty Header ID!\n");
			exit(0);
		}
		(*now).id = (char*) malloc(sizeof(char)*(strlen(tmp)+1));
		strcpy((*now).id, tmp);
		while(line[j] == ':') ++j; //skip the devide char ' '&':'
		
		//read second chapter
		i = 0;
		while(line[j] != ' ' && line[j] != '\n')
		{
			tmp[i++]=line[j++];
		}
		tmp[i]='\0';
		(*now).name = (char*) malloc(sizeof(char)*(strlen(tmp)+1));
		strcpy((*now).name, tmp);
		while(line[j] == ' ' || line[j] == ':') ++j; //skip the devide char ' '&':'
	}
	
	free(tmp);
	return;
}
