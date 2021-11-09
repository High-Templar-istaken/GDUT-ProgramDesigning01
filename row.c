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
			if(CheckHeaderUnmove(nowheader))
			{
				nowheader = (*nowheader).nxtheader;
				continue;
			}
			nowkey = QueryKeyHeader(nowrow,(*nowheader).id);
			
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

void DeleteRow(PROW del, bool truedelete)
{
	//spj
	if((*rowbegin).nxtrow == NULL)
	{
		rowbegin = NULL;
		rowend = NULL;
		free(del);
		return;
	}
	
	PROW now = NULL;
	PROW pre = NULL;
	PROW nxt = NULL;
	/*delete*/
	if(rowbegin == del) // rowbegin
	{
		nxt = (*del).nxtrow;
		
		(*nxt).lasrow = NULL;
		rowbegin = nxt;
	}
	else if(rowend == del) //headerend
	{
		pre = (*del).lasrow;
		
		(*pre).nxtrow = NULL;
		rowend = pre;
	}
	else
	{
		pre = (*del).lasrow;
		nxt = (*del).nxtrow;
		
		(*pre).nxtrow = nxt;
		(*nxt).lasrow = pre;
	}
	if(truedelete == true) free(del);
	else
	{
		(*del).lasrow = NULL;
		(*del).nxtrow = NULL;
	}
	return;
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
		
		if(DEBUG) printf("temp:get = %s\n",line);
		for(int i=0;i<strlen(line);++i)
		{
			if(line[i] != ' ' && line[i] != '\n') break;
			
			if(i == strlen(line) - 1) continue;
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
		
		ReadAllHeader_DevideNextHeaderInput(source, &j, &((*now).header), &((*now).value), tmp);
		
		InsertKey_BackOf((*inrow).keyend , now, inrow);
		
		while(source[j] == ' ' || source[j] == ':') ++j; //skip the devide char ' '&':'
	}
	free(tmp);
	return;
}
