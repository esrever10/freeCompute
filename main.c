/*************************************************************************
	> File Name: main.c
	> Author: ellochen
	> Mail: god_mode@yeah.net
	> Created Time: Mon Apr 29 21:36:12 2013
 ************************************************************************/
#include <stdio.h>
#include <stdlib.h>

#define LINE_MAX 256

int main()
{
	char line[LINE_MAX] = {0};
	while(fgets(line,LINE_MAX,stdin) != NULL) {
		puts(line);
	}
	return 0;
}
