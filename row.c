#include "mycheck.h"

void ShowAllRow()
{
	if(DEBUG)
	{
		printf("-----debug----\nROW that read\n");
		PROW nowrow = rowbegin;
		
		while(nowrow != NULL)
		{
			printf("In a new row:");
			PKEY nowkey = (*nowrow).keybegin;
			while(nowkey != NULL)
			{
				printf("header=%s WHILE Value=%s ||", (*nowkey).header, (*nowkey).value);
				nowkey = (*nowkey).nxtkey;
			}
			putchar('\n');
			nowrow = (*nowrow).nxtrow;
		}
		
		printf("---debugend---\n");
	}
}

void ReadAllRow(FILE *stream)
{
	// fill the in-program row
	char *line = NULL;
 	bool newrow = true;
 	PROW nowrow = NULL;
 	PKEY nowkey = NULL;
	do
	{
		//get input
		_templar_GetTightString_Getline(&line, stream);
		if(strcmp(line, "\n") == 0) break;
		
		//create a new row
		if(newrow == true)
		{
			newrow = false;
			
			nowrow = (PROW) malloc(sizeof(struct row));
			(*nowrow).nxtrow = NULL;
			(*nowrow).lasrow = NULL;
			(*nowrow).keybegin = NULL;
			rowbegin = nowrow;
		}
		else
		{
			(*nowrow).nxtrow = (PROW) malloc(sizeof(struct row));
			(*(*nowrow).nxtrow).lasrow = nowrow;
			nowrow = (*nowrow).nxtrow;
			
			(*nowrow).nxtrow = NULL;
			(*nowrow).keybegin = NULL;
		}
		(*nowrow).keybegin = RowDevide(line);
	}while(true);
}

struct key* RowDevide(char *source)
{
	if(DEBUG) printf("debug: In function 'RowDevide': source=%s",source);
	
	PKEY keybegin = NULL;
	PKEY now = NULL;
	char tmp[10001];
	bool firstkey = true;
	
	int j = 0, i = 0;
	while(source[j] != '\n')
	{
		// create a new key
		if(firstkey != true)
		{
			(*now).nxtkey = (PKEY) malloc(sizeof(struct key));
			(*(*now).nxtkey).laskey = now;
			now = (*now).nxtkey;
			(*now).nxtkey = NULL;
		}
		else
		{
			now = (PKEY) malloc(sizeof(struct key));
			(*now).nxtkey = NULL;
			(*now).laskey = NULL;
			keybegin = now;
			
			firstkey = false;
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
		(*now).header = (char*) malloc(sizeof(char)*(strlen(tmp)+1));
		strcpy((*now).header, tmp);
		while(source[j] == ' ' || source[j] == ':') ++j; //skip the devide char ' '&':'
		
		//read second chapter
		i = 0;
		while(source[j] != ' '&&source[j] != '\n')
		{
			tmp[i++]=source[j++];
		}
		tmp[i]='\0';
		(*now).value = (char*) malloc(sizeof(char)*(strlen(tmp)+1));
		strcpy((*now).value, tmp);
		while(source[j] == ' ' || source[j] == ':') ++j; //skip the devide char ' '&':'
	}
	
	return keybegin;
}
