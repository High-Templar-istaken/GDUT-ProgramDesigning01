#ifndef _MYCHECK_TOOLS
#define _MYCHECK_TOOLS

bool logical_calc(struct VLA f);
void _templar_GetTightString_Getline(char**, FILE *);
double _templar_StringToNumber(char *str);
bool _templar_HaveColon(char*);
void _templar_vla_clear(struct VLA* a);
void _templar_vla_create(struct VLA* a);
void _templar_vla_push(struct VLA* a,int t);
bool _templar_JudgeStringIsNumber(char *a);

#endif
