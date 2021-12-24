#include "mycheck.h"

void getquery_vla_push(struct VLA* a,int t)
{
	(*a).arr[++(*a).now]=t;
	
	if(((*a).now)+1==((*a).len))
	{
		(*a).len*=2;
		(*a).arr = (int*) realloc((*a).arr,sizeof(int)*((*a).len));
	}
}

void getquery_vla_create(struct VLA* a)
{
	(*a).len=1;
	(*a).now=-1;
	(*a).arr = (int*) malloc(sizeof(int) * ((*a).len));// 0 - and ; 1 - or; 2 - (; 3 - ); 4 - !
}

void getquery_vla_clear(struct VLA* a)
{
	if((*a).arr != NULL) free((*a).arr);
	(*a).arr = NULL;
}

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

bool getquery_calc(struct VLA f)
{
	// negative num
	// 5 - and ; 1 - or; 2 - (; 3 - ); 4 - !
	
	struct VLA numstack,operstack;
	numstack.arr = NULL;
	operstack.arr = NULL;
	
	getquery_vla_create(&numstack);
	getquery_vla_create(&operstack);
	
	int now;
	for(int i=0;i<=f.now;++i)
	{
		putchar('g');
		now = f.arr[i];
		if(now<0)
		{
			if(now==-2) // (
			{
				getquery_vla_push(&operstack,now);
			}
			else if(now == -4) // !
			{
				getquery_vla_push(&operstack,now);
			}
			else if(now==-3) // )
			{
				if(operstack.arr[operstack.now]==-2)
				{
					operstack.now--;
					if(numstack.now<0) continue;
					f.arr[i]=numstack.arr[numstack.now--];
					i--;
					continue;
				}
				else
				{
					printf("ERROR: Parenthesis Matching Error!\n");
					exit(0);
				}
			}
			else // or and
			{
				if(i==0 || f.arr[i-1]==-1 || f.arr[i-1]==-5)
				{
					printf("ERROR: Wrong operators!\n");
					exit(0);
				}
				getquery_vla_push(&operstack,now);
			//	printf("%d\n",operstack.arr[operstack.now]);
			}
		}
		else
		{
			putchar('N');
			if(operstack.now<0 || operstack.arr[operstack.now] == -2)
			{
				putchar('P');
				getquery_vla_push(&numstack,now);
			}
			else
			{
				while(operstack.now>=0 && operstack.arr[operstack.now] != -2)
				{
					putchar('W');
					int t = operstack.arr[operstack.now--];
					if(t == -4) // !
					{
						now^=1;
						if(operstack.now<0)
						{
							getquery_vla_push(&numstack,now);
						}
						else continue;
					}
					
					else if(t == -1) // or
					{
						putchar('O');
						if(numstack.now<0)
						{
							printf("ERROR: Numbers don't match the operators! - situation 1\n");
							exit(0);
						}
						numstack.arr[numstack.now] |= now;
						printf("'%d'\n",now);
					}
					else if(t == -5) // and
					{
						if(numstack.now<0)
						{
							printf("ERROR: Numbers don't match the operators! - situation 1\n");
							exit(0);
						}
						numstack.arr[numstack.now] &= now;
					}
					f.arr[i]=numstack.arr[numstack.now--];
					printf("num=%d\n",numstack.now);
					printf("oper=%d\n",operstack.now);
					i--;
					continue;
				}
			}
		}
	}
	
	printf("num=%d\n",numstack.now);
					printf("oper=%d\n",operstack.now);
	if(numstack.now>0 || operstack.now>=0)
	{
		printf("ERROR: Numbers don't match the operators! - situation 2\n");
		exit(0);
	}
	
	int r=numstack.arr[0];
	getquery_vla_clear(&numstack);
	getquery_vla_clear(&operstack);
	
	/*if(DEBUG)*/ printf("[un]DEBUG: return %d in calculation.\n",r);
	return r;
}

void getquery_argument(int argc, char *argv[])
{
	ReadTable("./.mycheck/working.txt");
	
	bool nowbool = true;
	bool tmpbool = false;
	
	PROW nowrow = rowbegin;
	PROW nxtrow = NULL;
	
	struct VLA Function;
	Function.arr = NULL;
	
	while(nowrow != NULL)
	{
		
		nxtrow = (*nowrow).nxtrow;
		
		getquery_vla_clear(&Function);
		getquery_vla_create(&Function);
		
		
		
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
				
				getquery_vla_push(&Function,tmpbool);
				
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
				getquery_vla_push(&Function,tmpbool);
				i+=3;
			}
			else if(strcmp(argv[i],"+") == 0 || strcmp(argv[i],"-and") == 0)
			{
				getquery_vla_push(&Function,-5);
				i+=1;
			}
			else if(strcmp(argv[i],"/") == 0 || strcmp(argv[i],"-or") == 0)
			{
				getquery_vla_push(&Function,-1);
				i+=1;
			}
			else if(strcmp(argv[i],"(") == 0)
			{
				getquery_vla_push(&Function,-2);
				i+=1;
			}
			else if(strcmp(argv[i],")") == 0)
			{
				getquery_vla_push(&Function,-3);
				i+=1;
			}
			else if(strcmp(argv[i],"!") == 0)
			{
				getquery_vla_push(&Function,-4);
				i+=1;
			}
			else
			{
				printf("Unknown operation '%s'!\n",argv[i]);
				exit(0);
			}
		}
		printf("Function ---> ");
		for(int i=0;i<=Function.now;++i)
		{
			printf("%d ",Function.arr[i]);
		}
		putchar('\n');
		
		getquery_calc(Function);
		
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
