#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define MAXSIZE 60000

//char* cmd1[] = {"ls", "-l", NULL};
//char* cmd2[] = {"wc", "-l", NULL};
//char* cmd3[] = {};

char* cmd1[MAXSIZE];
char* cmd2[MAXSIZE];

//char** cmd1 = (char**) malloc(MAXSIZE * sizeof(char));
//char** cmd2 = (char**) malloc(MAXSIZE * sizeof(char));

// split commands with an delimiter argument to a array of commands
void split(char* str, char** v){
	int i = 0;
    char* p = strtok(str, " ");
	do {
		v[i] = p;
		i++;
	} while( (p = strtok(NULL, " ")) != NULL );
    v[i] = NULL;
}

int main (int argc, char* argv[]) {
	int fd[2];
	pid_t pid;
	int i=0;
	
	char* s1 = strtok(argv[1], "|");
    char* s2 = strtok(NULL, "|");

	split(s1, cmd1);
	split(s2, cmd2);
	
	if (pipe(fd) < 0) {
		/* pipe error */
	} if ((pid = fork()) < 0) {
		/* fork error */
	} if (pid > 0) {
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);  // stdout to pipe
		close(fd[1]);
		// parent writes to the pipe
		if (execvp(cmd1[0], cmd1) < 0) {
			/* exec error */
		}
	} else {
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO); // stdin from pipe
		close(fd[0]);
		if (execvp(cmd2[0], cmd2) < 0) {
			/* exec error */
		}
	}
	return 0;
}