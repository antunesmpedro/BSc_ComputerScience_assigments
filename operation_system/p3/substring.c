#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX_STR_SIZE  64

int main(int argc, char* argv[]) {
// exercicio 1.2
/*
	if(strstr(argv[2],argv[1]) != NULL)
		printf("string1:%s in string2:%s\n",argv[1],argv[2]);
	else
		printf("string1:%s not in string2:%s\n",argv[1],argv[2]);
	return EXIT_SUCCESS;
*/

//exercicio 1.3
	int ocorre = 0;
	char *old;
	while((old = strstr(argv[2],argv[1])) != NULL){
		printf("%s\n",argv[2]);
		ocorre++;
		argv[2]=old+1;
		printf("%s\n",argv[2]);
	}

	if(ocorre == 0)
		printf("string1:%s not in string2:%s\n",argv[1],argv[2]);
	else
		printf("string1:%s are %d times in string2:%s\n",argv[1],ocorre,argv[2]);
	return EXIT_SUCCESS;
}