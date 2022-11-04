#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX_STR_SIZE  64

int main(int argc, char* argv[]) {
	int i;
	char* p1 = (char*)malloc(MAX_STR_SIZE * sizeof(char));
	int length = strlen(argv[1]);
	
	strcpy(p1, argv[1]);
	for(i=0; i<length;i++){
		if(p1[i]<97)
			p1[i]=p1[i]+32;
	}

	printf("%s\n",p1);
	return EXIT_SUCCESS;
}