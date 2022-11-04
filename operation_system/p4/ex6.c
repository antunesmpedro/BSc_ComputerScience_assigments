#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include <string.h>
#include <time.h>

char * permessions(char * file) {
	struct stat st;
	char *modeval = malloc(sizeof(char)*9+1);
	if(stat(file,&st) == 0) {
		mode_t perm = st.st_mode;
		modeval[0] = (S_ISDIR(perm)) ? 'd' : '-';
		modeval[1] = (perm & S_IRUSR) ? 'r' : '-';
		modeval[2] = (perm & S_IWUSR) ? 'w' : '-';
		modeval[3] = (perm & S_IXUSR) ? 'x' : '-';
		modeval[4] = (perm & S_IRGRP) ? 'r' : '-';
		modeval[5] = (perm & S_IWGRP) ? 'w' : '-';
		modeval[6] = (perm & S_IXGRP) ? 'x' : '-';
		modeval[7] = (perm & S_IROTH) ? 'r' : '-';
		modeval[8] = (perm & S_IWOTH) ? 'w' : '-';
		modeval[9] = (perm & S_IXOTH) ? 'x' : '-';
		modeval[10] = '\0';
		return modeval;    
	}
	else{
		return NULL;
	}   
}


int main (int argc, char** argv) {
	int len, i;
	struct dirent *p;
	DIR *q;
	struct stat info;
	if (argc < 2) {
		fprintf (stderr, "usage: %s dirname or filename\n", argv[0]);
		return EXIT_FAILURE;
	}
	for(i=1; i<argc; i++){
		q = opendir (argv[i]);
		if (q == NULL) {
			fprintf (stderr, "%s: Cannot open directory ’%s’, maybe it's an file\n",
				argv[0], argv[i]);
			if (lstat(argv[i], &info) == -1) {
				fprintf(stderr, "fsize: Can’t stat %s, isn't a file too :(\n",
					argv[i]);
				return EXIT_FAILURE;
			}
			else {
				
				//printf("%d  ", info.st_mode);
				printf (" %s", argv[i]);
				printf("%s" ,permessions(argv[i]));
				printf(" %u", info.st_uid); /* Print uid. */
				printf(" %u", info.st_gid);
 				printf(" %ld", info.st_size); /* Print size. */
				printf(" %s" ,ctime(&info.st_mtime));

				continue;
			}
		}

		printf ("directory:/%s\n", argv[i]);
		p = readdir(q);
		while (p != NULL) {
			char* string;
			strcpy(string, argv[i]);
			strcat(string,"/");
			strcat(string, p->d_name);
			//printf ("\t%s\n", p->d_name);
			printf("%s  " ,string);
			if (lstat(string, &info) == -1) {
				fprintf(stderr, "fsize: Can’t stat %s\n",
					string);
				return EXIT_FAILURE;
			}	
			else {
				//printf("%d  ", info.st_mode);
				printf("%s" ,permessions(argv[i]));
				printf("  %u", info.st_uid); /* Print uid. */
				printf("  %u", info.st_gid);
 				printf("  %ld", info.st_size); /* Print size. */
 				printf("  %s" ,ctime(&info.st_mtime));
				//printf ("  %s\n", argv[i]);
			}
			
			p = readdir(q);
		}
		closedir (q);
	}
	return EXIT_SUCCESS;
}
