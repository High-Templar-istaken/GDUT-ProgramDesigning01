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

PKEY QueryKeyHeader(PROW inrow, char *target)
{
//	if(DEBUG) printf("debug: In function 'QueryKeyHeader': truekey=%d WHILE target=%s\n",(*inrow).truekey,target);
	PKEY nowkey = (*inrow).keybegin;
	while(nowkey != NULL)
	{
		if(strcmp((*nowkey).header, target) == 0) break;
		nowkey = (*nowkey).nxtkey;
	}
	return nowkey;
}

PKEY InsertKey_BackOf(PKEY place, PKEY tobe, PROW inrow)
{
	if(place == NULL)
	{
		(*inrow).keyend = (*inrow).keybegin = tobe;
		return tobe;
	}
	// create a new key
	if((*place).nxtkey == NULL)
	{
		(*place).nxtkey = tobe;
		(*tobe).laskey = place;
		
		(*inrow).keyend = tobe;
	}
	else if((*place).laskey == NULL)
	{
		(*place).laskey = tobe;
		(*tobe).nxtkey = place;
		
		(*inrow).keybegin = tobe;
	}
	else
	{
		(*(*place).nxtkey).laskey = tobe;
		
		(*tobe).nxtkey = (*place).nxtkey;
		(*tobe).laskey = place;
		
		(*place).nxtkey = tobe;
	}
	return tobe;
}
