/*************************************************************************
	> File Name: lex.cc
	> Author: ellochen
	> Mail: god_mode@yeah.net
	> Created Time: Mon Apr 29 21:57:57 2013
 ************************************************************************/
typedef int (*Matcher)(void);
extern char* CURSOR;
static Matcher matchers[256];
static int matchNum(void)
{
	
}

static int matchPlus(void)
{
	
}

static int matchMinus(void)
{
	
}

static int matchStar(void)
{
	
}

static int matchSlash(void)
{

}

void InitLexer(void)
{
	int c;
	for(c = '0'; c <= '9'; ++c){
		matchers[c] = matchNum;
	}
	matchers['+'] = matchPlus;
	matchers['-'] = matchMinus;
	matchers['*'] = matchMinus;
	matchers['/'] = matchMinus;
}

void getNextToken()
{
	(matchers[*CURSOR])();	
}
