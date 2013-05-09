/*************************************************************************
	> File Name: lex.c
	> Author: ellochen
	> Mail: god_mode@yeah.net
	> Created Time: Mon Apr 29 21:57:57 2013
 ************************************************************************/
#include "token.h"
#include "lex.h"
typedef struct Token (*Matcher)(void);
extern char* CURSOR;
static Matcher matchers[256];

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

void InitLexer(void)
{
	int c;
	for(c = '0'; c <= '9'; ++c){
		matchers[c] = matchDouble;
	}

	matchers['+'] = matchPlus;
	matchers['-'] = matchMinus;
	matchers['*'] = matchMinus;
	matchers['/'] = matchMinus;
}

struct Token getNextToken()
{
	return (matchers[*CURSOR])();	
}
