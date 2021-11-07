#include "mycheck.h"
/* run this program using the console pauser or add your own getch, system("pause") or input loop */

const bool DEBUG = true;
const int MAX_INPUT_CACHE=10001;

PROW rowbegin;
PHEADER headerbegin;
bool showcode = false;
int maxrow,maxheader;

int main(int argc, char *argv[])
{
//	if(DEBUG) system("cls");
	system("@chcp 65001"); //set charset to UTF-8
	
	switch(analyze(argc,argv))
	{
		case 0:printf("Program End safely.\n");
			break;
		case -1:printf("Fatal Error: No argument input!\n");
			break;
		case -2://printf("Error: Unknown command type when analyzing\n");
			break;
		case -3:printf("Error: Run time error\n");
			break;
		default:printf("Error: Unexpected return value from function 'analyze'\n");
			break;
	}
	
	/*
	system("pause");
	system("chcp 936");   //set charset back to GBK
	*/
	return 0;
}
