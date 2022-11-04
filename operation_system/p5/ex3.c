#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

//int value = 5;
int main(int argc, char* argv[]) {
	int value = 5;
	pid_t pid;
	if ((pid = fork()) < 0 ) {
		printf("%s: cannot fork()\n", argv[0]);
		return EXIT_FAILURE;
	}
	else if (pid == 0) {
/* child process */
		value += 15;
		printf("%d\n", pid);
		printf("CHILD: value = %d\n",value);
		return EXIT_SUCCESS;
	}
	else {
/* parent process */
		printf("%d\n", pid);
		if (waitpid(pid, NULL, 0) < 0) {
			printf("%s: cannot wait for child\n", argv[0]);
			return EXIT_FAILURE;
		}
		printf("pai %d\n", pid);
		printf("PARENT: value = %d\n",value);
		return EXIT_SUCCESS;
	}
}