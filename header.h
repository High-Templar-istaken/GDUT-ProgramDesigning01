#ifndef _MYCHECK_HEADEROPERATION
#define _MYCHECK_HEADEROPERATION

struct header* NewHeader_PushFrontOf(PHEADER place, char *id, char *name);
struct header* NewHeader_PushBackOf(PHEADER place, char *id, char *name);
void ReleaseShowAllHeader();
void DEBUGShowAllHeader();
void ReadAllHeader(FILE*);
struct header* QueryHeaderID(char *);
struct header* QueryHeaderCode(int);
void DeleteHeader(PHEADER);

#endif
