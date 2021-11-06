#ifndef _MYCHECK_ALLHEADFILES
#define _MYCHECK_ALLHEADFILES
/*global var*/


struct key
{
	struct key *nxtkey;
	struct key *laskey;
	char *value;
	char *header;
};
	
struct row
{
	struct key *keybegin;
	struct row *nxtrow;
	struct row *lasrow;
};
extern struct row* rowbegin;

struct header
{
	char *id, *name;
	struct header *nxtheader;
	struct header *lasheader;
};
extern struct header* headerbegin;
extern const int MAX_INPUT_CACHE;

#define PKEY struct key*
#define PROW struct row*
#define PHEADER struct header*

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "tools.h"

#include "analyze.h"
#include "display.h"
#include "header.h" 
#include "row.h"
#include "key.h"
#include "else.h"
#include "getheader.h"

#include "table.h"



extern const bool DEBUG;

#endif
