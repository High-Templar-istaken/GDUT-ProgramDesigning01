#ifndef _MYCHECK_HEADEROPERATION
#define _MYCHECK_HEADEROPERATION

PHEADER InsertHeader_FrontOf(PHEADER place, PHEADER tobenew);
PHEADER InsertHeader_BackOf(PHEADER place, PHEADER tobenew);
void ReleaseShowAllHeader();
void DEBUGShowAllHeader();
void ReadAllHeader(FILE*);
void ReadAllHeader_DevideNextHeaderInput(char *line, int *j, char **first, char **second, char *tmp);
PHEADER QueryHeaderID(char *);
void DeleteHeader(PHEADER del, bool truedelete);
bool CheckHeaderUnmove(PHEADER now);
bool CheckHeaderUnmove_String(char* now);

#endif
