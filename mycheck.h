#ifndef _MYCHECK_ALLHEADFILES
#define _MYCHECK_ALLHEADFILES

#define MAX_INPUT_CACHE 10001

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "tools.h"

#include "analyze.h"
#include "display.h"
#include "header.h" 
#include "row.h"
#define PKEY struct key*
#define PROW struct row*
#define PHEADER struct header*

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
extern bool DEBUG;
extern struct header* headerbegin;

#endif
