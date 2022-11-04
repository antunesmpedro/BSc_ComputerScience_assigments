#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
int main(int argc, char* argv[]) {
/* fork a child process */
	int pid = fork();
/* fork another child process */
	pid = fork();
/* and fork another */
	pid = fork();

	printf("%d\n", getpid());
	return EXIT_SUCCESS;
}

// fica com 8 processos
