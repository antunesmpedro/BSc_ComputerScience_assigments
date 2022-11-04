#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <list>
#include <queue>
#include <cstring>
#include <time.h>
#include <string>

using namespace std;

 

typedef struct Node{
  int matriz[4][4];
  int profundidade;
  char jogada;
  Node *pai;
}Node;

//vars globais
int inicial[4][4], final[4][4];
list<Node*> filaNos;
list<Node*> filaNosVisitados;
int contadorNos=1;

void make_descendants(Node *node);

bool isSolution(Node *jogo){
  for(int i = 0; i < 4; i++){
    for(int j = 0; j < 4; j++){
      if(jogo->matriz[i][j] != final[i][j])
        return false;
    }
  }
  return true;
}

Node * busca_nivel(int profundidade_nivel){
  //filaNos.clear();
  //filaNosVisitados.clear();
  Node *node = (Node*)malloc(sizeof(Node));
  memcpy(node->matriz, inicial, 16*sizeof(int));
  node->profundidade=0;
  node-> pai=NULL;
  filaNos.push_front(node);
  while(filaNos.size()){
    node= filaNos.front();
    filaNos.pop_front();
    if(node->profundidade <= profundidade_nivel){
      if(isSolution(node))
        return node;
      else 
        make_descendants(node);
    }

  }
  return NULL;
}

Node *resolucao(){
  Node *node;
  for(int i=0;i<81;i++){
    if((node = busca_nivel(i)) != NULL)
      return node;
    else continue;
  }
}

// determinar solvabilidade das configuracoes dadas
bool isSolvable(int inicial [4][4], int final[4][4]) {
  int array_in[16], array_fin[16];
  int k=0, n=0;
  int i,j, y_inicial, y_final;

  // determinar o valor y(linhas) da posição 0
  for(i=0; i<4; i++) {
    for(j=0; j<4; j++) {
      if(inicial[i][j] != 0)
        array_in[k++] = inicial[i][j];
      else 
        y_inicial = i+1;

      if(final[i][j] != 0)
        array_fin[n++]=final[i][j];
      else 
        y_final = i+1;
    }
  }

  //determinar inversoes do array
  int inv_inicial=0, inv_final=0;
  for(i=0; i<15; i++) {
    for(j=i+1; j<15; j++) {
      if(array_in[i] > array_in[j])
        inv_inicial++;
      if(array_fin[i] > array_fin[j])
        inv_final++;
    }
  }

  bool solvable_final, solvable_inicial;

  solvable_final = ((y_final == 4 || y_final == 2) == (inv_final % 2 == 0));
  solvable_inicial = ((y_inicial == 4 || y_inicial == 2) == (inv_inicial % 2 == 0));
  if(solvable_inicial == solvable_final)
    return true;
  else
    return false;
}

void make_descendants(Node *node){
  //encontrar coordenadas casa 0
  int i, j, x, y;
  for(i = 0; i < 4; i++)
    for(j = 0; j < 4; j++)
      if(node->matriz[i][j] == 0){ 
         x = j;
         y = i;
         i=4; 
         break;
      }

  if(x > 0 && node->jogada != 'R'){
    Node *newNode = (Node*)malloc(sizeof(Node));
    memcpy(newNode->matriz, node->matriz, 16*sizeof(int));
    newNode->matriz[y][x] = node->matriz[y][x-1];
    newNode->matriz[y][x-1] = 0;
    newNode->profundidade = node->profundidade + 1;
    newNode->jogada = 'L';
    newNode->pai = node;
    filaNos.push_front(newNode);
    contadorNos++;
  }

  if(x < 3 && node->jogada != 'L'){
    Node *newNode = (Node*)malloc(sizeof(Node));
    memcpy(newNode->matriz, node->matriz, 16*sizeof(int));
    newNode->matriz[y][x] = node->matriz[y][x+1];
    newNode->matriz[y][x+1] = 0;
    newNode->profundidade = node->profundidade + 1;
    newNode->jogada = 'R';
    newNode->pai = node;
    filaNos.push_front(newNode);
    contadorNos++;
  }

  if(y > 0 && node->jogada != 'D'){
    Node *newNode = (Node*)malloc(sizeof(Node));
    memcpy(newNode->matriz, node->matriz, 16*sizeof(int));
    newNode->matriz[y][x] = node->matriz[y-1][x];
    newNode->matriz[y-1][x] = 0;
    newNode->profundidade = node->profundidade + 1;
    newNode->jogada = 'U';
    newNode->pai = node;
    filaNos.push_front(newNode);
    contadorNos++;
  }

  if(y < 3 && node->jogada != 'U'){
    Node *newNode = (Node*)malloc(sizeof(Node));
    memcpy(newNode->matriz, node->matriz, 16*sizeof(int));
    newNode->matriz[y][x] = node->matriz[y+1][x];
    newNode->matriz[y+1][x] = 0;
    newNode->profundidade = node->profundidade + 1;
    newNode->jogada = 'D';
    newNode->pai = node;
    filaNos.push_front(newNode);
    contadorNos++;
  }
}

int main(){
  cout << "Configuracao inicial:" << endl;
  for(int i = 0; i < 4; i++){
    for(int j = 0; j < 4; j++){
      scanf("%d", &inicial[i][j]);
    }
    getchar();
  }

  cout << "Configuracao final:" << endl;
  for(int i = 0; i < 4; i++){
    for(int j = 0; j < 4; j++){
      scanf("%d", &final[i][j]);
    }
    getchar();
  }
  if(!isSolvable(inicial, final)){
    cout << "Impossivel chegar a solucao" << endl;
    return 0;
  }
  else 
    cout << "A processar ..." << endl;
  clock_t t;
  t = clock();
  Node *node =resolucao();
  string caminho;

  cout << "\nProfundidade:" << node->profundidade << endl;
  if(node->profundidade == 0){
      cout << "Configuracao inicial == Configuracao final" << endl;
      return 0;
    }

  printf("Solucao:");
  caminho.insert(0,1,node->jogada);
  node = node->pai;
  while(node->pai!=NULL){
    caminho.insert(0, "");
    caminho.insert(0,1,node->jogada);
    node = node->pai;
  }

  cout << caminho << endl;
  t = clock() - t;
  printf("Memoria usada:%lu bytes\n" ,contadorNos*sizeof(Node));
  printf ("Tempo:%f segundos\n",((float)t)/CLOCKS_PER_SEC);
  return 0;
}
