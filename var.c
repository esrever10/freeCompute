#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "lex.h"
#include "var.h"

extern char *CURSOR;
/* evalute the variable and return its value
 */
struct Token varEval(){
	char *tok;
	char var[VAR_LEN];
	struct Token val;
	char pattern_set[] = "set";
	char str[100];
	strcpy(str, CURSOR);
	
	tok = strtok(str, " \t");

	if(!strcmp(pattern_set, tok)){
		tok = strtok(NULL, " \t");
		strcpy(var, tok);	
		tok = strtok(NULL, " \t");
		CURSOR = tok;
		varIni(var, val=getNextToken());
		return val;
	}

	tok = strtok(str, " \t\n+-*/()");
	CURSOR += strlen(tok);
	return searchTrie(tok);
}

Node* NodeIni(){
	Node *p = malloc(sizeof(Node));
	memset(p->l, 0, sizeof(Node *)*256);
	p->isVar = 0;
	return p;
}

int varIni(char *n_var, struct Token t_val){
	Node* p = v_root;		
	while(*n_var){
		if(!(p->l[*n_var]))
			p->l[*n_var] = NodeIni();
		p = p->l[*n_var];
		n_var++;
	}
	p->isVar = 1;
	p->t_val = t_val;
}

struct Token searchTrie(char *n_var){
	struct Token t_null;
	t_null.type = TOKEN_INVALID;
	Node* p	= v_root;
	while(*n_var){
		if(!(p->l[*n_var]))
			return t_null;
		p = p->l[*n_var];
		n_var++;
	}
	if(p->isVar)
		return p->t_val;
	return t_null;
}
