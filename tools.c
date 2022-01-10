#include "mycheck.h"

int ValueCmp(char *a,char *b)
{
	if(DEBUG) printf("debug: In function 'valuecmp': a=%s, b=%s!\n",a,b);
	bool bothdigit = true;
	int i = 0;
	
	if(a[0] == '-' || a[0] == '+')
	{
		if(strlen(a) != 1) ++i;
		else bothdigit = false;
	}
	
	bothdigit &= _templar_JudgeStringIsNumber(a+i);
	
	i = 0;
	if(b[0] == '-' || b[0] == '+')
	{
		if(strlen(b) != 1) ++i;
		else bothdigit = false;
	}
	bothdigit &= _templar_JudgeStringIsNumber(b+i);
	
	if(bothdigit)
	{
		int va = _templar_StringToNumber(a), vb = _templar_StringToNumber(b);
		if(va < vb) return -1;
		else if(va == vb) return 0;
		else if(va > vb) return 1;
	}
	else return strcmp(a,b);
	
	// unreachable
	return -1;
}

void _templar_vla_push(struct VLA* a,int t)
{
	(*a).arr[++(*a).now]=t;
	
	if(((*a).now)+1==((*a).len))
	{
		(*a).len*=2;
		(*a).arr = (int*) realloc((*a).arr,sizeof(int)*((*a).len));
	}
}

void _templar_vla_create(struct VLA* a)
{
	(*a).len=1;
	(*a).now=-1;
	(*a).arr = (int*) malloc(sizeof(int) * ((*a).len));// 0 - and ; 1 - or; 2 - (; 3 - ); 4 - !
}

void _templar_vla_clear(struct VLA* a)
{
	if((*a).arr != NULL) free((*a).arr);
	(*a).arr = NULL;
}

void _templar_GetTightString_Getline(char **_templar_StringName, FILE *stream)
{
	*_templar_StringName = NULL;
	
	char *_templar_tmp = NULL;
	
	_templar_tmp = (char*)malloc(sizeof(char) * MAX_INPUT_CACHE);
	fgets(_templar_tmp,MAX_INPUT_CACHE,stream);
	
	if(DEBUG) printf("debug: In func '_templarstring': Got='%s' len=%d\n",(_templar_tmp),(int)(strlen((_templar_tmp))));
	
	*_templar_StringName = (char*)malloc(sizeof(char) * (strlen(_templar_tmp)+1));
	strcpy(*_templar_StringName,_templar_tmp);
	free(_templar_tmp);
	
	return;
}

bool logical_calc(struct VLA f)
{
	// negative num
	// 5 - and ; 1 - or; 2 - (; 3 - ); 4 - !
	
	if(f.now<0) return true;
	
	struct VLA numstack,operstack;
	numstack.arr = NULL;
	operstack.arr = NULL;
	
	_templar_vla_create(&numstack);
	_templar_vla_create(&operstack);
	
	int now;
	for(int i=0;i<=f.now;++i)
	{
		if(DEBUG) putchar('g');
		now = f.arr[i];
		if(now<0)
		{
			if(now==-2) // (
			{
				_templar_vla_push(&operstack,now);
			}
			else if(now == -4) // !
			{
				_templar_vla_push(&operstack,now);
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
				if(i==0 || f.arr[i-1]==-1 || f.arr[i-1]==-5 || f.arr[i-1]==-4 || f.arr[i-1]==-2 )
				{
					printf("ERROR: Wrong operators!\n");
					exit(0);
				}
				_templar_vla_push(&operstack,now);
			//	printf("%d\n",operstack.arr[operstack.now]);
			}
		}
		else
		{
			if(DEBUG) putchar('N');
			if(operstack.now<0 || operstack.arr[operstack.now] == -2)
			{
				if(DEBUG) putchar('P');
				_templar_vla_push(&numstack,now);
			}
			else
			{
				while(operstack.now>=0 && operstack.arr[operstack.now] != -2)
				{
					if(DEBUG) putchar('W');
					int t = operstack.arr[operstack.now--];
					if(t == -4) // !
					{
						now^=1;
						if(operstack.now<0)
						{
							_templar_vla_push(&numstack,now);
						}
						else continue;
					}
					
					else if(t == -1) // or
					{
						if(DEBUG) putchar('O');
						if(numstack.now<0)
						{
							printf("ERROR: Numbers don't match the operators! - situation 1\n");
							exit(0);
						}
						numstack.arr[numstack.now] |= now;
						if(DEBUG) printf("'%d'\n",now);
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
					i--;
					continue;
				}
			}
		}
	}
	
	if(DEBUG) printf("num=%d\n",numstack.now);
	if(DEBUG) printf("oper=%d\n",operstack.now);
	if(numstack.now>0 || operstack.now>=0)
	{
		printf("ERROR: Numbers don't match the operators! - situation 2\n");
		exit(0);
	}
	
	int r=numstack.arr[0];
	_templar_vla_clear(&numstack);
	_templar_vla_clear(&operstack);
	
	if(DEBUG) printf("DEBUG: return %d in calculation.\n",r);
	return r;
}

double _templar_StringToNumber(char *str)
{
	if(_templar_JudgeStringIsNumber(str) == false)
	{
		printf("Error: In function '_templar_StringToNumber': '%s' is not a number\n",str);
		exit(0);
	}
	
	double back = 0;
	double downpower=1;
	int pn = 1;// positive or negative
	if(!isdigit(str[0]))
	{
		if(str[0] == '-') pn = -1;
		else if(str[0] == '+') pn = 1;
		str+=1;
	}
	
	bool pointed = false;
	
	for(int i=0;i<strlen(str);++i)
	{
		if(isdigit(str[i]))
		{
			if(pointed == false) back=back*10+str[i]-'0';
			else
			{
				downpower*=0.1;
				back+=downpower*(str[i]-'0');
			}
		}
		else if(str[i] == '.')
		{
			pointed = true;
		}
	}
	if(DEBUG) printf("debug: In function '_templar_StringToNumber': return = %lf\n",back*pn);
	return back*pn;
}

bool _templar_HaveColon(char *str)
{
	int t = strlen(str);
	for(int i = 0; i < t; ++i)
	{
		if(str[i] == ':') return true;
	}
	return false;
}

bool _templar_JudgeStringIsNumber(char *a)
{
	bool pointed=false;
	
	if(a[0]=='-' || a[0]=='+')
	{
		if(strlen(a) == 1) return false;
		else a++;
	}
	
	for(int i=0;i<strlen(a);++i)
	{
		if((!isdigit(a[i])) && (!(a[i]=='.' && i!=strlen(a)-1 && i!=0)))
		{
			return false;
		}
		if(a[i]=='.')
		{
			if(pointed == true) return false;
			else pointed=true;
		}
	}
	return true;
}
