#ifndef _COMMENT_CONVERT_H__
#define _COMMENT_CONVERT_H__
#endif
#include<stdio.h>
#include<stdlib.h>
enum State
{
	NUL_STATE,
	C_STATE,
	CPP_STATE,
	END_STATE
};


void CommentConvert();
void dowork(FILE*pfin,FILE*pfout);
void doc(FILE*pfin,FILE*pfout);
void donul(FILE*pfin,FILE*pfout);
void docpp(FILE*pfin,FILE*pfout);
