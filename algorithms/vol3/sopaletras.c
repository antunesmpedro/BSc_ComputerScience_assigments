#include <stdio.h>
#include <string.h>

int main() {
	char word_1[21];
	char word_2[21];
	int size_1;
	int difere = 0, i, pos;

	scanf("%s %s", word_1, word_2);
	size_1 = strlen(word_1);

	for (i=0; i<size_1; i++) {
		if (word_1[i] != word_2[i]){
			pos = i;
			difere = 1;
			break;
		}
	}

	if (difere == 0)
		printf("Nenhum\n");
	else
		printf("%c%c\n",word_1[pos], word_2[pos]);
	return 0;
}