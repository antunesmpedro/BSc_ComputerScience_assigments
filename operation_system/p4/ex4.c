#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <fcntl.h>

int main(int argc, char* argv[]) {

	if (argc != 2) {
		fprintf(stderr, "usage: %s file\n", argv[0]);
		return EXIT_FAILURE;
	}

	struct stat info;
	if(lstat(argv[1], &info) == -1){

	/* check if file can be opened and is readable */
		int fd = open(argv[1], O_CREAT);
		if (fd == -1) {
			printf("error: cannot open %s\n", argv[1]);
			return EXIT_FAILURE;
		}

		mode_t newperms = (mode_t)0;
		newperms |= S_IRUSR | S_IWUSR;
		newperms |= S_IRGRP;
		newperms |= S_IROTH;

		if (chmod(argv[1], newperms) == -1) {
			(void)fprintf(stderr, "%s: cannot chmod %s\n", argv[0], argv[1]);
			return EXIT_FAILURE;
		}
		else
			printf("file %s new permissions: 644\n",argv[1]);
	}
	else{
		//time_t t;
		//time(&t);
		//struct tm *mytime = localtime(&t);
		utimes(argv[1],NULL);
		printf("last_update: %s\n", ctime(&info.st_mtime));
		//info.st_mtime = time(0);
		
	}
	return EXIT_SUCCESS;
}