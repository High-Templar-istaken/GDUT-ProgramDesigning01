#include "mycheck.h"

void HeaderDevide(char *source)
{
	if(DEBUG) printf("debug: source:%s",source);
	
	headerbegin = NULL;
	struct header *now = NULL;
	char tmp[1001];
	bool firstheader = true;
	
	int j = 0, i = 0;
	while(source[j] != '\n')
	{
		// create a new node
		if(firstheader != true)
		{
			(*now).nxtheader = (struct header*) malloc(sizeof(struct header));
			now = (*now).nxtheader;
			(*now).nxtheader = NULL;
		}
		if(firstheader == true)
		{
			now = (struct header*) malloc(sizeof(struct header));
			(*now).nxtheader = NULL;
			headerbegin = now;
			firstheader = false;
		}
		
		// read first chapter
		i = 0;
		while(source[j]!=':')
		{
			tmp[i++]=source[j++];
			if(source[j]==' '||source[j]=='\n')
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
		while(source[j] == ' ' || source[j] == ':') ++j; //skip the devide char ' '&':'
		
		//read second chapter
		i = 0;
		while(source[j] != ' '&&source[j] != '\n')
		{
			tmp[i++]=source[j++];
		}
		tmp[i]='\0';
		(*now).name = (char*) malloc(sizeof(char)*(strlen(tmp)+1));
		strcpy((*now).name, tmp);
		while(source[j] == ' ' || source[j] == ':') ++j; //skip the devide char ' '&':'
	}
	
	return;
}
