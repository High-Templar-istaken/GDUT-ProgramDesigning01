#include "mycheck.h"

bool JudgePlacing(PROW moving, PROW stable, char *argv[])
{
	struct VLA Function;
	Function.arr = NULL;
	PKEY movingkey = NULL;
	PKEY stablekey = NULL;
	
	_templar_vla_create(&Function);
	
	for(int i=2; argv[i] != NULL ; )
	{
		if(strcmp(argv[i],"-bigger") == 0)
		{
			if(argv[i+1] == NULL)
			{
				printf("Error: Wrong grammar of '-bigger' argument!\n");
				exit(0);
			}
			else
			{
				movingkey = QueryKeyHeader(moving,argv[i+1]);
				stablekey = QueryKeyHeader(stable,argv[i+1]);
				
				int r;
				
				if(stablekey == NULL && movingkey == NULL)
				{
					r=ValueCmp(QueryHeaderID(argv[i+1])->def,QueryHeaderID(argv[i+1])->def);
				}
				else if(stablekey == NULL)
				{
					r=ValueCmp((*movingkey).value,QueryHeaderID(argv[i+1])->def);
				}
				else if(movingkey == NULL)
				{
					r=ValueCmp(QueryHeaderID(argv[i+1])->def,(*stablekey).value);
				}
				else
				{
					r=ValueCmp((*movingkey).value,(*stablekey).value);
				}
				if(r == 1) _templar_vla_push(&Function,1);
				else _templar_vla_push(&Function,0);
				
			}
			i+=2;
		}
		else if(strcmp(argv[i],"-smaller") == 0)
		{
			if(argv[i+1] == NULL)
			{
				printf("Error: Wrong grammar of '-smaller' argument!\n");
				exit(0);
			}
			else
			{
				movingkey = QueryKeyHeader(moving,argv[i+1]);
				stablekey = QueryKeyHeader(stable,argv[i+1]);
				
				int r;
				
				if(stablekey == NULL && movingkey == NULL)
				{
					r=ValueCmp(QueryHeaderID(argv[i+1])->def,QueryHeaderID(argv[i+1])->def);
				}
				else if(stablekey == NULL)
				{
					r=ValueCmp((*movingkey).value,QueryHeaderID(argv[i+1])->def);
				}
				else if(movingkey == NULL)
				{
					r=ValueCmp(QueryHeaderID(argv[i+1])->def,(*stablekey).value);
				}
				else
				{
					r=ValueCmp((*movingkey).value,(*stablekey).value);
				}
				
				if(r == -1) _templar_vla_push(&Function,1);
				else _templar_vla_push(&Function,0);
			}
			i+=2;
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
	
	
	int back = logical_calc(Function);
	_templar_vla_clear(&Function);
	return back;
}

int getsort(int argc, char *argv[])
{
	if(argc == 2)
	{
		printf("Error: In function 'getsort': No arguments input!\n");
		exit(0);
	}
	
	ReadTable("./.mycheck/working.txt");
	PROW ComparingRow = NULL;
	
	PROW nowrow = rowbegin;
	PROW nxtrow = NULL;
	PROW sortedend = rowbegin;
	
	if(nowrow == NULL) return 0;
	
	nowrow = (*nowrow).nxtrow;
	
	while(nowrow != NULL)
	{
		nxtrow = (*nowrow).nxtrow;
		
		ComparingRow = rowbegin;
		
		while(ComparingRow != NULL)
		{
			if(JudgePlacing(nowrow,ComparingRow,argv) == true)
			{
				DeleteRow(nowrow,false);
				InsertRow_FrontOf(ComparingRow,nowrow);
				break;
			}
			
			if(ComparingRow == sortedend)
			{
				DeleteRow(nowrow,false);
				InsertRow_BackOf(sortedend, nowrow);
				sortedend = nowrow;
				break;
			}
			ComparingRow = (*ComparingRow).nxtrow;
		}
		
		nowrow = nxtrow;
	}
	WriteTable("./.mycheck/working.txt");
	return 0;
}
