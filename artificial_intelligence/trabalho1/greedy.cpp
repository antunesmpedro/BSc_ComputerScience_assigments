#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <list>
#include <queue>
#include <cstring>
#include <string>

#define LCHILD(x) 2 * x + 1
#define RCHILD(x) 2 * x + 2
#define PARENT(x) (x - 1) / 2

using namespace std;

typedef struct Node{
  int heuristic;
  int matrix[4][4];
  char move;
  int depth;
  Node *father;
}Node;

//Implementação da minHeap
typedef struct minHeap {
  int size;
  Node **elem;
} minHeap;

minHeap initMinHeap(int size) {
  minHeap hp;
  hp.size = 0;
  return hp;
}

void swap(Node *n1, Node *n2) {
  Node temp = *n1 ;
  *n1 = *n2 ;
  *n2 = temp ;
}

void heapify(minHeap *hp, int i) {
  int smallest = (LCHILD(i) < hp->size && hp->elem[LCHILD(i)]->heuristic < hp->elem[i]->heuristic) ? LCHILD(i) : i ;
  if(RCHILD(i) < hp->size && hp->elem[RCHILD(i)]->heuristic < hp->elem[smallest]->heuristic) {
    smallest = RCHILD(i) ;
  }
  if(smallest != i) {
    swap((hp->elem[i]), (hp->elem[smallest])) ;
    heapify(hp, smallest) ;
  }
}

void insertNode(minHeap *hp, Node *node) {
  if(hp->size) {
    hp->elem = (struct Node **) realloc(hp->elem, (hp->size + 1) * sizeof(Node));
  } else {
    hp->elem = (struct Node **) malloc(sizeof(Node));
  }
  int i = (hp->size)++;
  while(i && node->heuristic < hp->elem[PARENT(i)]->heuristic) {
    hp->elem[i] = hp->elem[PARENT(i)];
    i = PARENT(i);
  }
  hp->elem[i] = node;
}

Node *remove_first(minHeap *hp) {
  Node *nd=hp->elem[0];
  if(hp->size) {
    hp->elem[0] = hp->elem[--(hp->size)] ;
    hp->elem = (struct Node **) realloc(hp->elem, hp->size * sizeof(Node)) ;
    heapify(hp, 0) ;
  } else {
    free(hp->elem) ;
  }
  return nd;
}


//vars globais
int inicial[4][4], final[4][4];
int count  = 1;
minHeap hp = initMinHeap(0);
list <Node*> filaNosVisitados;


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

bool isEqual(Node *node1, Node node2){
  for(int i = 0; i < 4; i++){
    for(int j = 0; j < 4; j++){
      if(node1->matrix[i][j] != node2.matrix[i][j])
        return false;
    }
  }
  return true;
}

bool inFilaNos(Node *node){
  for(int i = 0; i < hp.size; i++){
    if(isEqual(node, *(hp.elem[i])) && (hp.elem[i]->heuristic < node->heuristic))
      return true; 
  }
  return false;
}

bool inFilaNosVisitados(Node *node){
  for(std::list<Node*>::iterator it=filaNosVisitados.begin(); it != filaNosVisitados.end(); ++it){
    if(isEqual(node, **it) && ((*it)->heuristic < node->heuristic))
      return true;
  }
  return false;
}

int get_manhattan(int y1, int x1, int value){ 
  for(int i = 0; i < 4; i++)
    for(int j = 0; j < 4; j++)
      if(final[i][j] == value)
        return abs(i-y1)+abs(j-x1);
  return 0;
}

int heuristic(Node *node){
  int manhattan = 0;
  for(int i = 0; i < 4; i++)
    for(int j = 0; j < 4; j++)
      manhattan += get_manhattan(i,j,node->matrix[i][j]);
  return manhattan;
}


void makeDescedants(Node *now) {
  int i, j, x, y;
  for(i=0; i<4; i++) {
    for(j=0; j<4; j++) {
      // Procurar index de espaço branco
      if(now->matrix[i][j] == 0) {
        x = j;
        y = i;
        i=4;
        break;
      }
    }
  }

  if(x > 0 && now->move != 'R'){
    Node *node = (Node*)malloc(sizeof(Node));
    memcpy(node->matrix, now->matrix, 16*sizeof(int));
    node->matrix[y][x] = node->matrix[y][x-1];
    node->matrix[y][x-1] = 0;
    node->depth = now->depth + 1;
    node->heuristic = heuristic(node);
    node->move = 'L';
    node->father = now;
    if(!inFilaNosVisitados(node) && !inFilaNos(node)){
      insertNode(&hp,node);
      count++;
    }
    else free(node);
  }

  if(x < 3 && now->move != 'L'){
    Node *node = (Node*)malloc(sizeof(Node));
    memcpy(node->matrix, now->matrix, 16*sizeof(int));
    node->matrix[y][x] = node->matrix[y][x+1];
    node->matrix[y][x+1] = 0;
    node->depth = now->depth + 1;
    node->heuristic = heuristic(node);
    node->move = 'R';
    node->father = now;
    if(!inFilaNosVisitados(node) && !inFilaNos(node)){
      insertNode(&hp,node);
      count++;
    }
    else free(node);
  }

  if(y > 0 && now->move != 'D'){
    Node *node = (Node*)malloc(sizeof(Node));
    memcpy(node->matrix, now->matrix, 16*sizeof(int));
    node->matrix[y][x] = node->matrix[y-1][x];
    node->matrix[y-1][x] = 0;
    node->depth = now->depth + 1;
    node->heuristic = heuristic(node);
    node->move = 'U';
    node->father = now;
    if(!inFilaNosVisitados(node) && !inFilaNos(node)){
      insertNode(&hp,node);
      count++;
    }
    else free(node);
  }

  if(y < 3 && now->move != 'U'){
    Node *node = (Node*)malloc(sizeof(Node));
    memcpy(node->matrix, now->matrix, 16*sizeof(int));
    node->matrix[y][x] = node->matrix[y+1][x];
    node->matrix[y+1][x] = 0;
    node->depth = now->depth + 1;
    node->heuristic = heuristic(node);
    node->move = 'D';
    node->father = now;
    if(!inFilaNosVisitados(node) && !inFilaNos(node)){
      insertNode(&hp,node);
      count++;
    }
    else free(node);
  }
}

bool isSolution(Node *node) {
  if(node->heuristic == 0)
    return true;
  else return false;
}

Node *solve_puzzle() {
  //Criacao 1º Node
  Node *node = (Node*)malloc(sizeof(Node));
  memcpy(node->matrix, inicial, 16*sizeof(int));
  node->depth = 0;
  node->heuristic = heuristic(node);
  node->father = NULL;
  insertNode(&hp,node);

  while(hp.size != 0) {
    node = remove_first(&hp);
    if (isSolution(node))
      return node;
    else 
      makeDescedants(node);
    filaNosVisitados.push_front(node);
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
  else printf("A processar ...\n");
  

  clock_t t;
  t = clock();
  Node *node = solve_puzzle();
  string caminho;

   cout << "\nProfundidade:" << node->depth << endl;
  if(node->depth == 0){
      cout << "Configuracao inicial == Configuracao final" << endl;
      return 0;
    }
  
  printf("Solucao:");
  caminho.insert(0,1,node->move);
  node = node->father;
  while(node->father!=NULL){
    caminho.insert(0, "");
    caminho.insert(0,1,node->move);
    node = node->father;
  }
  
  cout << caminho << endl;
  t = clock() - t;
  printf("Memoria usada:%lu bytes\n" ,count*sizeof(Node));
  printf ("Tempo:%f segundos\n",((float)t)/CLOCKS_PER_SEC);
  return 0;
}
