/*************************************************************************
	> File Name: list.c
	> Author: ellochen
	> Mail: god_mode@yeah.net
	> Created Time: Wed May 15 22:35:16 2013
 ************************************************************************/
#include <stdlib.h>
#include <string.h>
#include "list.h"

void listInit(List *list, void (*destroy)(void *data))
{
	list->size = 0;
	list->destroy = destroy;
	list->head = NULL;
	list->tail = NULL;
}

void listDestory(List *list)
{
	void *data;
	while (listSize(list) > 0) {
		if (listRemoveNext(list, NULL, (void **)&data) == 0
				&& list->destroy != NULL) {
			list->destroy(data);
		}
	}
	memset(list, 0, sizeof(List));
}

int listInsertNext(List *list, ListElmt *element, const void *data)
{
	ListElmt *newElement;
	if ((newElement = (ListElmt *)malloc(sizeof(ListElmt))) == NULL) {
		return -1;
	}
	newElement->data = (void *)data;
	if (element == NULL) {
		if (listSize(list) == 0) {
			list->tail = newElement;
		}
		newElement->next = list->head;
		list->head = newElement;
	}else {
		if (element->next == NULL) {
			list->tail = newElement;
		}
		newElement->next = element->next;
		element->next = newElement;
	}
	list->size += 1;
	return 0;
}

int listRemoveNext(List *list, ListElmt *element, void **data)
{
	ListElmt *oldElement;
	if (listSize(list) == 0) {
		return -1;
	}
	if (element == NULL) {
		*data = list->head->data;
		oldElement = list->head;
		list->head = list->head->next;
		if (listSize(list) == 1) {
			list->tail = NULL;
		}
	}else {
		if (element->next = NULL) {
			return -1;
		}
		*data = element->next->data;
		oldElement = element->next;
		element->next = element->next->next;
		if (element->next == NULL) {
			list->tail = element;
		}
		free(oldElement);
		list->size -= 1;
		return 0;
	}
}
