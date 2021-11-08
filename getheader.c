#include "mycheck.h"

void moveheader(PHEADER moving,int targetcode,bool direct)// 0:forward ; 1:backward
/*0 means the replaced node will be pushed back*/
/*1 means the replaced node will be poped front*/
{
	//spj
	if(headerbegin == headerend) return;
	
	PHEADER now = NULL;
	/*delete*/
	DeleteHeader(moving, false);
	
	
	now = QueryHeaderCode(targetcode);
	if(now == NULL)
	{
		printf("WTF, how can you make that? Destination not found but the mission launched ?\n");
		exit(0);
	}
	if(direct == 0) InsertHeader_PushFrontOf(now, moving);
	if(direct == 1) InsertHeader_PushBackOf(now, moving);
}

/*
1: default
2: name
*/
void getheader_d_mode(char *filename, char *id)
{
	FILE *stream = fopen(filename,"r");
	ReadTable(stream);
	fclose(stream); stream = NULL;
	
	PHEADER tobe = QueryHeaderID(id);
	if(tobe == NULL)
	{
		printf("Error: In function 'getheader_d_mode': No such ID '%s'!",id);
		exit(0);
	}
	DeleteHeader(tobe,true);
	
	stream = fopen(filename,"w");
	WriteTable(stream);
	fclose(stream); stream = NULL;
}

void getheader_c_mode(char *filename, int changecode, char *id, char *newvalue)
{
	FILE *stream = fopen(filename,"r");
	ReadTable(stream);
	fclose(stream); stream = NULL;
	
	PHEADER tobe = QueryHeaderID(id);
	if(tobe == NULL)
	{
		printf("Error: In function 'getheader_c_mode': No such ID '%s'!",id);
		exit(0);
	}
	if(changecode == 1) //default
	{
		free((*tobe).def);
		(*tobe).def = newvalue;
	}
	else if(changecode == 2)
	{
		free((*tobe).def);
		(*tobe).name = newvalue;
	}
	
	stream = fopen(filename,"w");
	WriteTable(stream);
	fclose(stream); stream = NULL;
}

void getheader_m_mode(char *filename, char* id,char *offset)
{
	FILE *stream = fopen(filename,"r");
	ReadTable(stream);
	fclose(stream); stream = NULL;
	if(!isdigit(offset[0]))
	{
		if(offset[0] != ',' && offset[0] != '.')
		{
			printf("Error: In function 'getheader_m_mode': Direction mark of '%s' is not ',' or '.'\n", offset);
			exit(0);
		}
		if(offset[1] == '\0')
		{
			printf("Error: In function 'getheader_m_mode': No distance argument in '%s'!\n", offset);
			exit(0);
		} 
		
		PHEADER nowheader = QueryHeaderID(id);
		if(nowheader == NULL)
		{
			printf("Error: In function 'getheader_m_mode': HeaderID '%s' unexisted!\n", id);
			exit(0);
		}
		int step = _templar_StringToInt(offset+1), target;
		
		if(step == 0)
		{
			return;
		}
		
		if(offset[0] == ',') //forword
		{
			if((*nowheader).code == 1) return;
			target = (*nowheader).code - step;
			if(DEBUG) printf("debug: '%s' %d step(s) forward WHILE target site=%d\n",id,step,target);
			
			if(target <= 0) target = 1;
			if(target > (*headerend).code) target = (*headerend).code;
			moveheader(nowheader, target, 0);
		}
		else //backward
		{
			if((*nowheader).code == (*headerend).code) return;
			target = (*nowheader).code + step;
			if(DEBUG) printf("debug: '%s' %d step(s) forward WHILE target site=%d\n",id,step,target);
			
			if(target <= 0) target = 1;
			if(target > (*headerend).code) target = (*headerend).code;
			moveheader(nowheader, target, 1);
		}
	}
	else
	{
		printf("error: In function 'getheader_m_mode': No direction mark like ',' or '.' in argument '%s\n'",offset);
		exit(0);
	}
	stream = fopen(filename,"w");
	WriteTable(stream);
	fclose(stream); stream = NULL;
	
}

void getheader_n_mode(char *filename, char* id, char* displayname,char *def)
{
	if(DEBUG) printf("debug: stream=%s -> getheader_n_mode -> id=%s displayname=%s\n",filename,id,displayname);
	
	FILE *stream = fopen(filename,"r");
	ReadTable(stream);
	fclose(stream); stream = NULL;
	
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
	
	InsertHeader_PushBackOf(headerend, nowheader);
	
	DebugPrintTable();
	
	stream = fopen(filename,"w");
	WriteTable(stream);
	fclose(stream);
	stream = NULL;
}

void getheader_rn_mode(char *filename, char* id, char *newid)
{
	FILE *stream = fopen(filename,"r");
	ReadTable(stream);
	fclose(stream); stream = NULL;
	
	PHEADER nowheader;
	PROW nowrow = rowbegin;
	PKEY nowkey = NULL;
	
	nowheader = QueryHeaderID(id);
	if(nowheader == NULL)
	{
		printf("Error: In function 'getheader_rn_mode': No such header ID '%s'!\n",id);
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
	
	stream = fopen(filename,"w");
	WriteTable(stream);
	fclose(stream); stream = NULL;
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
			i+=2;
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
			i+=2;
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
			i+=2;
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
			++i;
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
			i+=2;
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
