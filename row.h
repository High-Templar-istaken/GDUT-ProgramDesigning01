#ifndef _MYCHECK_ROWEROPERATION
#define _MYCHECK_ROWEROPERATION

void ReleaseShowAllRow();
void DEBUGShowAllRow();
void ReadAllRow(FILE*);
PKEY RowDevide(char *);
PKEY QueryKeyHeader(PROW inrow, char *target);

#endif
