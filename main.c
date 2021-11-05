#include "mycheck.h"

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main(int argc, char *argv[])
{
//	system("chcp 65001"); //set charset to UTF-8
	
	switch(analyze(argc,argv))
	{
		case -1:printf("Fatal Error: No argument input!\n");
			break;
		case -2:printf("Error: Unknown command type\n");
			break;
		case -3:printf("Error: Failed to get return\n");
			break;
		default:printf("Error: Unexpected return value\n");
			break;
	}
	
	return 0;
	/*
	system("pause");
	system("chcp 936");   //set charset back to GBK
	*/
	return 0;
}
