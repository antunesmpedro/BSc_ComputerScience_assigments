#include <sys/wait.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

#define READ 0
#define WRITE 1
#define LINESIZE 25

int main(int argc, char* argv[]) {
	int n, r, fd[2];
	pid_t pid;
	char line[LINESIZE];
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
		close(fd[WRITE]);
		 printf("PARENT=> Parent process with pid %d\n", getpid());
		while ( (r = read(fd[READ], line, LINESIZE)) != 0) {
			r = write(STDOUT_FILENO,line, r);
		}
		if (r < 0)
			fprintf(stderr, "Unable to read to pipe: %s\n", strerror(errno));
		close(fd[READ]);
		exit(EXIT_SUCCESS);		
	}
	else {
		/* child */
		close(fd[READ]);
		pid_t p = getppid();
		printf("CHILD => Messaging the parent process (pid %d):\n", p);
		FILE* fp = fopen(argv[1],"r");
		if(fp == NULL) {
		  printf("%s: cannot open %s\n", argv[0], argv[1]);
		  return EXIT_FAILURE;
		}
		while(fread(line, 1, 1, fp) != 0){
			//snprintf(line,2,"%c",c);
			if ((n = write(fd[WRITE], line, 1)) < 0 ) {
				fprintf(stderr, "Unable to write from pipe: %s\n", strerror(errno));
			}
		}
		fclose(fp);
		close(fd[WRITE]);
		/* exit gracefully */
		exit(EXIT_SUCCESS);
	}
}