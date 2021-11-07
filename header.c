#include "mycheck.h"


void DeleteHeader(PHEADER del)
{
	//spj
	if(maxheader == 1)
	{
		headerbegin = NULL;
		maxheader = 0;
		noheader = true;
		free(del);
		return;
	}
	
	PHEADER now = NULL;
	PHEADER pre = NULL;
	PHEADER nxt = NULL;
	/*delete*/
	if((*del).code == 1) // headerbegin
	{
		nxt = (*del).nxtheader;
		
		(*nxt).lasheader = NULL;
		headerbegin = nxt;
	}
	else if((*del).code == maxheader) //headerend
	{
		pre = (*del).lasheader;
		
		(*pre).nxtheader = NULL;
	}
	else
	{
		pre = (*del).lasheader;
		nxt = (*del).nxtheader;
		
		(*pre).nxtheader = nxt;
		(*nxt).lasheader = pre;
	}
	free(del);
	return;
}

struct header* QueryHeaderID(char *targetheader)
{
	if(DEBUG) printf("debug: In function 'QueryHeaderID': targetheader = '%s'\n",targetheader);
	if(noheader == true)
	{
		if(DEBUG) printf("debug: In function 'QueryHeaderID': No Header already existed!\n");
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

struct header* QueryHeaderCode(int code)
{
	printf("temp: anyonealive>%d\n",code);
	if(DEBUG) printf("debug: In function 'QueryHeaderCode': targetcode = '%d'\n",code);
	if(noheader == true)
	{
		if(DEBUG) printf("debug: In function 'QueryHeaderCode': No Header already existed!\n");
		return NULL;
	}
	
	PHEADER nowheader = headerbegin;
	
	while(nowheader != NULL)
	{
		if((*nowheader).code == code) break;
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
		if(showcode == true) printf("%s(%d)", (*nowheader).id, (*nowheader).code);
		else printf("%s",(*nowheader).name);
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
			printf("(%d)",(*currentlist).code);
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
	
	headerbegin = NULL;
	
	if(strcmp(line,"\n") == 0 || strcmp(line," \n") == 0)
	{
		if(DEBUG) printf("debug: In function 'ReadAllHeader': no header!\n");
		noheader = true;
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
