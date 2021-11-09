#include "mycheck.h"

void getrow_n_mode(char *filename, int argc, char* argv[])
{
	PROW nowrow = NULL;
	nowrow = (PROW) malloc(sizeof(struct row));
	
	FILE *stream = fopen(filename,"r");
	ReadTable(stream);
	fclose(stream); stream = NULL;
	
	int argcnt=0;
	for(int i = 3; argv[i] != NULL ; ++i) ++argcnt;
	
	if(DEBUG) printf("debug: In function 'getrow_n_mode': cntinput=%d WHILE needinput=%d\n",argcnt,(*headerend).code);
	
	if(argcnt != (*headerend).code && argcnt != 0)
	{
		printf("ERROR: In function 'getrow_n_mode': input value(s) don't match the header(s) ONE BY ONE\n");
		exit(0);
	}
	
	(*nowrow).truekey = ++maxtruekey;
	(*nowrow).nxtrow = (*nowrow).lasrow = NULL;
	(*nowrow).keybegin = (*nowrow).keyend = NULL;
	
	PHEADER nowheader = headerbegin;
	PKEY nowkey = NULL;
	int cnt = 3;
	
	while(argcnt != 0 && nowheader != NULL)
	{
		nowkey = (PKEY) malloc(sizeof(struct key));
		(*nowkey).nxtkey = (*nowkey).laskey = NULL;
		
		(*nowkey).value = (char*) malloc(sizeof(char)*strlen(argv[cnt]));
		strcpy((*nowkey).value, argv[cnt]);
		++cnt;
		
		(*nowkey).header = (char*) malloc(sizeof(char)*strlen((*nowheader).id));
		strcpy((*nowkey).header, (*nowheader).id);
		
		InsertKey_BackOf((*nowrow).keyend, nowkey, nowrow);
		
		nowheader = (*nowheader).nxtheader;
	}
	
	InsertRow_BackOf(rowend, nowrow);
//	DebugPrintTable();
	stream = fopen(filename,"w");
	WriteTable(stream);
	fclose(stream); stream = NULL;
}

void getrow_d_mode(char *filename, char *code)
{
	int key = _templar_StringToInt(code);
	FILE *stream = fopen(filename,"r");
	ReadTable(stream);
	fclose(stream); stream = NULL;
	
	PROW nowrow = QueryRowTrueKey(key);
	if(nowrow == NULL)
	{
		printf("Error: No such truekey '%d'!\n",key);
		exit(0);
	}
	
	DeleteRow(nowrow, true);
	
	stream = fopen(filename,"w");
	WriteTable(stream);
	fclose(stream); stream = NULL;
}

void getrow_m_mode(char *filename, char *tobekey, char *placekey)
{
	if(placekey[0] != ',' && placekey[0] != '.')
	{
		printf("Error: No direction mark like ',' or '.' in argument '%s\n'",placekey);
		exit(0);
	}
	if(placekey[1] == '\0')
	{
		printf("Error: No target truekey in '%s'!\n",placekey);
		exit(0);
	}
	
	FILE *stream = fopen(filename,"r");
	ReadTable(stream);
	fclose(stream); stream = NULL;
	
	
	
	int tobetruekey = _templar_StringToInt(tobekey);
	int placetruekey = _templar_StringToInt(placekey+1);
	
	PROW tobe = QueryRowTrueKey(tobetruekey);
	PROW place = QueryRowTrueKey(placetruekey);
	
	
	if(tobe == NULL)
	{
		printf("Error: No such key '%d'!\n",tobetruekey);
		exit(0);
	}
	if(place == NULL)
	{
		printf("Error: No such key '%d'!\n",placetruekey);
		exit(0);
	}
	/*spj*/
	if(place == tobe) return;
	if(rowbegin == rowend) return;
	
	DeleteRow(tobe, false);
	
	if(placekey[0] == ',')
	{
		InsertRow_FrontOf(place,tobe);
	}
	else if(placekey[0] == '.')
	{
		InsertRow_BackOf(place,tobe);
	}
	
	stream = fopen(filename,"w");
	WriteTable(stream);
	fclose(stream); stream = NULL;
}

void getrow_r_mode(char *filename, char *key, char *headerid, char *value)
{
	int truekey = _templar_StringToInt(key);
	
	FILE *stream = fopen(filename,"r");
	ReadTable(stream);
	fclose(stream); stream = NULL;
	
	PROW nowrow = QueryRowTrueKey(truekey);
	PHEADER nowheader = QueryHeaderID(headerid);
	
	if(nowrow == NULL)
	{
		printf("Error: No such truekey '%s'!\n",key);
		exit(0);
	}
	if(nowheader == NULL)
	{
		printf("Error: No such header '%s'!\n",headerid);
		exit(0);
	}
	
	PKEY nowkey = QueryKeyHeader(nowrow, headerid);
	if(nowkey == NULL)
	{
		nowkey = (PKEY) malloc(sizeof(struct key));
		(*nowkey).header = headerid;
		(*nowkey).value = value;
		(*nowkey).nxtkey = (*nowkey).laskey = NULL;
		InsertKey_BackOf((*nowrow).keyend,nowkey,nowrow);
	}
	else
	{
		(*nowkey).value = value;
	}
	
	stream = fopen(filename,"w");
	WriteTable(stream);
	fclose(stream); stream = NULL;
}

void getrow_argument(int argc,char *argv[])
{
	for(int i = 2 ; argv[i] != NULL ; ++i)
	{
		if(strcmp(argv[i],"-n") == 0)
		{
			//operating both lists
			getrow_n_mode("./.mycheck/working.txt",argc,argv);
			getrow_n_mode("./.mycheck/storage.txt",argc,argv);
			return;
		}
		else if(strcmp(argv[i],"-d") == 0)
		{
			if(argv[i+1] == NULL)
			{
				printf("Error: In function 'getrow': Wrong format of argument '-d'\n");
				exit(0);
			}
			getrow_d_mode("./.mycheck/working.txt",argv[i+1]);
			getrow_d_mode("./.mycheck/storage.txt",argv[i+1]);
			return;
		}
		else if(strcmp(argv[i],"-m") == 0)
		{
			if(argv[i+1] == NULL || argv[i+2] == NULL)
			{
				printf("Error: In function 'getrow': Wrong format of argument '-d'\n");
				exit(0);
			}
			getrow_m_mode("./.mycheck/working.txt",argv[i+1],argv[i+2]);
			getrow_m_mode("./.mycheck/storage.txt",argv[i+1],argv[i+2]);
			return;
		}
		
		else if(strcmp(argv[i],"-r") == 0)
		{
			if(argv[i+1] == NULL || argv[i+2] == NULL || argv[i+3] == NULL)
			{
				printf("Error: In function 'getrow': Wrong format of argument '-c'\n");
				exit(0);
			}
			
			getrow_r_mode("./.mycheck/working.txt",argv[i+1],argv[i+2],argv[i+3]);
			getrow_r_mode("./.mycheck/storage.txt",argv[i+1],argv[i+2],argv[i+3]);
			return;
		}
		
		else
		{
			printf("Error: In function 'getrow': Unknown argument '%s'\n", argv[i]);
			exit(0);
		}
	}
}

int getrow(int argc,char *argv[])
{
	getrow_argument(argc, argv);
	
	return 0;
}
