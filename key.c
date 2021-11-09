#include "mycheck.h"

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
