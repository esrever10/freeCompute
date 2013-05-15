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

int symtblInit(SymTbl *tbl, int buckets, int (*h)(const void *key), 
		int(*match)(const void *key1, const void *key2),
		void (*destroy)(void *data))
{
	if ((tbl->table = (List *)malloc(buckets * sizeof(List))) == NULL) {
		return -1;
	}
	tbl->buckets = buckets;
	for (int i = 0; i < tbl->buckets; ++i) {
		listInit(&tbl->table[i], destroy);
	}
	tbl->h = h;
	tbl->match = match;
	tbl->destroy = destroy;
	tbl->size = 0;
	return 0;
}

void symtblDestory(SymTbl *tbl)
{
	for (int i = 0; i < tbl->buckets; ++i) {
		listDestory(&tbl->table[i]);
	}
	free(tbl->table);
	memset(tbl,0,sizeof(SymTbl));
}

int symtblInsert(SymTbl *tbl, const void *data)
{
	void *temp = (void *)data;
	if (symtblLookup(tbl, &temp) == 0) {
		return -1;
	}
	int bucket = tbl->h(data) % tbl->buckets;
	int retval = 0;
	if ((retval = listInsertNext(&tbl->table[bucket], NULL, data)) == 0) {
		tbl->size += 1;
	}
	return retval;
}

int symtblRemove(SymTbl *tbl, void **data)
{
	int bucket = tbl->h(*data) % tbl->buckets;
	ListElmt *prev = NULL;
	for (ListElmt *element = listHead(&tbl->table[bucket]); 
			element != NULL; 
			element = listNext(element)) {
		if (tbl->match(*data, listData(element))) {
			if (listRemoveNext(&tbl->table[bucket], prev, data) == 0) {
				tbl->size -= 1;
				return 0;
			}
		}else {
			return -1;
		}
		prev = element;
	}
	return -1;
}

int symtblLookup(const SymTbl *tbl, void **data)
{
	int bucket = tbl->h(*data) % tbl->buckets;
	for (ListElmt *element = listHead(&tbl->table[bucket]);
			element != NULL;
			element = listNext(element)) {
		if (tbl->match(*data, listData(element))) {
			*data = listData(element);
			return 0;
		}
	}
	return -1;
}

