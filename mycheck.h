#ifndef _MYCHECK_ALLHEADFILES
#define _MYCHECK_ALLHEADFILES

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "tools.h"

#include "analyze.h"
#include "display.h"
#include "header.h" 

/*global var*/
struct row
{
	struct key
	{
		struct key *nxtkey;
		char *value;
		char *header;
	};
	struct row *nxtrow;
};
extern struct header* rowbegin;

struct header
{
	char *id, *name;
	struct header* nxtheader;
};
extern bool DEBUG;
extern struct header* headerbegin;

#endif
