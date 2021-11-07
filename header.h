#ifndef _MYCHECK_HEADEROPERATION
#define _MYCHECK_HEADEROPERATION

struct header* InsertHeader_PushFrontOf(PHEADER place, PHEADER tobenew);
struct header* InsertHeader_PushBackOf(PHEADER place, PHEADER tobenew);
void ReleaseShowAllHeader();
void DEBUGShowAllHeader();
void ReadAllHeader(FILE*);
struct header* QueryHeaderID(char *);
struct header* QueryHeaderCode(int);
void DeleteHeader(PHEADER del, bool truedelete);

#endif
