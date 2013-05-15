/*************************************************************************
	> File Name: symbol.h
	> Author: ellochen
	> Mail: god_mode@yeah.net
	> Created Time: Mon May 13 20:01:50 2013
 ************************************************************************/
#ifndef _SYMTBL_H_
#define _SYMTBL_H_

#include "token.h"

#define MAX_LEN 256
struct Symbol{
	char name[MAX_LEN];
	double var;
};

#endif
