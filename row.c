#include "mycheck.h"

PROW InsertRow_FrontOf(PROW place, PROW tobenew) //place in the front of 'place'
{
	if(place == NULL)
	{
		(*tobenew).nxtrow = NULL;
		(*tobenew).lasrow = NULL;
		rowbegin = tobenew;
		rowend = tobenew;
		return tobenew;
	}
	
	if((*place).lasrow == NULL) //front of the list
	{
		//don't need to care about the front node
		(*tobenew).nxtrow = place; // don't need to take over the front node
		(*place).lasrow = tobenew;
		
		rowbegin = tobenew;
	}
	else
	{
		//care about the front node
		(*(*place).lasrow).nxtrow = tobenew;
		
		(*tobenew).lasrow = (*place).lasrow;
		(*tobenew).nxtrow = place;
		
		(*place).lasrow = tobenew;
	}
	return tobenew;
}

PROW InsertRow_BackOf(PROW place, PROW tobenew) //place in the back of 'place'
{
	//create now
	if(place == NULL)
	{
		(*tobenew).nxtrow = NULL;
		(*tobenew).lasrow = NULL;
		rowbegin = tobenew;
		rowend = tobenew;
		return tobenew;
	}
	
	if((*place).nxtrow == NULL) //back of the list
	{
		//don't need to care about the back node
		(*tobenew).lasrow = place; // don't need to take over the back node
		(*place).nxtrow = tobenew;
		
		rowend = tobenew;
	}
	else
	{
		//care about the back node
		(*(*place).nxtrow).lasrow = tobenew;
		
		(*tobenew).nxtrow = (*place).nxtrow;
		(*tobenew).lasrow = place;
		
		(*place).nxtrow = tobenew;
	}
	return tobenew;
}


PKEY QueryKeyHeader(PROW inrow, char *target)
{
	if(DEBUG) printf("debug: In function 'QueryKeyHeader': truekey=%d WHILE target=%s\n",(*inrow).truekey,target);
	PKEY nowkey = (*inrow).keybegin;
	while(nowkey != NULL)
	{
		if(strcmp((*nowkey).header, target) == 0) break;
		nowkey = (*nowkey).nxtkey;
	}
	return nowkey;
}

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
		if(showcode) printf("(%d):",(*nowrow).truekey);
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
			if(showcode) printf("code(%d):",(*nowrow).truekey);
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

PROW QueryRowTrueKey(int truekey)
{
	if(DEBUG) printf("debug: In function 'QueryRowTrueKey': targetcode = '%d'\n",truekey);
	if(rowbegin == NULL)
	{
		if(DEBUG) printf("debug: In function 'QueryRowTrueKey': No Header already existed!\n");
		return NULL;
	}
	
	PROW nowrow = rowbegin;
	
	while(nowrow != NULL)
	{
		if((*nowrow).truekey == truekey) break;
		nowrow = (*nowrow).nxtrow;
	}
	return nowrow;
}

void ReadAllRow(FILE *stream)
{
	// fill the in-program row
	int tmptruekey;
	char *line = NULL;
 	PROW nowrow = NULL;
 	PKEY nowkey = NULL;
 	
 	rowbegin = NULL;
 	rowend = NULL;
 	
	do
	{
		//get input
		fscanf(stream,"%d ",&tmptruekey);
		_templar_GetTightString_Getline(&line, stream);
		if(strcmp(line, "rowend\n") == 0) return;
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
		
		nowrow = (PROW) malloc(sizeof(struct row));
		(*nowrow).truekey = tmptruekey;
		(*nowrow).nxtrow = NULL;
		(*nowrow).lasrow = NULL;
		
		//create a new row
		RowDevide(line, nowrow);
		InsertRow_BackOf(rowend,nowrow);
		
		rowend = nowrow;
	}while(true);
	return;
}

PKEY InsertKey_BackOf(PKEY place, PKEY tobe, PROW inrow)
{
	if(place == NULL)
	{
		(*inrow).keyend = (*inrow).keybegin = tobe;
		return tobe;
	}
	// create a new key
	if((*place).nxtkey == NULL)
	{
		(*place).nxtkey = tobe;
		(*tobe).laskey = place;
		
		(*inrow).keyend = tobe;
	}
	else if((*place).laskey == NULL)
	{
		(*place).laskey = tobe;
		(*tobe).nxtkey = place;
		
		(*inrow).keybegin = tobe;
	}
	else
	{
		(*(*place).nxtkey).laskey = tobe;
		
		(*tobe).nxtkey = (*place).nxtkey;
		(*tobe).laskey = place;
		
		(*place).nxtkey = tobe;
	}
	return tobe;
}

void RowDevide(char *source, PROW inrow)
{
	if(DEBUG) printf("debug: In function 'RowDevide': source=%s\n",source);
	
	(*inrow).keyend = (*inrow).keybegin = NULL;
	if(strcmp(source,"\n") == 0 || strcmp(source," \n") == 0)
	{
		if(DEBUG) printf("debug: In function 'RowDevide': No key at all!\n");
		return;
	}
	
	PKEY now = NULL;
	char *tmp = (char*) malloc (sizeof(char)*MAX_INPUT_CACHE);
	
	int j = 0, i = 0;
	while(source[j] == ' ') ++j;
	while(source[j] != '\n')
	{
		now = (PKEY) malloc(sizeof(struct key));
		(*now).nxtkey = (*now).laskey = NULL;
		
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
		printf("tobeins: %s:%s\n",(*now).value,(*now).header);
		InsertKey_BackOf((*inrow).keyend , now, inrow);
		
		while(source[j] == ' ' || source[j] == ':') ++j; //skip the devide char ' '&':'
	}
	free(tmp);
	return;
}
