#ifndef _MYCHECK_ROWEROPERATION
#define _MYCHECK_ROWEROPERATION

void ReleaseShowAllRow();
void DEBUGShowAllRow();
void ReadAllRow(FILE*);
PROW InsertRow_FrontOf(PROW place, PROW tobenew);
PROW InsertRow_BackOf(PROW place, PROW tobenew);
PROW QueryRowTrueKey(int truekey);
void RowDevide(char *source, PROW inrow);
void DeleteRow(PROW del, bool truedelete);

#endif
