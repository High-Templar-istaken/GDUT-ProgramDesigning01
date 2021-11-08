#include "mycheck.h"

void ReleaseShowAllRow()
{
	PROW nowrow = rowbegin;
	PHEADER nowheader = headerbegin;
	PKEY nowkey = NULL;
	if(rowbegin == NULL)
	{
		printf("THERE IS NO ROW\n");
		return;
	}
	
	while(nowrow != NULL)
	{
		nowheader = headerbegin;
		if(showcode) printf("(%d):",(*nowrow).code);
		while(nowheader != NULL)
		{
			nowkey = QueryKey(nowrow,(*nowheader).id);
			
			if(nowkey == NULL) printf("%s",(*nowheader).def); //There is no such key in this table
			else printf("%s",(*nowkey).value);
			
			putchar('\t');
			nowheader = (*nowheader).nxtheader;
		}
		putchar('\n');
		nowrow = (*nowrow).nxtrow;
	}
	return;
}

void DEBUGShowAllRow()
{
	if(DEBUG)
	{
		printf("-----debug----\nROW that read\n");
		if(rowbegin == NULL)
		{
			printf("----norow----\n");
			printf("---debugend---\n");
			return;
		}
		
		PROW nowrow = rowbegin;
		
		while(nowrow != NULL)
		{
			printf("In a new row:");
			if(showcode) printf("code(%d):",(*nowrow).code);
			PKEY nowkey = (*nowrow).keybegin;
			while(nowkey != NULL)
			{
				printf("header=%s WHILE Value=%s||", (*nowkey).header, (*nowkey).value);
				nowkey = (*nowkey).nxtkey;
			}
			putchar('\n');
			nowrow = (*nowrow).nxtrow;
		}
		
		printf("---debugend---\n");
	}
	return;
}

void ReadAllRow(FILE *stream)
{
	// fill the in-program row
	char *line = NULL;
 	PROW nowrow = NULL;
 	PKEY nowkey = NULL;
 	
 	rowbegin = NULL;
 	rowend = NULL;
 	
	do
	{
		//get input
		_templar_GetTightString_Getline(&line, stream);
		if(DEBUG) printf("debug: In function 'ReadAllRow': Row that read:%s\n", line,strlen(line));
		for(int i=0;i<strlen(line);++i)
		{
			if(line[i] != ' ' && line[i] != '\n')
			{
				break;
			}
			
			if(i == strlen(line) - 1)
			{
				if(rowbegin == NULL && DEBUG)  printf("debug: In function 'ReadAllRow': no row!\n");
				return;
			}
		}
		
		//create a new row
		if(rowbegin == NULL)
		{
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
		
		rowend = nowrow;
	}while(true);
	return;
}

struct key* RowDevide(char *source)
{
	if(DEBUG) printf("debug: In function 'RowDevide': source=%s",source);
	
	PKEY keybegin = NULL;
	PKEY now = NULL;
	char *tmp = (char*) malloc (sizeof(char)*MAX_INPUT_CACHE);
	bool firstkey = true;
	
	int j = 0, i = 0;
	while(source[j] == ' ') ++j;
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
				printf("Error: In function 'RowDevide' Wrong format in the header of Working list!\n");
				exit(0);
			}
		}
		tmp[i]='\0';
		if(strlen(tmp) == 0)
		{
			printf("Error: In function 'RowDevide' Empty Header ID!\n");
			exit(0);
		}
		(*now).header = (char*) malloc(sizeof(char)*(strlen(tmp)+1));
		strcpy((*now).header, tmp);
		while(source[j] == ':') ++j; //skip the devide char ' '&':'
		
		//read second chapter
		i = 0;
		while(source[j] != ' '&&source[j] != '\n')
		{
			tmp[i++]=source[j++];
		}
		tmp[i] = '\0';
		if(strlen(tmp) == 0)
		{
			tmp[0] = '#';
			tmp[1] = '\0';
		}
		(*now).value = (char*) malloc(sizeof(char)*(strlen(tmp)+1));
		strcpy((*now).value, tmp);
		
		while(source[j] == ' ' || source[j] == ':') ++j; //skip the devide char ' '&':'
	}
	free(tmp);
	return keybegin;
}
