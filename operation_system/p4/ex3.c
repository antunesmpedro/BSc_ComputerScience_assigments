#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char* argv[]) {
	int countbytes = 0;
	int countblocks = 0;
	struct stat info;

	if (argc < 2) {
		fprintf(stderr, "usage: %s file\n", argv[0]);
		return EXIT_FAILURE;
	}
	int i;
	for(i=1; i< argc; i++){
		printf("\nFILE: %s\n", argv[i]);

		if (lstat(argv[i], &info) == -1) {
			fprintf(stderr, "fsize: Can’t stat %s\n", argv[i]);
			return EXIT_FAILURE;
		}
		printf("%s size: %d bytes, disk_blocks: %d last_update: %s owner_user: %d\n",
			argv[i], (int)info.st_size, (int)info.st_blocks,ctime(&info.st_mtime),info.st_uid);
		
		countbytes += (int) info.st_size;
		countblocks += (int) info.st_blocks;
	}

	printf("\ntotal blocks: %d total bytes: %d\n",countblocks,countbytes);
	return EXIT_SUCCESS;
}