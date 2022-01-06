#include "mycheck.h"

bool CheckHeaderLegitByPointer(PHEADER now)
{
	return CheckHeaderLegitByString((*now).id);
}


bool CheckHeaderLegitByString(char* now) // true = not legit
{
	for(int i=0;i<strlen(now);++i)
	{
		if(!(('0'<=now[i]&&now[i]<='9')||('a'<=now[i]&&now[i]<='z')||('A'<=now[i]&&now[i]<='Z')||(now[i]=='_')))
		{
			return true;
		}
	}
	return false;
}

PHEADER InsertHeader_FrontOf(PHEADER place, PHEADER tobenew) //place in the front of 'place'
{
	++totheader;
	if(place == NULL)
	{
		(*tobenew).nxtheader = NULL;
		(*tobenew).lasheader = NULL;
		headerbegin = tobenew;
		headerend = tobenew;
		return tobenew;
	}
	
	if((*place).lasheader == NULL) //front of the list
	{
		//don't need to care about the front node
		(*tobenew).nxtheader = place; // don't need to take over the front node
		(*place).lasheader = tobenew;
		
		headerbegin = tobenew;
	}
	else
	{
		//care about the front node
		(*(*place).lasheader).nxtheader = tobenew;
		
		(*tobenew).lasheader = (*place).lasheader;
		(*tobenew).nxtheader = place;
		
		(*place).lasheader = tobenew;
	}
	return tobenew;
}

PHEADER InsertHeader_BackOf(PHEADER place, PHEADER tobenew) //place in the back of 'place'
{
	++totheader;
	//create now
	if(place == NULL)
	{
		(*tobenew).nxtheader = NULL;
		(*tobenew).lasheader = NULL;
		headerbegin = tobenew;
		headerend = tobenew;
		return tobenew;
	}
	
	if((*place).nxtheader == NULL) //back of the list
	{
		//don't need to care about the back node
		(*tobenew).lasheader = place; // don't need to take over the back node
		(*place).nxtheader = tobenew;
		
		headerend = tobenew;
	}
	else
	{
		//care about the back node
		(*(*place).nxtheader).lasheader = tobenew;
		
		(*tobenew).nxtheader = (*place).nxtheader;
		(*tobenew).lasheader = place;
		
		(*place).nxtheader = tobenew;
	}
	return tobenew;
}

void DeleteHeader(PHEADER del, bool truedelete)
{
	--totheader;
	//spj
	if((*headerbegin).nxtheader == NULL)
	{
		headerbegin = NULL;
		headerend = NULL;
		if(truedelete == true) free(del);
		return;
	}
	
	PHEADER now = NULL;
	PHEADER pre = NULL;
	PHEADER nxt = NULL;
	/*delete*/
	if(headerbegin == del) // headerbegin
	{
		nxt = (*del).nxtheader;
		
		(*nxt).lasheader = NULL;
		headerbegin = nxt;
	}
	else if(headerend == del) //headerend
	{
		pre = (*del).lasheader;
		
		(*pre).nxtheader = NULL;
		headerend = pre;
	}
	else
	{
		pre = (*del).lasheader;
		nxt = (*del).nxtheader;
		
		(*pre).nxtheader = nxt;
		(*nxt).lasheader = pre;
	}
	if(truedelete == true) free(del);
	else
	{
		(*del).lasheader = NULL;
		(*del).nxtheader = NULL;
	}
	return;
}

PHEADER QueryHeaderID(char *targetheader)
{
	if(DEBUG) printf("debug: In function 'QueryHeaderID': targetheader = '%s'\n",targetheader);
	if(headerbegin == NULL)
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

void ReleaseShowAllHeader()
{
	PROW nowrow = rowbegin;
	PHEADER nowheader = headerbegin;
	PKEY nowkey = NULL;
	
	if(CheckHeaderLegitByPointer(headerend))
	{
		printf("No Header!\n");
		return;
	}
	
	if(showcode == true) printf("idH:");
	while(nowheader != NULL)
	{
		if(CheckHeaderLegitByPointer(nowheader))
		{
			nowheader = (*nowheader).nxtheader;
			continue;
		}
		if(showcode == true) printf("%s", (*nowheader).id);
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
		if(headerbegin == NULL)
		{
			printf("No Header!\n");
			printf("---debugend---\n");
			return;
		}
		
		PHEADER currentlist = headerbegin;
		while(currentlist != NULL)
		{
			printf("id:%s WHILE name=%s AND default=%s\n", (*currentlist).id , (*currentlist).name, (*currentlist).def);
			currentlist = (*currentlist).nxtheader;
			putchar('\n');
		}
		printf("---debugend---\n");
	}
}

void ReadAllHeader_DevideNextHeaderInput(char *line, int *j, char **first, char **second, char *tmp)
//**tmp: avoiding too many malloc requests
{
	// read first chapter
	int i = 0;
	for(int k=0;k<strlen(line);++k)
	{
		if(line[k] != ' ' && line[k] != '\n') break;
		if(k == strlen(line)-1) return;
	}
	
	while(line[(*j)] != ':')
	{
		tmp[i++]=line[(*j)++];
		if(line[(*j)]==' '||line[(*j)]=='\n')
		{
			printf("Error: In function 'ReadAllHeader_DevideNextHeaderInput' Wrong format in the header of Working list!\n");
			exit(0);
		}
	}
	tmp[i]='\0';
	if(strlen(tmp) == 0)
	{
		printf("Error: In function 'ReadAllHeader' Empty Header ID!\n");
		exit(0);
	}
	(*first) = (char*) malloc(sizeof(char)*(strlen(tmp)+1));
	strcpy((*first), tmp);
	while(line[(*j)] == ':') ++(*j); //skip the devide char ' '&':'
	
	//read second chapter
	i = 0;
	while(line[(*j)] != ' ' && line[(*j)] != '\n')
	{
		tmp[i++]=line[(*j)++];
	}
	tmp[i]='\0';
	(*second) = (char*) malloc(sizeof(char)*(strlen(tmp)+1));
	strcpy((*second), tmp);
}

void ReadAllHeader_HeaderPart(FILE *stream)
{
	char *line = NULL;
	totheader = 0;
	// ReadAllHeader -> Read header
	_templar_GetTightString_Getline(&line, stream);//firstline end with '\n'
	
	headerbegin = NULL;
	headerend = NULL;
	
	if(strcmp(line,"\n") == 0 || strcmp(line," \n") == 0)
	{
		if(DEBUG) printf("debug: In function 'ReadAllHeader_HeaderPart': no header!\n");
		printf("There is no header. The table is probably empty!\n");
		return;
	}
	
	if(DEBUG) printf("debug: In function 'ReadAllHeader_HeaderPart': source=%s",line);
	
	PHEADER las = headerbegin;
	PHEADER now = NULL;
	char *tmp = (char*) malloc (sizeof(char)*MAX_INPUT_CACHE);
	
	int j = 0;
	while(line[j] == ' ') ++j;
	
	
	while(line[j] != '\n')
	{
		now = (struct header*) malloc(sizeof(struct header));
		(*now).nxtheader = NULL;
		(*now).lasheader = NULL;
		(*now).def = "#";
		
		ReadAllHeader_DevideNextHeaderInput(line, &j, &((*now).id), &((*now).name), tmp);
		
		InsertHeader_BackOf(headerend, now);
		while(line[j] == ' ' || line[j] == ':') ++j; //skip the devide char ' '&':'
	}
	// ReadAllHeader -> Read default
	
	free(tmp);
}

void ReadAllHeader_DefaultPart(FILE *stream)
{
	char *line = NULL;
	PHEADER nowheader = NULL;
	// ReadAllHeader -> Read header
	_templar_GetTightString_Getline(&line, stream);//firstline end with '\n'
	
	if(DEBUG) printf("debug: In function '_templar_GetTightString_Getline': source=%s",line);
	
	char *tmpid = NULL, *tmpdef = NULL;
	char *tmp = (char*) malloc (sizeof(char)*MAX_INPUT_CACHE);
	
	int j = 0, i = 0;
	while(line[j] == ' ') ++j;
	
	while(line[j] != '\n')
	{
		// read second line
		ReadAllHeader_DevideNextHeaderInput(line, &j, &tmpid, &tmpdef, tmp);
		
		nowheader = QueryHeaderID(tmpid);
		if(nowheader == NULL)
		{
			printf("Error: In function 'ReadAllHeader_DefaultPart' No such Header ID!\n");
			exit(0);
		}
		
		(*nowheader).def = tmpdef;
		while(line[j] == ' ' || line[j] == ':') ++j; //skip the devide char ' '& ':'
	}
	// ReadAllHeader -> Read default
	
	free(tmp);
}

void ReadAllHeader_TrueKeyPart(FILE *stream)
{
	fscanf(stream,"%d\n",&maxtruekey);
	return;
}

void ReadAllHeader(FILE *stream)
{
	ReadAllHeader_TrueKeyPart(stream);
	ReadAllHeader_HeaderPart(stream);
	ReadAllHeader_DefaultPart(stream);
	return;
}
