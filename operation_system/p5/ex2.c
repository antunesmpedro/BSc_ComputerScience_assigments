#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
int main(int argc, char* argv[]) {
	int pid, cont = 0;

	for (int i = 0; i < 4; i++){
		if(pid = fork() == 0){
			printf("- pid %d\n", getpid());
			cont++;
		}
		else {
			printf("- pid %d\n", getpid());
			cont++;
		}
	}
	return EXIT_SUCCESS;
}

// | sort | uniq -c