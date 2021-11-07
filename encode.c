#include "mycheck.h"

void EncodeRow()
{
	int tmp = 0;
	maxrow = 0;
    PROW nowrow = rowbegin;
	if(nowrow == NULL && DEBUG) printf("debug: In function 'EncodeRow': no row in current list!\n");
	else
	{
		tmp = 0;
		while(nowrow != NULL)
		{
			maxrow = (*nowrow).code = ++tmp;
			nowrow = (*nowrow).nxtrow;
		}
	}
}

void EncodeHeader()
{
	int tmp = 0;
	PHEADER nowheader = headerbegin;
	maxheader = 0;
	if(nowheader == NULL && DEBUG) printf("debug: In function 'EncodeHeader': no header in current list!\n");
	else
	{
		tmp = 0;
		while(nowheader != NULL)
		{
			maxheader = (*nowheader).code = ++tmp;
			nowheader = (*nowheader).nxtheader;
		}
	}
}

void EncodeTable()
{
	EncodeHeader();
	EncodeRow();
	if(DEBUG) printf("debug: In function 'EncodeTable': maxrow=%d maxheader=%d\n",maxrow,maxheader);
}
