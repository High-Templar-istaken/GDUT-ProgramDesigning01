#ifndef _MYCHECK_HEADEROPERATION
#define _MYCHECK_HEADEROPERATION

PHEADER InsertHeader_PushFrontOf(PHEADER place, PHEADER tobenew);
PHEADER InsertHeader_PushBackOf(PHEADER place, PHEADER tobenew);
void ReleaseShowAllHeader();
void DEBUGShowAllHeader();
void ReadAllHeader(FILE*);
PHEADER QueryHeaderID(char *);
PHEADER QueryHeaderCode(int);
void DeleteHeader(PHEADER del, bool truedelete);

#endif
