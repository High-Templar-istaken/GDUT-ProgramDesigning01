#include "mycheck.h"

/*
1: default
2: name
*/
void getheader_d_mode(char *filename, char *id)
{
	ReadTable(filename);
	
	PHEADER tobe = QueryHeaderID(id);
	if(tobe == NULL)
	{
		printf("Error: In function 'getheader_d_mode': No such ID '%s'!",id);
		exit(0);
	}
	if(CheckHeaderLegitByPointer(tobe))
	{
		printf("Error: Deleting header begin with '#' or '-' is not allowed!\n");
		exit(0);
	}
	DeleteHeader(tobe,true);
	
	WriteTable(filename);
}

void getheader_c_mode(char *filename, int changecode, char *id, char *newvalue)
{
	ReadTable(filename);
	
	PHEADER tobe = QueryHeaderID(id);
	
	if(tobe == NULL)
	{
		printf("Error: In function 'getheader_c_mode': No such ID '%s'!",id);
		exit(0);
	}
	if(CheckHeaderLegitByPointer(tobe))
	{
		printf("Error: Deleting header begin with '#' or '-' is not allowed!\n");
		exit(0);
	}
	
	if(changecode == 1) //default
	{
		free((*tobe).def);
		(*tobe).def = newvalue;
	}
	else if(changecode == 2)
	{
		free((*tobe).name);
		(*tobe).name = newvalue;
	}
	
	WriteTable(filename);
}

void getheader_m_mode(char *filename, char* id,char *offset)
{
	if(offset[0] != ',' && offset[0] != '.')
	{
		printf("No direction mark like ',' or '.' in argument '%s\n'",offset);
		exit(0);
	}
	if(offset[1] == '\0')
	{
		printf("Error: In function 'getheader_m_mode': No distance argument in '%s'!\n", offset);
		exit(0);
	} 
	ReadTable(filename);
		
	PHEADER nowheader = QueryHeaderID(id);
	PHEADER place = QueryHeaderID(offset+1);
	if(nowheader == NULL)
	{
		printf("Error: In function 'getheader_m_mode': HeaderID '%s' unexisted!\n", id);
		exit(0);
	}
	if(place == NULL)
	{
		printf("Error: Unexisted header '%s'!\n",offset+1);
		exit(0);
	}
	
	if(CheckHeaderLegitByPointer(place) || CheckHeaderLegitByPointer(nowheader))
	{
		printf("Error: Deleting header begin with '#' or '-' is not allowed!\n");
		exit(0);
	}
	
	/*spj*/
	if(place == nowheader) return;
	if(headerbegin == headerend) return;
	
	DeleteHeader(nowheader, false);
	
	if(offset[0] == ',') //forword
	{
		InsertHeader_FrontOf(place, nowheader);
	}
	else //backward
	{
		InsertHeader_BackOf(place, nowheader);
	}
	
	WriteTable(filename);
}

void getheader_n_mode(char *filename, char* id, char* displayname,char *def)
{
	if(DEBUG) printf("debug: stream=%s -> getheader_n_mode -> id=%s displayname=%s\n",filename,id,displayname);
	if(CheckHeaderLegitByString(id))
	{
		printf("Error: Headerid %s is not allowed!(should only contains numbers or characters or dash '-_')\n",id);
		exit(0);
	}
	
	ReadTable(filename);
	
	if(QueryHeaderID(id) != NULL)
	{
		printf("Error: In function 'getheader_n_mode': new header's ID '%s' already existed!\n",id);
		exit(0);
	}
	
	PHEADER nowheader = (PHEADER) malloc (sizeof(struct header));
	
	(*nowheader).nxtheader = (*nowheader).lasheader = NULL;
	(*nowheader).id = id;
	(*nowheader).name = displayname;
	(*nowheader).def = def;
	
	InsertHeader_BackOf(headerend, nowheader);
	
	DebugPrintTable();
	
	WriteTable(filename);
}

void getheader_rn_mode(char *filename, char* id, char *newid)
{
	ReadTable(filename);
	
	PHEADER nowheader;
	PROW nowrow = rowbegin;
	PKEY nowkey = NULL;
	
	nowheader = QueryHeaderID(id);
	if(nowheader == NULL)
	{
		printf("Error: In function 'getheader_rn_mode': No such header ID '%s'!\n",id);
		exit(0);
	}
	if(CheckHeaderLegitByPointer(nowheader))
	{
		printf("Error: Headerid begin with '#' or '-' is not allowed!\n");
		exit(0);
	}
	if(QueryHeaderID(newid) != NULL)
	{
		printf("Error: You can't rename a header as an already existed ID!\n");
		exit(0);
	}
	
	free((*nowheader).id);
	(*nowheader).id = newid;
	
	while(nowrow != NULL)
	{
		nowkey = QueryKeyHeader(nowrow,id);
		if(nowkey == NULL)
		{
			if(DEBUG) printf("debug: In row(%d): No such key!\n",(*nowrow).truekey);
			continue;
		}
		if(DEBUG) printf("In row(%d): KEY FOUNDED, value=%s\n",(*nowrow).truekey,(*nowkey).value);
		
		free((*nowkey).header);
		(*nowkey).header = newid;
		nowrow = (*nowrow).nxtrow;
	}
	
	WriteTable(filename);
}

void getheader_argument(int argc,char *argv[])
{
	for(int i = 2 ; argv[i] != NULL ; ++i)
	{
		if(strcmp(argv[i],"-n") == 0)
		{
			if(argv[i+1] == NULL || argv[i+2] == NULL)
			{
				printf("Error: In function 'getheader': Wrong format of argument '-n'\n");
				exit(0);
			}
			//operating both lists
			getheader_n_mode("./.mycheck/working.txt",argv[i+1],argv[i+2],(argv[i+3] == '\0')?"#":argv[i+3]);
			getheader_n_mode("./.mycheck/storage.txt",argv[i+1],argv[i+2],(argv[i+3] == '\0')?"#":argv[i+3]);
			return;
		}
		else if(strcmp(argv[i],"-c=default") == 0 || strcmp(argv[i],"-c=name") == 0)
		{
			if(argv[i+1] == NULL || argv[i+2] == NULL)
			{
				printf("Error: In function 'getheader': Wrong format of argument '-c'\n");
				exit(0);
			}
			int changecode = 0;
			if(strcmp(argv[i],"-c=default") == 0) changecode = 1;
			else if(strcmp(argv[i],"-c=name") == 0) changecode = 2;
			
			getheader_c_mode("./.mycheck/working.txt",changecode,argv[i+1],argv[i+2]);
			getheader_c_mode("./.mycheck/storage.txt",changecode,argv[i+1],argv[i+2]);
			return;
		}
		else if(strcmp(argv[i],"-m") == 0)
		{
			if(argv[i+1] == NULL || argv[i+2] == NULL)
			{
				printf("Error: In function 'getheader': Wrong format of argument '-m'\n");
				exit(0);
			}
			getheader_m_mode("./.mycheck/working.txt",argv[i+1],argv[i+2]);
			getheader_m_mode("./.mycheck/storage.txt",argv[i+1],argv[i+2]);
			return;
		}
		else if(strcmp(argv[i],"-d") == 0)
		{
			if(argv[i+1] == NULL)
			{
				printf("Error: In function 'getheader': Wrong format of argument '-d'\n");
				exit(0);
			}
			getheader_d_mode("./.mycheck/working.txt",argv[i+1]);
			getheader_d_mode("./.mycheck/storage.txt",argv[i+1]);
			return;
		}
		else if(strcmp(argv[i],"-rn") == 0)
		{
			if(argv[i+1] == NULL || argv[i+2] == NULL)
			{
				printf("Error: In function 'getheader': Wrong format of argument '-r'\n");
				exit(0);
			}
			getheader_rn_mode("./.mycheck/working.txt",argv[i+1],argv[i+2]);
			getheader_rn_mode("./.mycheck/storage.txt",argv[i+1],argv[i+2]);
			return;
		}
		else
		{
			printf("Error: In function 'getheader': Unknown argument '%s'\n", argv[i]);
			exit(0);
		}
	}
}

int getheader(int argc,char *argv[])
{
	getheader_argument(argc, argv);
	
	return 0;
}
