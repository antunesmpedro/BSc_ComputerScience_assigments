#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int main(int argc, char* argv[]) {
	char cwd[PATH_MAX];
	getcwd(cwd,sizeof(cwd));
	printf("pathname: %s\n", cwd);

	return EXIT_SUCCESS;
}