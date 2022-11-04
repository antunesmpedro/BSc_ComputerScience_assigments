#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <list>
#include <queue>
#include <cstring>
#include <string>
#include <time.h>

using namespace std;

typedef struct Node{
  int matriz[4][4];
  char jogada;
  int profundidade;
  Node *pai;
}Node;

//vars globais
list<Node*> filaNos;
list<Node*> filaNosVisitados;
int inicial[4][4], final[4][4];
int contadorNos = 1;

bool isEqual(Node *node1, Node node2){
  for(int i = 0; i < 4; i++){
    for(int j = 0; j < 4; j++){
      if(node1->matriz[i][j] != node2.matriz[i][j])
        return false;
    }
  }
  return true;
}

bool inFilaNos(Node *node){
  list<Node*>::iterator item;
  for(item=filaNos.begin(); item !=filaNos.end(); ++item){
    if(isEqual(node, **item))
      return true;
  }
  return false;
}

bool inFilaNosVisitados(Node *node){
  list<Node*>::iterator item;
  for(item=filaNosVisitados.begin(); item != filaNosVisitados.end(); ++item){
    if(isEqual(node, **item))//  && node
      return true;
  }
  return false;
}

void makeDescendants(Node *node){
  int i, j, x, y;
  //encontrar coordenadas casa 0
  for(i = 0; i < 4; i++)
    for(j = 0; j < 4; j++)
      if(node->matriz[i][j] == 0){
  	     x = j;
  	     y = i;
	     i=4;
  	     break;
      }

  if(x > 0 && node->jogada != 'R' && node->profundidade < 80){
    Node *newNode = (Node*)malloc(sizeof(Node));
    memcpy(newNode->matriz, node->matriz, 16*sizeof(int));
    newNode->matriz[y][x] = node->matriz[y][x-1];
    newNode->matriz[y][x-1] = 0;
    newNode->profundidade = node->profundidade + 1;
    newNode->jogada = 'L';
    newNode->pai = node;
    if(!inFilaNos(newNode) && !inFilaNosVisitados(newNode)){
      filaNos.push_back(newNode);
      contadorNos++;

      /*
      for(int i=0; i<4; i++){
      for(int j=0; j<4; j++){
	cout << node->matriz[i][j] << " ";
      }
      cout << endl;
    }
      cout << endl;
      */
    }
    else free(newNode);  //liberta espaco nos repetidos
  }

  if(x < 3 && node->jogada != 'L' && node->profundidade < 80){
    Node *newNode = (Node*)malloc(sizeof(Node));
    memcpy(newNode->matriz, node->matriz, 16*sizeof(int));
    newNode->matriz[y][x] = node->matriz[y][x+1];
    newNode->matriz[y][x+1] = 0;
    newNode->profundidade = node->profundidade + 1;
    newNode->jogada = 'R';
    newNode->pai = node;
    if(!inFilaNos(newNode) && !inFilaNosVisitados(newNode)){
      filaNos.push_back(newNode);
      contadorNos++;

      /*
      for(int i=0; i<4; i++){
      for(int j=0; j<4; j++){
	cout << node->matriz[i][j] << " ";
      }
      cout << endl;
    }
      cout << endl;
      */
    }
    else free(newNode);
  }

  if(y > 0 && node->jogada != 'D' && node->profundidade < 80){
    Node *newNode = (Node*)malloc(sizeof(Node));
    memcpy(newNode->matriz, node->matriz, 16*sizeof(int));
    newNode->matriz[y][x] = node->matriz[y-1][x];
    newNode->matriz[y-1][x] = 0;
    newNode->profundidade = node->profundidade + 1;
    newNode->jogada = 'U';
    newNode->pai = node;
    if(!inFilaNos(newNode) && !inFilaNosVisitados(newNode)){
      filaNos.push_back(newNode);
      contadorNos++;
      /*
      for(int i=0; i<4; i++){
      for(int j=0; j<4; j++){
	cout << node->matriz[i][j] << " ";
      }
      cout << endl;
    }
      cout << endl;
      */
    }
    else free(newNode);  
  }

  if(y < 3 && node->jogada != 'U' && node->profundidade < 80){
    Node *newNode = (Node*)malloc(sizeof(Node));
    memcpy(newNode->matriz, node->matriz, 16*sizeof(int));
    newNode->matriz[y][x] = node->matriz[y+1][x];
    newNode->matriz[y+1][x] = 0;
    newNode->profundidade = node->profundidade + 1;
    newNode->jogada = 'D';
    newNode->pai = node;
    if(!inFilaNos(newNode) && !inFilaNosVisitados(newNode)){
      filaNos.push_back(newNode);
      contadorNos++;

      /*
      for(int i=0; i<4; i++){
      for(int j=0; j<4; j++){
	cout << node->matriz[i][j] << " ";
      }
      cout << endl;
    }
      cout << endl;
      */
    }
    else free(newNode);
  }

  /*
  for(int i=0; i<4; i++){
      for(int j=0; j<4; j++){
	cout << node->matriz[i][j] << " ";
      }
      cout << endl;
    }

  cout << endl;
*/
}

// determinar solvabilidade das configuracoes dadas
bool isSolvable(int inicial[4][4], int final[4][4]){
  int array_in[16], array_fin[16];
  int k = 0, n = 0;
  int i, j, y_final, y_inicial;
 
  // determinar o valor y(linhas) da posição 0
  for(i = 0; i < 4; i++){
    for(j = 0; j < 4; j++){
      if(inicial[i][j] != 0)
        array_in[k++] = inicial[i][j];
      else
        y_inicial = i+1;
      if(final[i][j] != 0)
        array_fin[n++] = final[i][j];
      else
        y_final = i+1;
    }
  }

  //determinar inversoes dos array
  int inv_inicial = 0, inv_final = 0;
  for(i = 0; i < 15; i++){
    for(j = i+1; j < 15; j++){
      if(array_in[i] > array_in[j])
        inv_inicial++;
      if(array_fin[i] > array_fin[j])
        inv_final++;
    }
  }
  
  bool solvable_inicial, solvable_final;
  solvable_final = ((y_final == 4 || y_final == 2) == (inv_final % 2 == 0));
  solvable_inicial = ((y_inicial == 4 || y_inicial == 2) == (inv_inicial % 2 == 0));
  if(solvable_inicial == solvable_final)
    return true;
  else
    return false;
}

bool isSolution(Node *node){
  for(int i = 0; i < 4; i++){
    for(int j = 0; j < 4; j++){
      if(node->matriz[i][j] != final[i][j])
        return false;
    }
  }
  return true;
}

Node *buscaSolucao(){
  Node *newNode = (Node*)malloc(sizeof(Node));
  memcpy(newNode->matriz, inicial, 16*sizeof(int));
  newNode->profundidade = 0;
  newNode->pai = NULL;
  filaNos.push_front(newNode);
  while( filaNos.size() != 0 ){
    newNode = filaNos.front();
    filaNos.pop_front();
      //printf("Chose node with depth = %d\n", node->depth);
    //cout << newNode << endl;
    if(isSolution(newNode)){
     
      return newNode;
    }
    else{
        filaNosVisitados.push_front(newNode);
        makeDescendants(newNode);
    }
    //cout << endl << filaNos.size() << endl;
  }
  //return NULL;
}

int main(){
  cout << "Configuracao inicial:" << endl;
  for(int i = 0; i < 4; i++){
    for(int j = 0; j < 4; j++){
      cin >> inicial[i][j];
    }
    getchar();
  }
  cout << "Configuracao final:" << endl;
  for(int i = 0; i < 4; i++){
    for(int j = 0; j < 4; j++){
      cin >> final[i][j];
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
    Node *node = buscaSolucao();
    string caminho;
      
    cout << "\nProfundidade:" << node->profundidade << endl;
    if(node->profundidade == 0){
      cout << "Configuracao inicial == Configuracao final" << endl;
      return 0;
    }

    printf("Solução:");
    caminho.insert(0,1,node->jogada);
    node = node->pai;
    while(node->pai!=NULL){
      caminho.insert(0, "");
      caminho.insert(0,1,node->jogada);
      node = node->pai;
    }
    
    cout << caminho << endl;
    t = clock() - t;
    printf("Memoria usada:%lu bytes\n", contadorNos*sizeof(Node));
    printf ("Tempo:%f segundos\n",((float)t)/CLOCKS_PER_SEC);
    return 0;
}
