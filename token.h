/*************************************************************************
	> File Name: token.h
	> Author: ellochen
	> Mail: god_mode@yeah.net
	> Created Time: Thu May  9 01:00:45 2013
 ************************************************************************/
#ifndef _TOKEN_H_
#define _TOKEN_H_

enum TOKENID{
//操作符
	TOKEN_PLUS,
	TOKEN_MINUS,
	TOKEN_STAR,
	TOKEN_SLASH,
	TOKEN_EQUAL,

//标点符号
	TOKEN_LPAREN,
	TOKEN_RPAREN,
	TOKEN_LINEEND,
	
//常量
	TOKEN_DOUBLECONST,
	TOKEN_INTCONST,
	TOKEN_STRCONST,
	
//标识符
	TOKEN_ID,
};

union TokenVar{
	double d;
	char *p;
};

struct Token{
	union TokenVar var;
	enum TOKENID type; 
};

#endif
