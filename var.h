#include"token.h"
#ifndef _VAR_H_
#define _VAR_H_

#define VAR_LEN 100

struct Node{
	struct Node *l[256];
	int isVar;
	struct Token t_val;
	int v;
};

typedef struct Node Node;
Node *v_root;

struct Token varEval();
int varIni(char *n_var, struct Token t_val);
//int varIni(char *n_var, int v);
struct Token searchTrie(char *n_var);
Node* NodeIni(); 

#endif
