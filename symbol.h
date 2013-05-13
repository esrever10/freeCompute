/*************************************************************************
	> File Name: symbol.h
	> Author: ellochen
	> Mail: god_mode@yeah.net
	> Created Time: Mon May 13 20:01:50 2013
 ************************************************************************/
#ifndef _SYMBOL_H_
#define _SYMBOL_H_

#include "token.h"

#define MAX_LEN 256
struct Symbol{
	char name[MAX_LEN];
	union TokenVar var;
};

struct SymbolList{
	struct Symbol symbol;
	struct SymbolList *next;
};

struct SymbolList *initSymbolList();
void insertSymbol(struct SymbolList *list, struct Symbol *symbol);
void symbolVar(struct SymbolList *list, char *name);
void cleanSymbolList(struct SymbolList *list);

#endif
