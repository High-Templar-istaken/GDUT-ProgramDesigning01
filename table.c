#include "mycheck.h"

void initconfig()
{
	FILE *config = fopen("./.mycheck/config.txt","r");
	
	/*debug cache showtable*/
	if(fscanf(config,"%d%d%d%d",&DEBUG,&MAX_INPUT_CACHE,&AlwaysShowtable,&ExitMute) != 4)
	{
		printf("Fatal Error: Failed to read the config. Try to use 'mycheck config -reset' to recover.\n");
		exit(0);
	}
	
	fclose(config);
	return;
}

void ReadTable(char *filename)
{
	FILE *stream = fopen(filename,"r");
	ReadAllHeader(stream);
	ReadAllRow(stream);
	if(DEBUG) printf("debug: read table end\n");
	
	fclose(stream); stream = NULL;
	return;
}

void ReleasePrintTable()
{
	ReleaseShowAllHeader();
	ReleaseShowAllRow();
	return;
}
void DebugPrintTable()
{
	DEBUGShowAllHeader();
	DEBUGShowAllRow();
	return;
}

void WriteTable(char *filename)
{
	FILE *stream = fopen(filename,"w");
	
	PHEADER nowheader = headerbegin;
	fprintf(stream,"%d\n",maxtruekey);
	while(nowheader != NULL)
	{
		fprintf(stream,"%s:%s ",(*nowheader).id, (*nowheader).name);
		nowheader = (*nowheader).nxtheader;
	}
	fprintf(stream,"\n");
	nowheader = headerbegin;
	while(nowheader != NULL)
	{
		fprintf(stream,"%s:%s ",(*nowheader).id, (*nowheader).def);
		nowheader = (*nowheader).nxtheader;
	}
	fprintf(stream,"\n");
	
	PROW nowrow = rowbegin;
	PKEY nowkey = NULL;
	while(nowrow != NULL)
	{
		nowkey = (*nowrow).keybegin;
		fprintf(stream,"%d ",(*nowrow).truekey);
		if((*nowrow).keybegin == NULL) fprintf(stream,"#:# ");
		while(nowkey != NULL)
		{
			fprintf(stream,"%s:%s ",(*nowkey).header,(*nowkey).value);
			nowkey = (*nowkey).nxtkey;
		}
		fprintf(stream,"\n");
		nowrow = (*nowrow).nxtrow;
	}
	fprintf(stream,"rowend\n");
	fprintf(stream,"\n\n\n");
	
	fclose(stream); stream = NULL;
}
