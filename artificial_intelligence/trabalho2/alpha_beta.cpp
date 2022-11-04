#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <climits>
#include <algorithm>

using namespace std;

typedef struct Node{
	char matriz[6][7];
	int prof;
	int util;
	int jogada;
}Node;

char mat_inicial[6][7];

int next_play = -1, utility_test;

int valor_max(Node *estado, int alpha, int beta);
int valor_min(Node *estado, int alpha, int beta);
int terminal_test(Node *estado);
Node *modificar_estado(Node *estado, int move, char jogador);
int procurar_matriz(Node *estado, int r, int l, int teste);
int terminal_test(Node *estado);
bool mostrar_tabuleiro(Node *estado, int move);
int check_win(Node *estado);
bool game_completed(Node *estado);

void criar_jogo(){
	int i , j;
	for(i=0;i<6;i++){
		for(j=0;j<7;j++){
			mat_inicial[i][j]= '-';
		}
	}
}

Node *makeNode(char matriz[][7], int prof, int util, int jogada){
	Node *node = (Node*) malloc(sizeof(Node));
	memcpy(node->matriz, matriz, 42*sizeof(char));
	node->prof=prof;
	node->util = util;
	node->jogada = jogada;
	return node;
}

Node *modificar_estado(Node *estado, int move, char jogador){
	int i;
	for(i=5;i>=0;i--){//começar em baixo
		if(estado->matriz[i][move]=='-'){
			estado->matriz[i][move] = jogador;
			break;
		}
	}
	return estado;
} 

void mostrar_tabuleiro(Node *estado){
	int i, j;
	printf("\n");
	for(i=0;i<6;i++){
		for(j=0;j<7;j++){
			cout << estado->matriz[i][j];
		}
		cout <<endl;
	}
	printf("1234567\n");
	printf("----------\n");
}
void AI_algoritmo(Node *estado){
	int v;
	v=valor_max(estado, INT_MIN, INT_MAX);
}

int horizontal(Node *estado,int x,int y){
  int x_num=0,o_num=0,casa_num=0;
  for(int i=y;i<y+4;i++){
    if(i<7){
      if(estado->matriz[x][i] == 'X')
        x_num++;
      else if(estado->matriz[x][i] == 'O')
        o_num++;
      casa_num++;
    }
  }
  if(casa_num == 4){
    if(x_num == 0 && o_num!=0){
      if(o_num == 1)
        return -1;
      else if(o_num == 2)
        return -10;
      else if(o_num == 3)
        return -50;
    }
    else if(o_num == 0 && x_num!=0){
    if(x_num == 1)
      return 1;
    else if(x_num == 2)
      return 10;
    else if(x_num == 3)
      return 50;
    }
  }
  else
    return 0;
return 0;
}
int vertical(Node *estado,int x,int y){
  int x_num=0,o_num=0,casa_num=0;
  for(int i=x;i<x+4;i++){
    if(i<6){
      if(estado->matriz[i][y] == 'X')
        x_num++;
      else if(estado->matriz[i][y] == 'O')
        o_num++;
      casa_num++;
    }
  }
  if(casa_num == 4){
    if(x_num == 0 && o_num!=0){
      if(o_num == 1)
        return -1;
      else if(o_num == 2)
        return -10;
      else if(o_num == 3)
        return -50;
    }
    else if(o_num == 0 && x_num!=0){
      if(x_num == 1)
        return 1;
      else if(x_num == 2)
        return 10;
      else if(x_num == 3)
        return 50;
    }
  }
  else
    return 0;
return 0;
}

int diagonal(Node *estado,int x,int y){
  int x_num=0,o_num=0,casa_num=0;
  for(int i=y;i<y+4;i++){
    if(i<7 && x<6){
      if(estado->matriz[x][i] == 'X')
        x_num++;
      else if(estado->matriz[x][i] == 'O')
        o_num++;
      casa_num++;
    }
    x++;
  }
  if(casa_num == 4){
    if(x_num == 0 && o_num!=0){
      if(o_num == 1)
        return -1;
      else if(o_num == 2)
        return -10;
      else if(o_num == 3)
        return -50;
    }
    else if(o_num == 0 && x_num!=0){
      if(x_num == 1)
        return 1;
      else if(x_num == 2)
        return 10;
      else if(x_num == 3)
        return 50;
    }
  }
  else
    return 0;
return 0;
}

int diagonal2(Node *estado,int x,int y){
  int x_num=0,o_num=0,casa_num=0;
  for(int i=y;i>y-4;i--){
    if(i>=0 && x<6){
      if(estado->matriz[x][i] == 'X')
        x_num++;
      else if(estado->matriz[x][i] == 'O')
        o_num++;
      casa_num++;
    }
    x++;
  }
  if(casa_num == 4){
    if(x_num == 0 && o_num!=0){
      if(o_num == 1)
        return -1;
      else if(o_num == 2)
        return -10;
      else if(o_num == 3)
        return -50;
    }
    else if(o_num == 0 && x_num!=0){
      if(x_num == 1)
        return 1;
      else if(x_num == 2)
        return 10;
      else if(x_num == 3)
        return 50;
    }
  }
  else
    return 0;
return 0;
}
int valor_util(Node *estado){
	int val_util=0, i, j;
	for(i=0;i<6;i++){
		for(j=0;j<7;j++){
			int hor = horizontal(estado,i,j);
      		int ver = vertical(estado,i,j);
		    int dia = diagonal(estado,i,j);
      		int dia2 = diagonal2(estado,i,j);
      		val_util += hor + ver + dia + dia2;
		}
	}
	return val_util;
}

int valor_min(Node *estado, int alpha, int beta){
	int val = terminal_test(estado);
	int v = INT_MAX;
	if(val != -1){
		if(val ==1){
			int util1 = valor_util(estado);
			return util1;
		}
		else 
			return val;
	}
	else{

		for(int j = 6; j >= 0; j--){
			for(int i = 5; i >= 0; i--){
				Node *descendentes = makeNode(estado->matriz, estado->prof + 1, 0, j);
				if(estado->matriz[i][j] == '-'){
					descendentes->matriz[i][j] = 'O';
					v = min(v, valor_max(descendentes, alpha, beta));
					if(v<=alpha) 
						return v;
					beta = min(beta, v);
					break;
				}
			}
		}
	}
	return v;
}

int valor_max(Node *estado, int alpha, int beta){
	int val = terminal_test(estado);
	int v = INT_MIN;
	if(val != -1){
		if(val ==1){
			int util1 = valor_util(estado);
			return util1;
		}
		else 
			return val;
	}
	else{
		for(int j = 6; j >= 0; j--){
			for(int i = 5; i >= 0; i--){
				Node *descendentes = makeNode(estado->matriz, estado->prof + 1, 0, j);
				if(estado->matriz[i][j] == '-'){
					descendentes->matriz[i][j] = 'X';
					int new_v;
					new_v = max(v, valor_min(descendentes, alpha, beta));
					if(v != new_v){
						descendentes->util = new_v;
						v=new_v;
						utility_test=new_v;
						if(descendentes->prof == 1){
							next_play = descendentes->jogada;
						}
					}
					if(v>= beta)
						return v;
					alpha = max(alpha, v);
					break;
				}
			}
  		}
	} 
	return v;
}

int terminal_test(Node *estado){
  int v;
  if((v=check_win(estado)) != 0){
    return v;               //vai retornar -512 ou 512
  }
  else if(game_completed(estado)){
    return 0;                       //retorna empate(0)
  }
  else if(estado->prof >= 7){
    return 1;                       //retorna código para chamar a utility
  }
  else{
    return -1;                      //retorna que o estado atual nao é terminal
  }
}

bool game_completed(Node *estado){
  int j;
  for(j=0;j<7;j++){
    if(estado->matriz[0][j] == '-')
      return false;
  }
  return true;
}

int check_win(Node *estado){
  int v;
  for(int i=0;i<6;i++){
    for(int j=0;j<7;j++){
      if((v=procurar_matriz(estado,i,j,1)) != 0)     return v;
      else if((v=procurar_matriz(estado,i,j, 2)) != 0)  return v;
      else if((v=procurar_matriz(estado,i,j, 3)) != 0)  return v;
      else if((v=procurar_matriz(estado,i,j, 4)) != 0) return v;
    }
  }
  return 0;
}

int procurar_matriz(Node *estado, int r, int l, int teste){
	int x_num=0, o_num=0;
	if(teste==1){
		for(int i=l;i<l+4;i++){
	    	if(i<7){
				if(estado->matriz[r][i] == 'X')
					x_num++;
				else if(estado->matriz[r][i] == 'O')
					o_num++;
		    }
		}
		if(x_num == 4)
			return 512;
		else if(o_num == 4)
			return -512;
		else
			return 0;
	}
	else if(teste == 2){
		for(int i=r;i<r+4;i++){
			if(i<6){
				if(estado->matriz[i][l] == 'X')
					x_num++;
				else if(estado->matriz[i][l] == 'O')
					o_num++;
			}
		}
		if(x_num == 4)
			return 512;
		else if(o_num == 4)
			return -512;
		else
			return 0;
	}
	else if(teste == 3){
		for(int i=l;i<l+4;i++){
			if(i<7 && r<6){
				if(estado->matriz[r][i] == 'X')
					x_num++;
				else if(estado->matriz[r][i] == 'O')
					o_num++;
			}
			r++;
  		}
		if(x_num == 4)
			return 512;
		else if(o_num == 4)
			return -512;
		else
			return 0;
	}
	else if(teste == 4){
		for(int i=l;i>l-4;i--){
			if(i>=0 && r<6){
				if(estado->matriz[r][i] == 'X')
					x_num++;
				else if(estado->matriz[r][i] == 'O')
					o_num++;
			}
			r++;
		}
		if(x_num == 4)
			return 512;
		else if(o_num == 4)
			return -512;
		else
			return 0;
	}
	return 0;
}

bool tabuleiro_cheio(Node *estado, int move){
	if(estado->matriz[0][move] != '-')
		return true;
	return false;
}
int main(){
	int move, v;
	char palavra;
	criar_jogo();
	Node *estado= makeNode(mat_inicial, 0, 0, -1);
	//printf("%d\n", estado);
	printf("Escolha o primeiro a jogar: 'A' para AI, 'H' para voce ser o primeiro\n");
	scanf("%c", &palavra);
	if(palavra == 'H'){
		printf("Selecione a linha que quer jogar (1-7)\n");
		scanf("%d", &move);
		if(move<=0 && move >7){
			printf("Jogada inválida\n");
			while(true){
				scanf("%d", &move);
				if(move<=0 && move>7)
					printf("Jogada inválida");
				else break;
			}
		}
		estado = modificar_estado(estado, move-1, 'O');
		printf("Tabuleiro atualizado\n");
		mostrar_tabuleiro(estado);
	}
	while(true){
		printf("É a vez da AI jogar\n");
		printf("AI a pensar ..\n");
		AI_algoritmo(estado);
		estado = modificar_estado(estado,next_play, 'X');
		printf("Tabuleiro atualizado\n");
		mostrar_tabuleiro(estado);
		v = terminal_test(estado);
		if(v==512){
			printf("AI ganhou\n");
			break;
		} 	
		else if(v==0){
			printf("Empate\n");
			break;
		}
		printf("Selecione a linha que quer jogar (1-7)\n");
		scanf("%d", &move);
		if(move<=0 || move >7 || tabuleiro_cheio(estado, move-1)){
			printf("Jogada inválida\n");
			scanf("%d", &move);
		}	
		estado=modificar_estado(estado, move-1, 'O');
		printf("Tabuleiro atualizado\n");
		mostrar_tabuleiro(estado);
		v = terminal_test(estado);
		if(v==-512){
			printf("Parabéns, ganhouo jogo.\n");
			break;
		}
		else if(v==0){
			printf("Empate.\n");
			break;
		}
	}
	return 0;
}