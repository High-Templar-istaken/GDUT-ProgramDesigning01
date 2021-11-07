#include "mycheck.h"

void getheader_m_mode(char *filename, char* id,char *offset)
{
	if(!isdigit(offset[0]))
	{
		if(offset[0] != '^' && offset[0] != '&')
		{
			printf("Error: In function 'getheader_m_mode': Direction mark of '%s' is not '^' or '&'\n", offset);
			exit(0);
		}
		if(offset[1] == '\0')
		{
			printf("Error: In function 'getheader_m_mode': No distance argument in '%s'!\n", offset);
			exit(0);
	 	} 
		if(offset[0] == '^')
		{
			
		}
		else
		{
			
		}
	}
	else
	{
		for(int i=0;i<strlen(offset);++i)
		{
			if(!isdigit(offset[i]))
			{
				printf("Error: In function 'getheader_m_mode': Not all chars of the argument '%s' is digit\n", offset);
				exit(0);
			}
		}
	}
}

void getheader_n_mode(char *filename, char* id, char* displayname)
{
	if(DEBUG) printf("debug: stream=%s -> getheader_n_mode -> id=%s displayname=%s\n",filename,id,displayname);
	
	FILE *stream = fopen(filename,"r");
	ReadTable(stream);
	if(QueryHeader(id) != NULL)
	{
		printf("Error: In function 'getheader_n_mode': new header's ID '%s' already existed!\n",id);
		exit(0);
	}
	
	if(noheader == true)
	{
		headerbegin = (PHEADER) malloc(sizeof(struct header));
		(*headerbegin).nxtheader = (*headerbegin).lasheader = NULL;
		(*headerbegin).id = id;
		(*headerbegin).name = displayname;
		fclose(stream);
		fclose(stream);
		stream = fopen(filename,"w");
		WriteTable(stream);
		fclose(stream);
		stream = NULL;
		return;
	}
	
	PHEADER nowheader = headerbegin;
	while((*nowheader).nxtheader != NULL) nowheader = (*nowheader).nxtheader;
	
	(*nowheader).nxtheader = (PHEADER) malloc(sizeof(struct header));
	(*((*nowheader).nxtheader)).lasheader = nowheader;
	nowheader = (*nowheader).nxtheader;
	(*nowheader).nxtheader = NULL;
	(*nowheader).id = id;
	(*nowheader).name = displayname;
	
	DebugPrintTable();
	fclose(stream);
	stream = fopen(filename,"w");
	WriteTable(stream);
	fclose(stream);
	stream = NULL;
}

void getheader_argument(int argc,char *argv[])
{
	for(int i = 2 ; argv[i] != NULL ; ++i)
	{
		if(strcmp(argv[i],"-n") == 0)
		{
			if(argv[i+1] == NULL || argv[i+2] == NULL)
			{
				printf("Error: In function 'getheader': Wrong format of argument '-n'\n");
				exit(0);
			}
			//operating both lists
			getheader_n_mode("./.mycheck/working.txt",argv[i+1],argv[i+2]);
			getheader_n_mode("./.mycheck/storage.txt",argv[i+1],argv[i+2]);
			i+=2;
			return;
		}
		else if(strcmp(argv[i],"-m") == 0)
		{
			if(argv[i+1] == NULL || argv[i+2] == NULL)
			{
				printf("Error: In function 'getheader': Wrong format of argument '-m'\n");
				exit(0);
			}
			getheader_m_mode("./.mycheck/working.txt",argv[i+1],argv[i+2]);
//			getheader_m_mode("./.mycheck/storage.txt",argv[i+1],argv[i+2]);
			i+=2;
		}
		else if(strcmp(argv[i],"-d") == 0)
		{
			if(argv[i+1] == NULL)
			{
				printf("Error: In function 'getheader': Wrong format of argument '-d'\n");
				exit(0);
			}
//			arg1 = argv[i+1];
			++i;
		}
		else if(strcmp(argv[i],"-r") == 0)
		{
			if(argv[i+1] == NULL || argv[i+2] == NULL)
			{
				printf("Error: In function 'getheader': Wrong format of argument '-r'\n");
				exit(0);
			}
//			arg1 = argv[i+1];
//			arg2 = argv[i+2];
			i+=2;
		}
		else
		{
			printf("Error: In function 'getheader': Unknown argument '%s'\n", argv[i]);
			exit(0);
		}
	}
}

int getheader(int argc,char *argv[])
{
	getheader_argument(argc, argv);
	
	return 0;
}
