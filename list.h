/*************************************************************************
	> File Name: list.h
	> Author: ellochen
	> Mail: god_mode@yeah.net
	> Created Time: Wed May 15 22:45:11 2013
 ************************************************************************/
//the implement refers to <<Mastering Algorithms with C>>
#ifndef _LIST_H_
#define _LIST_H_

typedef struct _ListElmt{
	void *data;
	struct _ListElmt *next;
}ListElmt;

typedef struct _List{
	int size;
	int (*match)(const void *key1, const void *key2);
	void (*destroy)(void *data);
	ListElmt *head;
	ListElmt *tail;
}List;

void listInit(List *list, void (*destory)(void *data));
void listDestory(List *list);
int listInsertNext(List *list, ListElmt *element, const void *data);
int listRemoveNext(List *list, ListElmt *element, void **data);

#define listSize(list) ((list)->size)
#define listHead(list) ((list)->head)
#define listTail(list) ((list)->tail)
#define listIsHead(list, element) ((element) == (list)->head ? 1 : 0)
#define listIsTail(element) ((element)->next == NULL ? 1 : 0)
#define listData(element) ((element)->data)
#define listNext(element) ((element)->next)

#endif

