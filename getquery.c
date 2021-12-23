#include "mycheck.h"

bool getquery_equal(PROW nowrow,char *headerid,char *value)
{
	
	PHEADER nowheader = QueryHeaderID(headerid);
	
	if(nowheader == NULL)
	{
		printf("Error: header '%s' not existed!\n",headerid);
		exit(0);
	}
	
	PKEY nowkey = QueryKeyHeader(nowrow,headerid);
	if(nowkey == NULL)
	{
		if(ValueCmp((*nowheader).def,value) == 0) return true;
		return false;
	}
	else
	{
		if(ValueCmp((*nowkey).value,value) == 0) return true;
		return false;
	}
	
}

bool getquery_between(PROW nowrow, char *headerid,char *begin,char *end)
{
	bool can = true;
	if(strcmp(begin,".") != 0  && strcmp(end,".") != 0 && ValueCmp(begin,end) == 1)
	{
		char *tmp = begin;
		begin = end;
		end = tmp;
	}
	
	PHEADER nowheader = QueryHeaderID(headerid);
	if(nowheader == NULL)
	{
		printf("Error: Header '%s' unexisted!\n");
		exit(0);
	}
	PKEY nowkey = NULL;
	nowkey = QueryKeyHeader(nowrow,headerid);

	if(nowkey == NULL)
	{
		if(begin != ".")
		{
			if(ValueCmp((*nowheader).def,begin) == -1) return false;
		}
		if(end != ".")
		{
			if(ValueCmp((*nowheader).def,end) == 1) return false;
		}
	}
	else
	{
		if(begin != ".")
		{
			if(ValueCmp((*nowkey).value,begin) == -1) return false;
		}
		if(end != ".")
		{
			if(ValueCmp((*nowkey).value,end) == 1) return false;
		}
	}
	return true;
}

void getquery_argument(int argc, char *argv[])
{
	ReadTable("./.mycheck/working.txt");
	
	bool merge = true; //true - and
	bool nowbool = true;
	bool tmpbool = false;
	
	int begi = 2;
	if(strcmp(argv[2], "-merge=and") == 0)
	{
		merge = true;++begi;
	}
	else if (strcmp(argv[2], "-merge=or") == 0)
	{
		merge = false;++begi;
		printf("or\n");
	}
	
	for(int i = begi ; argv[i] != NULL ;++i)
	{
		if(strcmp(argv[i], "-merge=and") == 0 || strcmp(argv[i], "-merge=or") == 0)
		{
			printf("Error: '-merge' argument should be placed in front of the arguments!\n");
			exit(0);
		}
	}
	
	
	bool input = false;
	
	PROW nowrow = rowbegin;
	PROW nxtrow = NULL;
	while(nowrow != NULL)
	{
		printf("nxtrow\n");
		nxtrow = (*nowrow).nxtrow;
		
		nowbool = merge == false?false:true;
		
		for(int i = begi; argv[i] != NULL ;)
		{
			
			if(strcmp(argv[i], "-between") == 0)
			{
				if(argv[i+1] == NULL || argv[i+2] == NULL || argv[i+3] == NULL)
				{
					printf("Error: Wrong format of '-between' argument!\n");
					exit(0);
				}
				tmpbool = getquery_between(nowrow,argv[i+1],argv[i+2],argv[i+3]);
				i+=4;
			}
			else if(strcmp(argv[i], "-equal") == 0)
			{
				
				if(argv[i+1] == NULL || argv[i+2] == NULL)
				{
					printf("Error: Wrong format of '-between' argument!\n");
					exit(0);
				}
				tmpbool = getquery_equal(nowrow,argv[i+1],argv[i+2]);
				printf("%d\n",tmpbool);
				i+=3;
			}
			else
			{
				printf("Unknown operation '%s'!\n",argv[i]);
				exit(0);
			}
			
			if(merge == true)
			{
				nowbool = nowbool && tmpbool;
			}
			else
			{
				nowbool = nowbool || tmpbool;
			}
		}
		
		if(nowbool == false)  DeleteRow(nowrow,true);
		
		nowrow = nxtrow;
	}
	return;
}

int getquery(int argc,char *argv[])
{
	if(argv[2] == NULL)
	{
		printf("Error: Wrong format of 'query'!\n");
		exit(0);
	}
	getquery_argument(argc, argv);
	ReleasePrintTable();
	WriteTable("./.mycheck/working.txt");
	return 0;
}
