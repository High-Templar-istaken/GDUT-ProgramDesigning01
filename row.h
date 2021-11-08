#ifndef _MYCHECK_ROWEROPERATION
#define _MYCHECK_ROWEROPERATION

void ReleaseShowAllRow();
void DEBUGShowAllRow();
void ReadAllRow(FILE*);
PKEY RowDevide(char *);
PKEY QueryKeyHeader(PROW inrow, char *target);
PROW InsertRow_PushFrontOf(PROW place, PROW tobenew);
PROW InsertRow_PushBackOf(PROW place, PROW tobenew);
PROW QueryRowTrueKey(int truekey);

#endif
