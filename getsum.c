#include "mycheck.h"

int getsum(int argc,char *argv[])
{
	double sum=0;
	
	ReadTable("./.mycheck/working.txt");
	if(argc > 3 || argc <= 2)
	{
		printf("ERROR: In function 'getsum': Not enough arguments!\n");
		exit(0);
	}
	
	PKEY nowkey = NULL;
	char *header = argv[2];
	
	if(QueryHeaderID(header) == NULL)
	{
		printf("ERROR: In function 'getsum': No such header '%s'!\n",header);
		exit(0);
	}
	
	PROW nowrow = rowbegin;
	
	while(nowrow != NULL)
	{
		nowkey = QueryKeyHeader(nowrow, header);
		if(nowkey != NULL)
		{
			sum+=_templar_StringToNumber((*nowkey).value);
		}
		else
		{
			sum+=_templar_StringToNumber(QueryHeaderID(header)->def);
		}
		nowrow = (*nowrow).nxtrow;
	}
	
	if(ExitMute == false) printf("The result of summing up header '%s' is %lf\n",header,sum);
	else printf("%lf",sum);
	return 0;
}
