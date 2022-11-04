#include <stdio.h>

#define MAX 100

int main() {
	int durTrabalhos;
	int tipos, lucro, tempo, qtdMax, qtdMin;
	int lucroTipos[MAX+1];
	int tempoTipos[MAX+1];
	int qtd_max_tipos[MAX+1];
	int qtd_min_tipos[MAX+1];
	float ratioTipos[MAX+1];
	float kilosTipos[MAX+1];

	scanf("%d %d", &durTrabalhos, &tipos);
	durTrabalhos = durTrabalhos * 60;
	for(int i = 1; i<=tipos; i++){
		scanf("%d %d %d %d", &lucro, &tempo, &qtdMax, &qtdMin);
		lucroTipos[i] = lucro;
		tempoTipos[i] = tempo;
		qtd_max_tipos[i] = qtdMax;
		qtd_min_tipos[i] = qtdMin;
		ratioTipos[i] = lucroTipos[i] / tempoTipos[i]; 
	}

	int j = tipos;
	int maxTipo = 1;
	while(j){
		for(int i=2; i<=tipos; i++){
			if (ratioTipos[maxTipo] < ratioTipos[i])
				maxTipo = i;
		}

		if (durTrabalhos < tempoTipos[maxTipo]) {
			if(qtd_max_tipos[maxTipo] < tempoTipos[maxTipo]){
				kilosTipos[maxTipo] = qtd_max_tipos[maxTipo] * lucroTipos[maxTipo];
				durTrabalhos -= qtd_max_tipos[maxTipo];
			}
			else{
				kilosTipos[maxTipo] = durTrabalhos * lucroTipos[maxTipo];	
				durTrabalhos = 0;
			}
		}
		else {
			if(qtd_max_tipos[maxTipo] < tempoTipos[maxTipo]){
				kilosTipos[maxTipo] = qtd_max_tipos[maxTipo] * lucroTipos[maxTipo];
				durTrabalhos -= qtd_max_tipos[maxTipo];
			}
			else {
				kilosTipos[maxTipo] = tempoTipos[maxTipo] * lucroTipos[maxTipo];
				durTrabalhos -= tempoTipos[maxTipo];
			}
		}

		j--;
	}

	for(int i=1; i<= tipos; i++) 
		printf("Produto %d: %.2f Kg\n", i, kilosTipos[i]);
	
	return 0;
}