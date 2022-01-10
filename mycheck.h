#ifndef _MYCHECK_ALLHEADFILES
#define _MYCHECK_ALLHEADFILES
/*global var*/
#include <stdbool.h>
#define PKEY struct key*
#define PROW struct row*
#define PHEADER struct header*

/*变长度数组类型*/
struct VLA
{
	int *arr;
	int len,now;
};

/*双向链表 ×3*/
struct key
{
	struct key *nxtkey;
	struct key *laskey;
	char *value;
	char *header;
};
	
struct row
{
	struct key *keybegin, *keyend;
	struct row *nxtrow;
	struct row *lasrow;// should be named 'pre...' but I can't rename it :(
	long long truekey;
};
extern PROW rowbegin;
extern PROW rowend;

struct header
{
	char *id, *name, *def;
	struct header *nxtheader;
	struct header *lasheader;// should be named 'pre...' but I can't rename it :(
};
extern PHEADER headerbegin;
extern PHEADER headerend;

extern bool showcode;
extern long long maxtruekey,totheader;

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "tools.h"

#include "analyze.h"
#include "display.h"
#include "header.h" 
#include "row.h"
#include "key.h"
#include "else.h"
#include "getheader.h"
#include "getrow.h"
#include "getquery.h"
#include "getsum.h"
#include "getsort.h"
#include "getconfig.h"

#include "table.h"

/*四大配置*/
extern bool DEBUG;
extern int MAX_INPUT_CACHE;
extern int AlwaysShowtable;
extern bool ExitMute;

#endif
