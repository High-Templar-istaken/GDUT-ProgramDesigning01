#ifndef _MYCHECK_KEYOPERATION
#define _MYCHECK_KEYOPERATION

PKEY QueryKeyHeader(PROW inrow, char *target);
PKEY InsertKey_BackOf(PKEY place, PKEY tobe, PROW inrow);
int ValueCmp(char *a,char *b);

#endif
