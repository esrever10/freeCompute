/*************************************************************************
	> File Name: parser.c
	> Author: ellochen
	> Mail: god_mode@yeah.net
	> Created Time: Wed May  8 23:24:27 2013
 ************************************************************************/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "parser.h"
#include "lex.h"
#include "token.h"
#include "symtbl.h"
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
	Identifier
	Number
	( Expression )
	- Primary
	+ Primary

Number:
	double
*/

extern char *CURSOR;
extern SymTbl *SYMTBL;

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
			exit(0);
		}
	}else if (TOKEN_PLUS == token.type) {
		return primary();
	}else if (TOKEN_MINUS == token.type) {
		return -primary();
	}else if (TOKEN_ID == token.type) {
		Symbol *pSymbol = (Symbol *)malloc(sizeof(Symbol));
		pSymbol->key = token.var.p;
		if (symtblLookup((void **)&pSymbol) < 0) {
			printf("变量未定义\n");
			exit(0);
		}else {
			return pSymbol->var;
		}
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

#define BUCKET_NUM 256

static int hash(const void *dat)
{
	const Symbol *pSymbol = (Symbol *)dat;
	const char *ptr = (const char *)pSymbol->key;
	unsigned int val = 0;

	while (*ptr != '\0') {
		unsigned int tmp;
		val = (val << 4) + (*ptr);

		if (tmp = (val & 0xf0000000)) {
			val = val ^ (tmp >> 24);
			val = val ^ tmp;
		}
		ptr++;
	}
	return val % BUCKET_NUM; 
}

static int match(const void *dat1, const void *dat2)
{
	const Symbol *pSymbol1 = (Symbol *)dat1;
	const Symbol *pSymbol2 = (Symbol *)dat2;
	return strcmp(pSymbol1->key, pSymbol2->key);
}

static void destroy(void *dat)
{
	Symbol *pSymbol = (Symbol *)dat;
	free(pSymbol->key);
	free(pSymbol);
}

double statement()
{
	char *back = CURSOR;
	struct Token token = getNextToken();
	if (TOKEN_ID == token.type && TOKEN_EQUAL == getNextToken().type) {
			double var = expression();
			Symbol *pSymbol = (Symbol *)malloc(sizeof(Symbol));
			pSymbol->var = var;
			pSymbol->key = token.var.p;
			if (symtblInsert((void *)pSymbol) < 0) {
				symtblUpdate((void *)pSymbol);
			}
			return var;
	}else { 
		CURSOR = back;
		return expression();
	}
}

int parserInit()
{
	SYMTBL = (SymTbl *)malloc(sizeof(SymTbl));
	symtblInit(BUCKET_NUM, hash, match, destroy);
}

int parserDestroy()
{
	symtblDestroy();
}