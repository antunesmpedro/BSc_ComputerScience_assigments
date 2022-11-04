#include <stdio.h>
#define MAX 100

int main(){
	int cadeiras[MAX];
	int i, flag = 0, ntipos, pessoas_a_pe = 0, cadeiras_livres=0;
	int tipo, valor, nhabitantes, npreferencias, prefere;

	scanf("%d",&ntipos);

	for(i=0; i<ntipos; i++)
		cadeiras[i] = 0;
	for(i=0; i<ntipos; i++){
		scanf("%d%d", &tipo, &valor);
		cadeiras[tipo-1] = valor;
	}

	scanf("%d", &nhabitantes);
	for(i=0 ; i<nhabitantes; i++){
		scanf("%d", &npreferencias);
		flag = 0;
		while(npreferencias > 0){
			scanf("%d", &prefere);
			if(flag == 0 && cadeiras[prefere-1] > 0){
				cadeiras[prefere-1]--;
				flag = 1;
			}
			npreferencias--;
		}

		if( flag == 0)
			pessoas_a_pe++;
	}

	for(i = 0; i<ntipos; i++){
		cadeiras_livres += cadeiras[i];
	}

	printf("%d\n",pessoas_a_pe);
	printf("%d\n",cadeiras_livres);
	return 0;
}