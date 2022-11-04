#include <sys/wait.h>
#include <sys/socket.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define SOCK0 0
#define SOCK1 1
#define DATA0 "In every walk with nature..."
#define DATA1 "...one receives far more than he seeks."
/* by John Muir */
int main(int argc, char* argv[]) {
	int   sockets[2];
	char*  buf;
	int i=0;
	long bufsize;
	pid_t pid;
	if (socketpair(AF_UNIX, SOCK_STREAM, 0, sockets) < 0) {
		perror("opening stream socket pair");
		exit(1);
	}
	FILE* f;
	f = fopen(argv[1],"r");
	fseek(f, 0, SEEK_END);
	bufsize = ftell(f);
	fseek(f, 0, SEEK_SET);
	buf = (char*) malloc(sizeof(char)*bufsize);

	if ((pid = fork()) < 0) {
		perror("fork");
		return EXIT_FAILURE;
	} else if (pid == 0) {
/* this is the child */
		close(sockets[SOCK0]);

		if (read(sockets[SOCK1], buf, bufsize) < 0)
			perror("CHILD=>reading stream message");
		printf("FILHO LEU\n");
		//printf("message from %d-->%s\n", getppid(), buf);
		while(buf[i] != '\0'){
			buf[i] = toupper(buf[i]);
			i++;
		}
		if (write(sockets[SOCK1], buf, bufsize) < 0)
			perror("CHILD=>writing stream message");
		printf("FILHO ESCREVEU\n");
		close(sockets[SOCK1]);
/* leave gracefully */
		return EXIT_SUCCESS;
	}else {
/* this is the parent */
		close(sockets[SOCK1]);
		fread(buf,bufsize,1,f);
		fclose(f);
		if (write(sockets[SOCK0], buf, bufsize) < 0)
			perror("PARENT=>writing stream message");
/* wait for child and exit */
		printf("PAI ESCREVEU\n");
		if (waitpid(pid, NULL, 0) < 0) {
			perror("PARENT=>did not catch child exiting");
			return EXIT_FAILURE;
		}
		if (read(sockets[SOCK0], buf, bufsize) < 0)
			perror("reading stream message");
		//printf("message from %d-->%s\n", pid, buf);
		printf("PAI LEU\n");
		printf("%s\n",buf);
		close(sockets[SOCK0]);

		return EXIT_SUCCESS;
	}
}