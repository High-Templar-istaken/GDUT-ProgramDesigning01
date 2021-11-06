#include "mycheck.h"

void _templar_GetTightString_Getline(char **_templar_StringName, FILE *stream)
{
	
	*_templar_StringName = NULL;
	
	char *_templar_tmp = NULL;
	
	_templar_tmp = (char*)malloc(sizeof(char) * MAX_INPUT_CACHE);
	fgets(_templar_tmp,MAX_INPUT_CACHE,stream);
	
	*_templar_StringName = (char*)malloc(sizeof(char) * (strlen(_templar_tmp)+1));
	strcpy(*_templar_StringName,_templar_tmp);
	free(_templar_tmp);
	
	return;
}
