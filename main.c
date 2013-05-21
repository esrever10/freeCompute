/*************************************************************************
	> File Name: main.c
	> Author: ellochen
	> Mail: god_mode@yeah.net
	> Created Time: Mon Apr 29 21:36:12 2013
 ************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parser.h"
#include "lex.h"
#include "symtbl.h"

#define LINE_MAX 256

void help()
{
	printf("Welcome to freeCompute!\n");
}

void processOneLine()
{
	printf("%lf\n",statement());
}

int main(int argc, char*argv[])
{
	if (1 == argc){
		lexerInit();
		char *line = (char*)malloc(LINE_MAX);
		help();
		printf(">>>");
		while(fgets(line,LINE_MAX,stdin) != NULL) {
			CURSOR = line;
			processOneLine();
			memset(line,0,strlen(line));
			printf(">>>");
		}
	}
	return 0;
}
