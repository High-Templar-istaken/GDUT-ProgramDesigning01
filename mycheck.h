#ifndef _MYCHECK_ALLHEADFILES
#define _MYCHECK_ALLHEADFILES
/*global var*/
#include <stdbool.h>

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
	int code;
};
extern struct row* rowbegin;
extern bool norow;

struct header
{
	char *id, *name;
	struct header *nxtheader;
	struct header *lasheader;
	int code;
};
extern struct header* headerbegin;
extern const int MAX_INPUT_CACHE;
extern bool noheader,showcode;

#define PKEY struct key*
#define PROW struct row*
#define PHEADER struct header*

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tools.h"

#include "analyze.h"
#include "display.h"
#include "header.h" 
#include "row.h"
#include "key.h"
#include "else.h"
#include "getheader.h"
#include "encode.h"

#include "table.h"

extern const bool DEBUG;

#endif
