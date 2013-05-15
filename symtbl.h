/*************************************************************************
	> File Name: symbol.h
	> Author: ellochen
	> Mail: god_mode@yeah.net
	> Created Time: Mon May 13 20:01:50 2013
 ************************************************************************/
//the implement refers to <<Mastering Algorithms with C>>
#ifndef _SYMTBL_H_
#define _SYMTBL_H_

#include "list.h"

typedef struct _SymTbl {
	int buckets;
	
	int (*h)(const void *key);
	int (*match)(const void *key1, const void *key2);
	void (*destroy)(void *dat);

	int size;
	List *table;
}SymTbl;

int symtblInit(SymTbl *tbl, int buckets, int (*h)(const void *key), 
		int(*match)(const void *key1, const void *key2),
		void (*destroy)(void *data));

void symtblDestory(SymTbl *tbl);

int symtblInsert(SymTbl *tbl, const void *data);

int symtblRemove(SymTbl *tbl, void **data);

int symtblLookup(const SymTbl *tbl, void **data);

#define symtblSize(tbl) ((tbl)->size)

#endif
