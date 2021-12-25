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
	if(strcmp(begin,".") != 0  && strcmp(end,".") != 0 && ValueCmp(begin,end) == 1)
	{
		char *tmp = begin;
		begin = end;
		end = tmp;
	}
	
	PHEADER nowheader = QueryHeaderID(headerid);
	if(nowheader == NULL)
	{
		printf("Error: Header '%s' unexisted!\n",headerid);
		exit(0);
	}
	PKEY nowkey = NULL;
	nowkey = QueryKeyHeader(nowrow,headerid);

	if(nowkey == NULL)
	{
		if(strcmp(begin,".")!=0)
		{
			if(ValueCmp((*nowheader).def,begin) == -1) return false;
		}
		if(strcmp(end,".")!=0)
		{
			if(ValueCmp((*nowheader).def,end) == 1) return false;
		}
	}
	else
	{
		if(strcmp(begin,".")!=0)
		{
			if(ValueCmp((*nowkey).value,begin) == -1) return false;
		}
		if(strcmp(end,".")!=0)
		{
			if(ValueCmp((*nowkey).value,end) == 1) return false;
		}
	}
	return true;
}

void getquery_argument(int argc, char *argv[])
{
	ReadTable("./.mycheck/working.txt");
	
	bool tmpbool = false;
	
	PROW nowrow = rowbegin;
	PROW nxtrow = NULL;
	
	struct VLA Function;
	Function.arr = NULL;
	
	while(nowrow != NULL)
	{
		nxtrow = (*nowrow).nxtrow;
		
		_templar_vla_clear(&Function);
		_templar_vla_create(&Function);
		
		for(int i = 2; argv[i] != NULL ;)
		{
			if(strcmp(argv[i], "-between") == 0)
			{
				if(argv[i+1] == NULL || argv[i+2] == NULL || argv[i+3] == NULL)
				{
					printf("Error: Wrong format of '-between' argument!\n");
					exit(0);
				}
				tmpbool = getquery_between(nowrow,argv[i+1],argv[i+2],argv[i+3]);
				
				_templar_vla_push(&Function,tmpbool);
				
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
				_templar_vla_push(&Function,tmpbool);
				i+=3;
			}
			else if(strcmp(argv[i],"+") == 0 || strcmp(argv[i],"-and") == 0)
			{
				_templar_vla_push(&Function,-5);
				i+=1;
			}
			else if(strcmp(argv[i],"/") == 0 || strcmp(argv[i],"-or") == 0)
			{
				_templar_vla_push(&Function,-1);
				i+=1;
			}
			else if(strcmp(argv[i],"(") == 0 || strcmp(argv[i],"-l") == 0)
			{
				_templar_vla_push(&Function,-2);
				i+=1;
			}
			else if(strcmp(argv[i],")") == 0 || strcmp(argv[i],"-r") == 0)
			{
				_templar_vla_push(&Function,-3);
				i+=1;
			}
			else if(strcmp(argv[i],"!") == 0 || strcmp(argv[i],"-not") == 0)
			{
				_templar_vla_push(&Function,-4);
				i+=1;
			}
			else
			{
				printf("Unknown operation '%s'!\n",argv[i]);
				exit(0);
			}
		}
		if(DEBUG)
		{
			printf("Function ---> ");
			for(int i=0;i<=Function.now;++i)
			{
				printf("%d ",Function.arr[i]);
			}
			putchar('\n');
		}
		
		
		if(logical_calc(Function) == false)  DeleteRow(nowrow,true);
		
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
	WriteTable("./.mycheck/working.txt");
	return 0;
}
