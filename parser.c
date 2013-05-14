/*************************************************************************
	> File Name: parser.c
	> Author: ellochen
	> Mail: god_mode@yeah.net
	> Created Time: Wed May  8 23:24:27 2013
 ************************************************************************/
#include <stdio.h>
#include "parser.h"
#include "lex.h"
#include "token.h"
/*
Statement:
	Identifier = Expression
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

static double expression();
static double primary()
{
	char *back = CURSOR;
	struct Token token = getNextToken();
	if (TOKEN_DOUBLECONST == token.type) {
		return token.var.d;
	}else if (TOKEN_LPAREN == token.type) {
		double var = expression();
		back = CURSOR;
		token = getNextToken();
		if (TOKEN_RPAREN == token.type) {
			return var;
		}else {
			printf("括号不匹配,错误字符:%d\n",token.type);
			return -1;
		}
	}else if (TOKEN_PLUS == token.type) {
		return primary();
	}else if (TOKEN_MINUS == token.type) {
		return -primary();
	}else {
		CURSOR = back;
		return 1;
	}
}

static double term()
{
	double var = primary();
	char *back = CURSOR;
	struct Token token = getNextToken();
	while(1) {
		if (TOKEN_STAR == token.type) {
			var *= primary();
			back = CURSOR;
			token = getNextToken();
		}else if (TOKEN_SLASH == token.type) {
			double temp = primary();
			if (0 == temp) {
				printf("除数不能为0\n");
				return -1;
			}else {
				var /= temp;
			}
			back = CURSOR;
			token = getNextToken();
		}else if (TOKEN_LINEEND == token.type) {
			break;
		}else {
			CURSOR = back;
			break;
		}
	}
	return var;
}

static double expression()
{
	double var = term();
	char *back = CURSOR;
	struct Token token = getNextToken();
	while(1) {
		if (TOKEN_PLUS == token.type){
			var += term();
			back = CURSOR;
			token = getNextToken();
		}else if (TOKEN_MINUS == token.type) {
			var -= term();
			back = CURSOR;
			token = getNextToken();
		}else if (TOKEN_LINEEND == token.type) {
			break;
		}else {
			CURSOR = back;
			return var;
		}
	}
	return var;
}

double statement()
{
	char *back = CURSOR;
	struct Token token = getNextToken();
	if (TOKEN_ID == token.type && TOKEN_EQUAL == getNextToken().type) {
			double var = expression();
	}else { 
		CURSOR = back;
		return expression();
	}
}
