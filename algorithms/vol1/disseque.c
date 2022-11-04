#include <stdio.h>

#define MAX 100

typedef enum {true, false} BOOL;

int main() {
	BOOL visitados[MAX+1];
	int esquerda[MAX+1];
	int n, i, prox, n_elementos, sem_grupo = 0;
	int max_grupo;

	scanf("%d", &n);

	for (i = 1; i <= n; i++){
		visitados[i] = false;
		scanf("%d", &esquerda[i]);
	}

	for (i=1; i <= n; i++){
		n_elementos = 1;
		visitados[i] = true;
		max_grupo = i;
		prox = esquerda[i];
		while (visitados[prox] != true && prox != i) {
			n_elementos++;
			visitados[prox] = true;
			if (max_grupo < prox)
				max_grupo = prox;
			prox = esquerda[prox];
		}

		if (esquerda[i] == i){
			//printf("1-entrei\n");
			sem_grupo++;
		} else if (n_elementos == 2){
			//printf("2-entrei\n");
			sem_grupo += 2;
		} else if (n_elementos >=3){
			printf("%d %d", n_elementos, max_grupo);
			prox = esquerda[max_grupo];
			while( prox != max_grupo ) {
				printf(" %d", prox);
				prox = esquerda[prox];
			}
			printf("\n");
		}
	}
	printf("%d\n",sem_grupo);
	return 0;
}