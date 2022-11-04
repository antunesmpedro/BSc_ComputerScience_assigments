#include <sys/wait.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <limits.h>
#define PP_RD 0
#define PP_WR 1
int main(int argc, char* argv[]) {
	int   n, r, fd[2];
	pid_t pid;
	char  line[BUFSIZ];
	if (pipe(fd) < 0) {
		perror("pipe error");
		exit(EXIT_FAILURE);
	}
	if ((pid = fork()) < 0) {
		perror("fork error");
		exit(EXIT_FAILURE);
	}
	else if (pid > 0) {
/* parent */
		FILE * file;
		file = fopen(argv[1],"r");
		close(fd[PP_RD]);
		if(file){
			printf("PARENT=> Parent process with pid %d\n", getpid());
			printf("PARENT=> Messaging the child process (pid %d):\n", pid);
			while(fread(line,BUFSIZ,1,file) != EOF) {
				if ((r = write(fd[PP_WR], line, BUFSIZ+1)) < 0) {
					//r=write(fd[PP_WR],"\n",strlen("\n"));
					fprintf(stderr, "Unable to write to pipe: %s\n", strerror(errno));
				}
			}
		}
		else {
			perror("file error");
			exit(EXIT_FAILURE);
		}
		close(fd[PP_WR]);
		fclose(file);
/* wait for schild and exit */
		if ( waitpid(pid, NULL, 0) < 0) {
			fprintf(stderr, "Cannot wait for child: %s\n", strerror(errno));
		}
		exit(EXIT_SUCCESS);
	}
	else {
/* child */
		close(fd[PP_WR]);
		printf("CHILD=> Child process with pid %d\n", getpid());
		printf("CHILD=> Receiving message from parent (pid %d):\n", getppid());
		if ((n = read(fd[PP_RD], line, BUFSIZ)) < 0 ) {
			fprintf(stderr, "Unable to read from pipe: %s\n", strerror(errno));
		}
		close(fd[PP_RD]);
/* write message from parent */
		write(STDOUT_FILENO, line, strlen(line));
/* exit gracefully */
		exit(EXIT_SUCCESS);
	}
}
