#include "mycheck.h"

void moveheader(PHEADER moving,int targetcode,bool direct)// 0:forward ; 1:backward
/*0 means the replaced node will be pushed back*/
/*1 means the replaced node will be poped front*/
{
	//spj
	if(maxheader == 1) return;
	
	PHEADER now = NULL;
	/*delete*/
	DeleteHeader(moving);
	DebugPrintTable();
	
	now = QueryHeaderCode(targetcode);
	if(now == NULL)
	{
		printf("WTF, how can you make that? Destination not found but the mission launched ?\n");
		exit(0);
	}
	
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
			if(target > maxheader) target = maxheader;
			moveheader(nowheader, target, 0);
		}
		else //backward
		{
			if((*nowheader).code == maxheader) return;
			target = (*nowheader).code + step;
			if(DEBUG) printf("debug: '%s' %d step(s) forward WHILE target site=%d\n",id,step,target);
			
			if(target <= 0) target = 1;
			if(target > maxheader) target = maxheader;
			moveheader(nowheader, target, 1);
		}
	}
	else
	{
		int step = _templar_StringToInt(offset);
		int target = step;
		if(DEBUG) printf("debug: '%s' move to %d\n",id,target);
	}
}

void getheader_n_mode(char *filename, char* id, char* displayname)
{
	if(DEBUG) printf("debug: stream=%s -> getheader_n_mode -> id=%s displayname=%s\n",filename,id,displayname);
	
	FILE *stream = fopen(filename,"r");
	ReadTable(stream);
	if(QueryHeaderID(id) != NULL)
	{
		printf("Error: In function 'getheader_n_mode': new header's ID '%s' already existed!\n",id);
		exit(0);
	}
	
	if(headerbegin == NULL)
	{
		headerbegin = (PHEADER) malloc(sizeof(struct header));
		(*headerbegin).nxtheader = (*headerbegin).lasheader = NULL;
		(*headerbegin).id = id;
		(*headerbegin).name = displayname;
		fclose(stream);
		fclose(stream);
		stream = fopen(filename,"w");
		WriteTable(stream);
		fclose(stream);
		stream = NULL;
		return;
	}
	
	PHEADER nowheader = headerbegin;
	while((*nowheader).nxtheader != NULL) nowheader = (*nowheader).nxtheader;
	
	(*nowheader).nxtheader = (PHEADER) malloc(sizeof(struct header));
	(*((*nowheader).nxtheader)).lasheader = nowheader;
	nowheader = (*nowheader).nxtheader;
	(*nowheader).nxtheader = NULL;
	(*nowheader).id = id;
	(*nowheader).name = displayname;
	
	DebugPrintTable();
	fclose(stream);
	stream = fopen(filename,"w");
	WriteTable(stream);
	fclose(stream);
	stream = NULL;
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
			getheader_n_mode("./.mycheck/working.txt",argv[i+1],argv[i+2]);
			getheader_n_mode("./.mycheck/storage.txt",argv[i+1],argv[i+2]);
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
//			getheader_m_mode("./.mycheck/storage.txt",argv[i+1],argv[i+2]);
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
//			arg1 = argv[i+1];
			++i;
		}
		else if(strcmp(argv[i],"-r") == 0)
		{
			if(argv[i+1] == NULL || argv[i+2] == NULL)
			{
				printf("Error: In function 'getheader': Wrong format of argument '-r'\n");
				exit(0);
			}
//			arg1 = argv[i+1];
//			arg2 = argv[i+2];
			i+=2;
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
