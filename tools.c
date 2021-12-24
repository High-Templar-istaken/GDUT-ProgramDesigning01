#include "mycheck.h"

void _templar_GetTightString_Getline(char **_templar_StringName, FILE *stream)
{
	*_templar_StringName = NULL;
	
	char *_templar_tmp = NULL;
	
	_templar_tmp = (char*)malloc(sizeof(char) * MAX_INPUT_CACHE);
	fgets(_templar_tmp,MAX_INPUT_CACHE,stream);
	
	if(DEBUG) printf("debug: In func '_templarstring': Got='%s' len=%d\n",(_templar_tmp),(int)(strlen((_templar_tmp))));
	
	*_templar_StringName = (char*)malloc(sizeof(char) * (strlen(_templar_tmp)+1));
	strcpy(*_templar_StringName,_templar_tmp);
	free(_templar_tmp);
	
	return;
}

int _templar_StringToInt(char *str)
{
	int i = 0;
	int back = 0;
	int pn = 1;// positive or negative
	if(!isdigit(str[0]))
	{
		if(str[0] == '-') pn = -1;
		else if(str[0] == '+') pn = 1;
		else
		{
			printf("Error: In function '_templar_StringToInt': '%s' is not a number\n",str);
			exit(0);
		}
		++i;
	}
	for(;i<strlen(str);++i)
	{
		if(isdigit(str[i]))
		{
			back=back*10+str[i]-'0';
		}
		else
		{
			printf("Error: In function 'StringToInt': '%s' is not a number\n",str);
			exit(0);
		}
	}
	return back*pn;
}

bool _templar_HaveColon(char *str)
{
	int t = strlen(str);
	for(int i = 0; i < t; ++i)
	{
		if(str[i] == ':') return true;
	}
	return false;
}
