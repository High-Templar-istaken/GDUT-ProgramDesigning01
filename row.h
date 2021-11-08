#ifndef _MYCHECK_ROWEROPERATION
#define _MYCHECK_ROWEROPERATION

void ReleaseShowAllRow();
void DEBUGShowAllRow();
void ReadAllRow(FILE*);
PKEY QueryKeyHeader(PROW inrow, char *target);
PROW InsertRow_FrontOf(PROW place, PROW tobenew);
PROW InsertRow_BackOf(PROW place, PROW tobenew);
PROW QueryRowTrueKey(int truekey);
void RowDevide(char *source, PROW inrow);
PKEY InsertKey_BackOf(PKEY place, PKEY tobe, PROW inrow);

#endif
