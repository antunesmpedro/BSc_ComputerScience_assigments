#include <stdio.h>

/*
		if (conta_c / 100 > 0) {
			conta_e += conta_c / 100;
			conta_c %= 100; 
		}
		troco_e = conta_e - trans_e;
		troco_c = conta_c - trans_c;
		if (troco_c < 0) {
			troco_e--;
			troco_c = 100 + troco_c;
		}
*/

int main() {
	int caixa[6], n_transacoes = 0, n_retencoes = 0;
	int i, trans_e, trans_c, coin;
	int quantia_retida_e = 0, quantia_retida_c = 0;
	float conta, troco, pagamento, troco_dado, quantia_retida;

	for (i=0; i<6; i++)
		scanf("%d", &caixa[i]);

	scanf("%d%d", &trans_e, &trans_c);
	while (trans_e != 0 || trans_c != 0) {
		n_transacoes++;
		conta = trans_e;
		conta += (float) trans_c / 100;
		troco_dado = 0;
		pagamento = 0;

		scanf("%d", &coin);
		while (coin != 0) {
			switch (coin) {
				case 2: 
					pagamento += 2;
					caixa[0]++;
					break;
				case 1: 
					pagamento += 1;
					caixa[1]++;
					break;
				case 50: 
					pagamento += 0.50;
					caixa[2]++;
					break;
				case 20: 
					pagamento += 0.20;
					caixa[3]++;
					break;
				case 10: 
					pagamento += 0.10;
					caixa[4]++;
					break;
				case 5: 
					pagamento += 0.05;
					caixa[5]++;
					break;
			}
			scanf("%d", &coin);
		}

		troco = pagamento - conta;
		//printf("CAIXA: 2-%d 1-%d 50-%d 20-%d 10-%d 5-%d\n", caixa[0], caixa[1], caixa[2], caixa[3], caixa[4], caixa[5]);
		//printf("troco-%.2f pagamento-%.2f conta-%.2f troco_dado-%.2f\n", troco, pagamento, conta, troco_dado);

		while ( caixa[0] > 0 && troco-troco_dado >= 2){
			troco_dado += 2;
			caixa[0]--;
			//printf("moeda troco 2\n");
		}
		while ( caixa[1] > 0 && troco-troco_dado >= 1){
			troco_dado += 1;
			caixa[1]--;
			//printf("moeda troco 1\n");
		}
		while ( caixa[2] > 0 && troco-troco_dado >= 0.50 ){
			troco_dado += 0.50;
			caixa[2]--;
			//printf("moeda troco 50\n");
		}
		while ( caixa[3] > 0 && troco-troco_dado >= 0.20 ){
			troco_dado += 0.20;
			caixa[3]--;
			//printf("moeda troco 20\n");
		}
		while ( caixa[4] > 0 && troco-troco_dado >= 0.10 ){
			troco_dado += 0.10;
			caixa[4]--;
			//printf("moeda troco 10\n");
		}
		while ( caixa[5] > 0 && troco-troco_dado >= 0.05 ){
			troco_dado += 0.05;
			caixa[5]--;
			//printf("moeda troco 5\n");
		}

		//printf("troco-%f pagamento-%.2f conta-%.2f troco_dado-%f\n", troco, pagamento, conta, troco_dado);
		quantia_retida = troco - troco_dado;
		printf("%.2f\n", quantia_retida);
		if ( quantia_retida != 0) {
			n_retencoes++;
			quantia_retida_e += (int) quantia_retida;
			quantia_retida -= (int) quantia_retida;
			quantia_retida_c += quantia_retida * 100;
			printf("entrei\n");
		}
		
		//printf("CAIXA: 2-%d 1-%d 50-%d 20-%d 10-%d 5-%d\n\n", caixa[0], caixa[1], caixa[2], caixa[3], caixa[4], caixa[5]);
		scanf("%d%d", &trans_e, &trans_c);
	}

	printf("%d %d\n", quantia_retida_e, quantia_retida_c);
	printf("%d/%d\n", n_retencoes, n_transacoes);
	return 0;
}