#include <stdio.h>

#define MAX 50

typedef struct p {
	int id;
	int n_tarefas_possiveis;
	int n_tarefas_max;
	int tarefas[n_tarefas_possiveis];
}Pessoa;

int main() {
	int n_pessoas, n_tarefas, n_propostas;
	int id_tarefa, id_pessoa;
	Pessoa pessoas[MAX];

	scanf("%d %d", &n_pessoas, &n_tarefas);
	for (i=0; i<n_pessoas; i++) {
		scanf("%d %d %d",&pessoas[i].id, &pessoas[i].n_tarefas_possiveis, &pessoas[i].n_tarefas_max);
		for (j=0; j<pessoas[i].n_tarefas_possiveis; j++) 
			scanf("%d", &pessoas[i].tarefas[j]);
	}
	
	scanf("%d", &n_propostas);
	for (i=1; i<=n_propostas; i++) {
		scanf("%d %d", &id_tarefa, &id_pessoa);
		while ( !(id_pessoa == 0 && id_tarefa == 0) ) {
			
		}
	}

	return 0;
}