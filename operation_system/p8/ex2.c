#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <string.h>

#define MAXSIZE 25

int main(int argc, char* argv[]) {
	pid_t pid;
	char cmd[MAXSIZE];
	while(1){
		printf("$ ");
		scanf("%s", cmd);
		if(strcmp(cmd,"quit") == 0)
				break;	
		/* fork a child process */
		if ((pid = fork()) < 0 ) {
			printf("%s: cannot fork()\n", argv[0]);
			return EXIT_FAILURE;
		}
		else if (pid == 0) {/* child process */
			if (execlp(cmd,cmd,NULL) < 0) {
				printf("bummer, did not exec %s\n", argv[1]);
				return EXIT_FAILURE;
			}
		}
		else {
			/* parent process */
			if (waitpid(pid, NULL, 0) < 0) {
				printf("%s: cannot wait for child\n", argv[0]);
				return EXIT_FAILURE;
			}
			printf("child exited\n");
		}
	}
	return EXIT_SUCCESS;
}