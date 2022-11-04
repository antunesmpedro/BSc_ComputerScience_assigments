#include <stdio.h>
#include <string.h>
#include <stdlib.h>
//ctrl+shift+p

int f(char* content) {
	int size = strlen(content);
	char* str = (char*) malloc(size * sizeof(char));
	int result = 2;
	(void)strcpy(str, content);
	free(str);
	return result;
}

int main(int argc, char* argv[]) {
	if (argc == 2)
		printf("result = %d\n", f(argv[1]));
	return EXIT_SUCCESS;
}