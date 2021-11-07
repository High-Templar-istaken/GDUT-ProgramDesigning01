#include "mycheck.h"

void ReadTable(FILE* stream)
{
	ReadAllHeader(stream);
	ReadAllRow(stream);
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
	while(nowheader != NULL)
	{
		fprintf(stream,"%s:%s ",(*nowheader).id, (*nowheader).name);
		nowheader = (*nowheader).nxtheader;
	}
	fprintf(stream,"\n");
	
	PROW nowrow = rowbegin;
	PKEY nowkey = NULL;
	while(nowrow != NULL)
	{
		nowkey = (*nowrow).keybegin;
		while(nowkey != NULL)
		{
			fprintf(stream,"%s:%s ",(*nowkey).header,(*nowkey).value);
			nowkey = (*nowkey).nxtkey;
		}
		fprintf(stream,"\n");
		nowrow = (*nowrow).nxtrow;
	}
	fprintf(stream,"\n");
	fprintf(stream,"\n");
	fclose(stream);
}
