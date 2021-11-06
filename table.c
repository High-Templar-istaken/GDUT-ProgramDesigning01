#include "mycheck.h"

void ReadTable(FILE* stream)
{
	ReadAllHeader(stream);
	ReadAllRow(stream);
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
