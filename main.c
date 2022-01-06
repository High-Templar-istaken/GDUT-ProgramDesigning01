#include "mycheck.h"

bool DEBUG = false;
int MAX_INPUT_CACHE = 10001;
bool AlwaysShowtable = false;
bool ExitMute = false;

PROW rowbegin;
PROW rowend;
PHEADER headerbegin;
PHEADER headerend;
bool showcode = false;
long long maxtruekey,totheader;

int main(int argc, char *argv[])
{
//	if(DEBUG) system("cls");
//	system("chcp 65001"); //set charset to UTF-8
	
	switch(analyze(argc,argv))
	{
		case 0:if(ExitMute != true) printf("Program End safely.\n");
			break;
		case -1:printf("Fatal Error: No argument input!\n");
			AlwaysShowtable = false;
			break;
		case -2:printf("Error: Unknown command type when analyzing\n");
			AlwaysShowtable = false;
			break;
		default:printf("Error: Unexpected return value from function 'analyze'\n");
			AlwaysShowtable = false;
			break;
	}
	
	if(AlwaysShowtable == true)
	{
		ReleasePrintTable();
	}
	return 0;
}
