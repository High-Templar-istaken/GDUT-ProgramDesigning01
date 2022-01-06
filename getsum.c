#include "mycheck.h"

void getsum_add_mode(char *header)
{
	double sum=0;
	PKEY nowkey = NULL;
	
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
	
	return;
}

void getsum_numrow_mode()
{
	int cnt=0;
	
	PROW nowrow = rowbegin;
	
	while(nowrow != NULL)
	{
		++cnt;
		nowrow = (*nowrow).nxtrow;
	}
	
	if(ExitMute == false) printf("rows remain: %d\n",cnt-1);// except the ##:##
	else printf("%d",cnt); 
	
	return;
}

void getsum_numheader_mode()
{
	int cnt=0;
	
	PHEADER nowheader = headerbegin;
	
	while(nowheader != NULL)
	{
		++cnt;
		nowheader = (*nowheader).nxtheader;
	}
	
	if(ExitMute == false) printf("headers remain: %d\n",cnt);
	else printf("%d",cnt);
	
	return;
}

int getsum(int argc,char *argv[])
{
	ReadTable("./.mycheck/working.txt");
	
	if(argv[2] == NULL)
	{
		printf("ERROR: In function 'getsum': Not enough arguments!\n");
		exit(0);
	}
	
	if(strcmp(argv[2],"-add") == 0)
	{
		if(argv[3] == NULL)
		{
			printf("ERROR: Not enough arguments in the '-add'\n");
			exit(0);
		}
		getsum_add_mode(argv[3]);
	}
	else if(strcmp(argv[2],"-num=row") == 0)
	{
		if(argv[3] != NULL)
		{
			printf("ERROR: Too many arguments in the '-num'\n");
			exit(0);
		}
		getsum_numrow_mode();
	}
	else if(strcmp(argv[2],"-num=header") == 0)
	{
		if(argv[3] != NULL)
		{
			printf("ERROR: Too many arguments in the '-num'\n");
			exit(0);
		}
		getsum_numheader_mode();
	}
	else
	{
		printf("ERROR: Unrecognized argument '%s'\n",argv[2]);
		exit(0);
	}
	
	
	return 0;
}
