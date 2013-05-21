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
	
	int (*h)(const void *dat);
	int (*match)(const void *dat1, const void *dat2);
	void (*destroy)(void *dat);

	int size;
	List *table;
}SymTbl;

extern SymTbl *SYMTBL;

int symtblInit(int buckets, int (*h)(const void *dat),
	int (*match)(const void *dat1, const void *dat2),
	void (*destroy)(void *dat));

void symtblDestroy();

int symtblInsert(const void *data);

int symtblRemove(void **data);

int symtblLookup(void **data);

#define symtblSize() ((SYMTBL)->size)

#endif
