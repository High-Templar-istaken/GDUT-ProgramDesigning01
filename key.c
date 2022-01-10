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

void DeleteKey(PKEY del, PROW inrow)
{
	//spj
	if((*inrow).keybegin->nxtkey == NULL)
	{
		(*inrow).keybegin = NULL;
		(*inrow).keybegin = NULL;
		free(del);
		return;
	}
	
	PKEY now = NULL;
	PKEY pre = NULL;
	PKEY nxt = NULL;
	/*delete*/
	if((*inrow).keybegin == del) // rowbegin
	{
		nxt = (*del).nxtkey;
		
		(*nxt).laskey = NULL;
		(*inrow).keybegin = nxt;
	}
	else if((*inrow).keyend == del) //headerend
	{
		pre = (*del).laskey;
		
		(*pre).nxtkey = NULL;
		(*inrow).keyend = pre;
	}
	else
	{
		pre = (*del).laskey;
		nxt = (*del).nxtkey;
		
		(*pre).nxtkey = nxt;
		(*nxt).laskey = pre;
	}
	
	free(del);
	
	return;
}
