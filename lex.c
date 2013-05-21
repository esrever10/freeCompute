/*************************************************************************
	> File Name: lex.c
	> Author: ellochen
	> Mail: god_mode@yeah.net
	> Created Time: Mon Apr 29 21:57:57 2013
 ************************************************************************/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "token.h"
#include "lex.h"
typedef struct Token (*Matcher)(void);
char *CURSOR = 0;
#define END_OF_FILE  255
static Matcher matchers[END_OF_FILE+1];

static struct Token matchInt(void)
{
	int i = 0;
	char *start = CURSOR;
	CURSOR += 1;
	while (IsDigit(*CURSOR)) {
		CURSOR += 1;
	}
	i = atoi(start);
	struct Token token;
	token.var.i = i;
	token.type = TOKEN_INTCONST;
	return token;
}

static struct Token matchDouble(void)
{
	double d = 0;
	char *start = CURSOR;
	CURSOR += 1;
	while (IsDigit(*CURSOR)) {
		CURSOR += 1;
	}
	if ('.' == *CURSOR) {
		CURSOR += 1;
		while (IsDigit(*CURSOR)) {
			CURSOR += 1;
		}	
	}
	d = strtod(start,0);
	struct Token token;
	token.var.d = d;
	token.type = TOKEN_DOUBLECONST;
	return token;
}

static struct Token matchPlus(void)
{
	CURSOR += 1;
	struct Token token;
	token.type = TOKEN_PLUS;
	return token;
}

static struct Token matchMinus(void)
{
	CURSOR += 1;
	struct Token token;
	token.type = TOKEN_MINUS;
	return token;
}

static struct Token matchStar(void)
{
	CURSOR += 1;
	struct Token token;
	token.type = TOKEN_STAR;
	return token;
}

static struct Token matchSlash(void)
{
	CURSOR += 1;
	struct Token token;
	token.type = TOKEN_SLASH;
	return token;
}

static struct Token matchBadChar(void)
{
	printf("无法识别的字符:%c\n",*CURSOR);
	exit(0);
}

static struct Token matchLineEnd(void)
{
	CURSOR += 1;
	struct Token token;
	token.type = TOKEN_LINEEND;
	return token;
}

static struct Token matchLparen(void)
{
	CURSOR += 1;
	struct Token token;
	token.type = TOKEN_LPAREN;
	return token;
}

static struct Token matchRparen(void)
{
	CURSOR += 1;
	struct Token token;
	token.type = TOKEN_RPAREN;
	return token;
}

static struct Token matchIdentifier(void)
{
	char *start = CURSOR;
	CURSOR += 1;
	while (IsLetterOrDigit(*CURSOR)) {
		CURSOR += 1;
	}
	struct Token token;
	token.type = TOKEN_ID;
	char *tokenVar = (char*)malloc(CURSOR - start);
	strncpy(tokenVar,start,CURSOR - start);
	token.var.p = (void*)tokenVar;
	return token;
}

static struct Token matchEqual(void)
{
	CURSOR += 1;
	struct Token token;
	token.type = TOKEN_EQUAL;
	return token;
}

void lexerInit(void)
{
	int i;
	for (i = 0; i < END_OF_FILE + 1; i++) {
		if (IsDigit(i)) {
			matchers[i] = matchDouble;
		}else if (IsLetter(i)) {
			matchers[i] = matchIdentifier;
		}else {
			matchers[i] = matchBadChar;
		}
	}
	matchers['\0'] = matchLineEnd;
	matchers['+'] = matchPlus;
	matchers['-'] = matchMinus;
	matchers['*'] = matchStar;
	matchers['/'] = matchSlash;
	matchers['('] = matchLparen;
	matchers[')'] = matchRparen;
	matchers['='] = matchEqual;
}

static void SkipWhiteSpace(void)
{
	while (*CURSOR == '\t' || *CURSOR == '\v' || *CURSOR == '\f' || *CURSOR == ' ' ||
	       *CURSOR == '\r' || *CURSOR == '\n') {
			   CURSOR += 1;
	}
}

struct Token getNextToken()
{
	SkipWhiteSpace();
	return (matchers[*CURSOR])();	
}
