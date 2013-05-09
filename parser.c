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
	double
*/

extern char *CURSOR;

static double primary()
{
	Token token = getNextToken();
	if (TOKEN_DOUBLECONST == token.type) {
		return token.var.d;
	}else if (TOKEN_LPAREN == token.type) {
		double var = expression();
		token = getNextToken();
		if (TOKEN_RPAREN == token.type) {
			return var;
		}else {
			printf("括号不匹配\n");
			return -1;
		}
	}else if (TOKEN_PLUS == token.type) {
		return primary();
	}else if (TOKEN_MINUS == token.type) {
		return -primary();
	}
}

static double term()
{
	double var = primary();
	Token token = getNextToken();
	while(1) {
		if (TOKEN_STAR == token.type) {
			var *= primary();
			token = getNextToken();
		}else if (TOKEN_SLASH == token.type) {
			double temp = primary();
			if (0 == temp) {
				printf("除数不能为0\n");
				return -1;
			}else {
				var /= temp;
			}
			token = getNextToken();
		}else if (TOKEN_NEWLINE == token.type) {
			break;
		}
	}
}

static double expression()
{
	double var = term();
	Token token = getNextToken();
	while(1) {
		if (TOKEN_PLUS == token.type){
			var += term();
			token = getNextToken();
		}else if (TOKEN_MINUS == token.type) {
			var -= term();
			token = getNextToken();
		}else if (TOKEN_NEWLINE == token.type) {
			break;
		}
	}
	return var;
}

double statement()
{
	return expression();
}
