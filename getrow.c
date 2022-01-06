#include "mycheck.h"

void getrow_n_mode(char *filename, int argc, char* argv[])
{
	PROW nowrow = NULL;
	nowrow = (PROW) malloc(sizeof(struct row));
	
	ReadTable(filename);
	
	int argcnt=0;
	for(int i = 3; argv[i] != NULL ; ++i)
	{
		if(_templar_HaveColon(argv[i]) == true)
		{
			printf("Error: Colon ':' was not allowed in the key!\n");
			exit(0);
		}
		++argcnt;
	}
	
	if(DEBUG) printf("debug: In function 'getrow_n_mode': cntinput=%d WHILE needinput=%d\n",argcnt,totheader);
	
	if(argcnt != totheader-1 && argcnt != 0)
	{
		printf("ERROR: In function 'getrow_n_mode': input value(s) don't match the header(s) ONE BY ONE\n");
		printf("Needed %d but inputed %d\n",totheader-1,argcnt);
		exit(0);
	}
	
	(*nowrow).truekey = ++maxtruekey;
	(*nowrow).nxtrow = (*nowrow).lasrow = NULL;
	(*nowrow).keybegin = (*nowrow).keyend = NULL;
	
	PHEADER nowheader = headerbegin;
	PKEY nowkey = NULL;
	int cnt = 3;
	
	
	/*
		if argcnt == 0
		This row will contain nothing and the loop will be ended safely
	*/
	while(argcnt != 0 && nowheader != NULL)
	{
		if(CheckHeaderLegitByPointer(nowheader))
		{
			nowheader = (*nowheader).nxtheader;
			continue;
		}
		
		nowkey = (PKEY) malloc(sizeof(struct key));
		(*nowkey).nxtkey = (*nowkey).laskey = NULL;
		
		if(strcmp(argv[cnt] , ".") != 0)
		{
			(*nowkey).value = (char*) malloc(sizeof(char)*strlen(argv[cnt]));
			strcpy((*nowkey).value, argv[cnt]);
			
			(*nowkey).header = (char*) malloc(sizeof(char)*strlen((*nowheader).id));
			strcpy((*nowkey).header, (*nowheader).id);
			
			InsertKey_BackOf((*nowrow).keyend, nowkey, nowrow);
		}
		
		++cnt;
		
		nowheader = (*nowheader).nxtheader;
	}
	
	InsertRow_BackOf(rowend, nowrow);
//	DebugPrintTable();
	WriteTable(filename);
}

void getrow_d_mode(char *filename, char *code)
{
	int key = _templar_StringToNumber(code);
	ReadTable(filename);
	
	PROW nowrow = QueryRowTrueKey(key);
	if(nowrow == NULL)
	{
		printf("Error: No such truekey '%d'!\n",key);
		exit(0);
	}
	
	DeleteRow(nowrow, true);
	
	WriteTable(filename);
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
	
	ReadTable(filename);
	
	
	
	int tobetruekey = _templar_StringToNumber(tobekey);
	int placetruekey = _templar_StringToNumber(placekey+1);
	
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
	
	WriteTable(filename);
}

void getrow_r_mode(char *filename, char *key, char *headerid, char *value)
{
	if(_templar_HaveColon(value) == true)
	{
		printf("Error: Colon ':' was not allowed in the key!\n");
		exit(0);
	}
	int truekey = _templar_StringToNumber(key);
	
	ReadTable(filename);
	
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
	
	WriteTable(filename);
}

void getrow_kd_mode(char *filename, char *truekey, char *headerid)
{
	ReadTable(filename);
	
	if(_templar_JudgeStringIsNumber(truekey) == false)
	{
		printf("Error: '%s' is not a number\n");
		exit(0);
	}
	
	PROW inrow = QueryRowTrueKey(_templar_StringToNumber(truekey));
	PHEADER inheader = QueryHeaderID(headerid);
	PKEY inkey = NULL;
	if(inrow == NULL)
	{
		printf("Error: No such row '%s'!\n",truekey);
		exit(0);
	}
	if(inheader == NULL)
	{
		printf("Error: No such header '%s'!\n",headerid);
		exit(0);
	}
	inkey = QueryKeyHeader(inrow,headerid);
	if(inkey == NULL)
	{
		printf("Error: No such key %s:%s!\n",truekey,headerid);
		exit(0);
	}
	DeleteKey(inkey,inrow);
	
	WriteTable(filename);
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
		
		else if(strcmp(argv[i],"-kd") == 0)
		{
			if(argv[i+1] == NULL || argv[i+2] == NULL)
			{
				printf("Error: In function 'getrow': Wrong format of argument '-kd'\n");
				exit(0);
			}
			
			getrow_kd_mode("./.mycheck/working.txt",argv[i+1],argv[i+2]);
			getrow_kd_mode("./.mycheck/storage.txt",argv[i+1],argv[i+2]);
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
