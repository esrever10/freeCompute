/*************************************************************************
	> File Name: symbol.c
	> Author: ellochen
	> Mail: god_mode@yeah.net
	> Created Time: Mon May 13 20:01:42 2013
 ************************************************************************/
//the implement refers to <<Mastering Algorithms with C>>
#include <stdlib.h>
#include <string.h>
#include "symtbl.h"

SymTbl * SYMTBL = NULL;

int symtblInit(int buckets, int (*h)(const void *key),
	int (*match)(const void *key1, const void *key2),
	void (*destroy)(void *dat))
{
	if ((SYMTBL->table = (List *)malloc(buckets * sizeof(List))) == NULL) {
		return -1;
	}
	SYMTBL->buckets = buckets;
	for (int i = 0; i < SYMTBL->buckets; ++i) {
		listInit(&SYMTBL->table[i], destroy);
	}
	SYMTBL->h = h;
	SYMTBL->match = match;
	SYMTBL->destroy = destroy;
	SYMTBL->size = 0;
	return 0;
}

void symtblDestroy()
{
	for (int i = 0; i < SYMTBL->buckets; ++i) {
		listDestory(&SYMTBL->table[i]);
	}
	free(SYMTBL->table);
	memset(SYMTBL,0,sizeof(SymTbl));
}

int symtblInsert(const void *data)
{
	void *temp = (void *)data;
	if (symtblLookup(&temp) == 0) {
		return -1;
	}
	int bucket = SYMTBL->h(data) % SYMTBL->buckets;
	int retval = 0;
	if ((retval = listInsertNext(&SYMTBL->table[bucket], NULL, data)) == 0) {
		SYMTBL->size += 1;
	}
	return retval;
}

int symtblRemove(void **data)
{
	int bucket = SYMTBL->h(*data) % SYMTBL->buckets;
	ListElmt *prev = NULL;
	for (ListElmt *element = listHead(&SYMTBL->table[bucket]); 
			element != NULL; 
			element = listNext(element)) {
		if (SYMTBL->match(*data, listData(element))) {
			if (listRemoveNext(&SYMTBL->table[bucket], prev, data) == 0) {
				SYMTBL->size -= 1;
				return 0;
			}
		}else {
			return -1;
		}
		prev = element;
	}
	return -1;
}

int symtblLookup(void **data)
{
	int bucket = SYMTBL->h(*data) % SYMTBL->buckets;
	for (ListElmt *element = listHead(&SYMTBL->table[bucket]);
			element != NULL;
			element = listNext(element)) {
		if (SYMTBL->match(*data, listData(element))) {
			*data = listData(element);
			return 0;
		}
	}
	return -1;
}

