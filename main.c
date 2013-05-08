/*************************************************************************
	> File Name: main.c
	> Author: ellochen
	> Mail: god_mode@yeah.net
	> Created Time: Mon Apr 29 21:36:12 2013
 ************************************************************************/
#include <stdio.h>
#include <stdlib.h>

#define LINE_MAX 256

char *CURSOR = 0;

void help()
{
	printf("Welcome to freeCompute!\n");
}

/*
Statement:
	Expression

Expression:
	Term
	Expression + Term
	Expression - Term

Term:
	Primary
	Term * Primary
	Term / Primary

Primary:
	Number
	( Expression )
	- Primary
	+ Primary

Number:
	float
*/
void processOneLine()
{
	
}

int main(int argc, char*argv[])
{
	if (1 == argc){
		char *line = (char*)malloc(LINE_MAX);
		help();
		printf(">>>");
		while(fgets(line,LINE_MAX,stdin) != NULL) {
			CURSOR = line;
			processOneLine();
			printf(">>>");
		}
	}
	return 0;
}
