#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
typedef enum amode {UPPER=0, LOWER=1} mode;
#define CONVERT(X,Y) ((X)==UPPER)? toupper(Y): tolower(Y)
#define LINESIZE 256
int main(int argc, char* argv[]) {
/* check if 1 args available */
	if (argc != 2) {
		printf("usage: chcase  file\n");
		return EXIT_FAILURE;
	}
	char line[LINESIZE];
/* check if option is valid 
	if(strcmp(argv[1], "-u") == 0 )
		m = UPPER;
	else
		if(strcmp(argv[1], "-l") == 0 )
			m = LOWER;
		else {
			printf("usage: chcase -u|-l file\n");
			return EXIT_FAILURE;
		}
	*/

	/* check if argv[2] can be opened and is readable */
	FILE* fp = fopen(argv[1], "r");
	if(fp == NULL) {
		printf("%s: cannot open %s\n", argv[0], argv[1]);
		return EXIT_FAILURE;
	}
	char c;
	int cont = 0;
	int lines = 0;
	/* get one char at a time and print upper or lower case */
	while(fread(&c, 1, 1, fp) != 0) {
		cont++;
		if(c == '\n')
			lines++;
	}

	fprintf(stdout, "%s: chars: %d ; lines: %d\n", argv[1], cont, lines);
	snprintf(line, LINESIZE, "Hello! I’m your parent pid %d!\n", getpid());
	/* close file */
	fclose(fp);
	return EXIT_SUCCESS;
}