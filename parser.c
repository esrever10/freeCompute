/*************************************************************************
	> File Name: parser.c
	> Author: ellochen
	> Mail: god_mode@yeah.net
	> Created Time: Wed May  8 23:24:27 2013
 ************************************************************************/
#include "parser.h"
#include "lex.h"
#include "token.h"
/*
Statement:
	Expression

Expression:
	Term
	Expression + Term
	Expression - Term

Term:
	Primary
	Term * Primary
	Term / Primary

Primary:
	Number
	( Expression )
	- Primary
	+ Primary

Number:
	float
*/

extern char *CURSOR;

static double primary()
{

}

static double term()
{

}

static double expression()
{
	double var = term();
	int tokenId = getNextToken();
	while(1) {
		if (TOKEN_PLUS == tokenId){
			var += term();
			tokenId = getNextToken();
		}else if (TOKEN_MINUS == tokenId) {
			var -= term();
			tokenId = getNextToken();
		}else if (TOKEN_NEWLINE == tokenId) {
			break;
		}
	}
	return var;
}

double statement()
{
	return expression();
}
