#include "mycheck.h"

void ReadTable(FILE* stream)
{
	ReadAllHeader(stream);
	ReadAllRow(stream);
	if(DEBUG) printf("debug: read table end\n");
	EncodeTable();
	
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

void WriteTable(FILE *stream)
{
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
	fclose(stream);
}
