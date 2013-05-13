/*************************************************************************
	> File Name: symbol.c
	> Author: ellochen
	> Mail: god_mode@yeah.net
	> Created Time: Mon May 13 20:01:42 2013
 ************************************************************************/

#include <stdlib.h>
#include <string.h>
#include "symbol.h"

static struct Symbol *initSymbol(char *name, union TokenVar *var)
{
	struct Symbol *symbol = (struct Symbol*)malloc(sizeof(struct Symbol));
	if (NULL == symbol) return NULL;
	strncpy(symbol->name, name, strlen(name));
	symbol->var.d = var->d;
	symbol->var.i = var->i;
	strncpy(symbol->var.p, var->p, strlen(var->p));
	return symbol;
}

struct SymbolList *initSymbolList()
{
	struct SymbolList *list = (struct SymbolList*)malloc(sizeof(struct SymbolList));
	if (NULL == list) return NULL;
}

void insertSymbol(struct SymbolList *list, struct Symbol *symbol)
{

}

void symbolVar(struct SymbolList *list, char *name)
{

}


void cleanSymbolList(struct SymbolList *list)
{

}

