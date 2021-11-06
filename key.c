#include "mycheck.h"

struct key* QueryKey(PROW inrow, char *targetheader)
{
	PKEY nowkey = (*inrow).keybegin;
	while(nowkey != NULL)
	{
		if(strcmp(targetheader, (*nowkey).header) == 0)
		{
			break;
		}
		nowkey = (*nowkey).nxtkey;
	}
	return nowkey;
}
