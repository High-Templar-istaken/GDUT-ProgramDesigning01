#ifndef _MYCHECK_HEADEROPERATION
#define _MYCHECK_HEADEROPERATION

void ReleaseShowAllHeader();
void DEBUGShowAllHeader();
void ReadAllHeader(FILE*);
struct header* QueryHeaderID(char *);
struct header* QueryHeaderCode(int);
void DeleteHeader(PHEADER);

#endif
