#include <stdio.h>

#define MAX 30

int main() {
	int caminho[MAX];
	int i=0, j, inicio_ciclo, flag=0;	

	for (j = 0; j < MAX; j++) {
		caminho[j] = 0;
	}
	scanf("%d", &caminho[0]);

	while (caminho[i] != 0){
		//printf("entrei ");
		flag=0;
		scanf("%d", &caminho[++i]);
		//printf("a-%d\n", caminho[i]);
		for (j = 0; j <= i; j++){
			if (caminho[j] == caminho[i]) {
				inicio_ciclo = j; 
				flag = 1;
				break;
			}
		}
		//printf("b-%d\n", caminho[i]);
		if (flag == 1){
			for (j = inicio_ciclo +1; j <= i; j++) 
				caminho[j] = 0;
			i=inicio_ciclo;
		}
		//printf("c-%d\n", caminho[i]);
	}

	i=0;
	while (caminho[i] != 0)
		printf("%d\n", caminho[i++]);

	return 0;
}