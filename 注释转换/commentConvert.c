#include"CommentConvert.h"

static enum State state = NUL_STATE;
void doc(FILE*pfin,FILE*pfout)
{
	int first = 0;
	int second = 0;
	first = fgetc(pfin);
	if(first == '*')
	{
		second = fgetc(pfin);
		if(second == '/')
		{
			fputc('\n',pfout);
			state = NUL_STATE;
		}
		else if(second == '\n')
		{
			fputc(first,pfout);
			fputc('\n',pfout);
			fputc('/',pfout);
			fputc('/',pfout);
		}
		else if(second == '*')
		{
			ungetc(second,pfin);
			fputc(first,pfout);
		}
		else
		{
			fputc(first,pfout);
			fputc(second,pfout);
		}
	}
	else if(first == '\n')
	{
		fputc(first,pfout);
		fputc('/',pfout);
		fputc('/',pfout);
	}
	else if(first == EOF)
	{
		state = END_STATE;
	}
	else
	{
		fputc(first,pfout);
	}
}
void donul(FILE*pfin,FILE*pfout)
{
	int first = 0;
	int second = 0;
	first = fgetc(pfin);
	if(first == '/')
	{
		second = fgetc(pfin);
		if(second == '/')
		{
			fputc(first,pfout);
			fputc(second,pfout);
			state = CPP_STATE;
		}
		else if(second == '*')
		{
			fputc('/',pfout);
			fputc('/',pfout);
			state = C_STATE;
		}
		else
		{
			fputc(first,pfout);
		}
	}
	else if(first == EOF)
	{
		state = END_STATE;
	}
	else
	{
		fputc(first,pfout);
	}
}
void docpp(FILE*pfin,FILE*pfout)
{
	int first = 0;
	int second = 0;
	first = fgetc(pfin);
	if(first == '/')
	{
		second = fgetc(pfin);
		if(second == '\n')
		{
			fputc(first,pfout);
			fputc(second,pfout);
			state = NUL_STATE;
		}
		else 
		{
			fputc(first,pfout);
			fputc(second,pfout);
		}
	}
	else if(first == '\n')
	{
		fputc(first,pfout);
		state = NUL_STATE;
	}
	else if(first == EOF)
	{
		state = END_STATE;
	}
	else
	{
		fputc(first,pfout);
	}
}
void dowork(FILE*pfin,FILE*pfout)
{
	while(state!=END_STATE)
	{
		switch(state)
		{
		case C_STATE:
			doc(pfin,pfout);
			break;
		case CPP_STATE:
			docpp(pfin,pfout);
			break;
		case NUL_STATE:
			donul(pfin,pfout);
			break;
		case END_STATE:
			break;
		default :
			break;
		}
	}
}
void CommentConvert()
{
	FILE *pfwrite = NULL;
	FILE *pfread = NULL;
	pfread = fopen("input.c","r");
	if(pfread == NULL)
	{
		perror("open file for read\n");
		exit(EXIT_FAILURE);
	}
	pfwrite = fopen("output.c","w");
	if(pfwrite == NULL)
	{
		perror("open file for write\n");
		fclose(pfread);
		exit(EXIT_FAILURE);
	}
	dowork(pfread,pfwrite);
	fclose(pfread);
	fclose(pfwrite);
}