/*-------------------------------------------------------------------*\
|  TAD para implementacao de grafo dirigido com UM peso (int)         |
|                                                                     |
|    Versão simplificada;  |V| <=  MAXVERTS;                          |
|     Assume-se que os vértices são numerados de 1 a |V|.             |
|                                                                     |
|   A.P.Tomás, CC2001 (material para prova pratica), DCC-FCUP, 2017   |
|   Last modified: 2017.12.18                                         |
\--------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAXVERTS 2500
// numero maximo de vertices (alterar se necessario)


typedef struct arco {
  int no_final;
  int valor;
  struct arco *prox;
} ARCO;

typedef struct no {
  //int label;
  ARCO *adjs;
} NO;

typedef struct graph {
  NO verts[MAXVERTS+1];  // nós implicitamente numerados de 1 a nvs
  int nvs, narcos;
} GRAFO;

//--- protótipos das funções disponíveis----------------------------
//    ATENÇÃO AOS TIPOS DE ARGUMENTOS E DE RESULTADO


GRAFO *new_graph(int nverts);
/* cria um grafo com nverts vertices e sem arcos */
void destroy_graph(GRAFO *g);
/* liberta o espaço reservado na criação do grafo */
void insert_new_arc(int i, int j, int valor_ij, GRAFO *g);
/* insere arco (i,j) no grafo, bem como o seu peso; não evita repetições */
void remove_arc(ARCO *arco, int i, GRAFO *g);
/* retira adjacente arco da lista de adjacentes de i */
ARCO *find_arc(int i, int j, GRAFO *g);
/* retorna um apontador para o arco (i,j) ou NULL se não existir */

//--- macros de acesso aos campos da estrutura --------------------------

#define NUM_VERTICES(g) ( (g) -> nvs )
// numero de vertices
#define NUM_ARCOS(g) ( (g) -> narcos )
// numero de arcos
#define ADJS_NO(i,g) ( (g) -> verts[i].adjs )
// primeiro arco da lista de adjacentes do nó i
#define PROX_ADJ(arco) ((arco) -> prox)
// proximo adjacente 
#define ADJ_VALIDO(arco) (((arco) != NULL))
// se arco é válido
#define EXTREMO_FINAL(arco) ((arco) -> no_final)
// qual o extremo final de arco
#define VALOR_ARCO(arco) ((arco) -> valor)
// qual o valor do arco

//======  protótipos de funções auxiliares (privadas) ======
static ARCO* cria_arco(int, int valor_ij);
static void free_arcs(ARCO *);


//======  Implementação (definição das funções) ========================

// para criar um grafo com nverts vertices e sem ramos
GRAFO *new_graph(int nverts)
{
  if (nverts > MAXVERTS) {
    fprintf(stderr,"Erro: %d > MAXVERTS\n",nverts);
    exit(EXIT_FAILURE);
  }
  GRAFO *g = (GRAFO *) malloc(sizeof(GRAFO));
  if (g == NULL) { 
    fprintf(stderr,"Erro: falta memoria\n");
    exit(EXIT_FAILURE);
  }

  NUM_VERTICES(g) = nverts;  
  NUM_ARCOS(g) = 0;
  while (nverts) {
    ADJS_NO(nverts,g) = NULL;
    nverts--;
  }
  return g;
}


// para destruir um grafo criado
void destroy_graph(GRAFO *g)
{ int i;
  if (g != NULL) {
    for (i=1; i<= NUM_VERTICES(g); i++) 
      free_arcs(ADJS_NO(i,g));
    free(g);
  }
}

// para inserir um novo arco num grafo
void insert_new_arc(int i, int j, int valor_ij, GRAFO *g)
{ /* insere arco (i,j) no grafo g, bem como o seu label  */

  ARCO *arco = cria_arco(j,valor_ij);
  PROX_ADJ(arco) = ADJS_NO(i,g);
  ADJS_NO(i,g) = arco;  // novo adjacente fica à cabeça da lista
  NUM_ARCOS(g)++;
}

// para remover um arco de um grafo (se existir na lista de adjs[i])
void remove_arc(ARCO *arco, int i, GRAFO *g)
{ 
  if (arco != NULL) {
    ARCO *aux = ADJS_NO(i,g), *prev = NULL;
    while (aux != arco && ADJ_VALIDO(aux)) {
      prev = aux;
      aux = PROX_ADJ(aux);
    }
    if (aux == arco) {
      if (prev == NULL) {
	ADJS_NO(i,g)  = PROX_ADJ(arco);
      } else PROX_ADJ(prev) = PROX_ADJ(arco);
      free(arco);
      NUM_ARCOS(g)--;
    }
  }
}

// retorna um apontador para o arco (i,j) ou NULL se não existir 
ARCO *find_arc(int i, int j, GRAFO *g){
  ARCO *adj = ADJS_NO(i,g);

  while(adj != NULL && EXTREMO_FINAL(adj) != j)
    adj = PROX_ADJ(adj);

  return adj;
}
    

// ----  as duas funcoes abaixo sao auxiliares nao publicas ----

// reservar memoria para um novo arco e inicializa-lo
static ARCO *cria_arco(int j, int valor)
{ // cria um novo adjacente
  ARCO *arco = (ARCO *) malloc(sizeof(ARCO));
  if (arco == NULL) {
    fprintf(stderr,"ERROR: cannot create arc\n");
    exit(EXIT_FAILURE);
  }
  EXTREMO_FINAL(arco) = j;
  VALOR_ARCO(arco) = valor;
  PROX_ADJ(arco) = NULL;
  return arco;
}

// libertar uma lista de arcos 
static void free_arcs(ARCO *arco)
{ // liberta lista de adjacentes 
  if (arco == NULL) return;
  free_arcs(PROX_ADJ(arco));
  free(arco);
}

/*-----------------------------------------------------------------------*\
|  Exemplo de implementacao de fila de prioridade (por heap de mínimo)    |
|                                                                         |
|   A.P.Tomás, CC2001 (material para prova pratica), DCC-FCUP, 2017       |
|   Last modified: 2017.12.18                                             |
\*-----------------------------------------------------------------------*/

#include<stdio.h>
#include<stdlib.h>

typedef enum bool {TRUE, FALSE} BOOL;

typedef struct qnode {
  int vert, vertkey;
} QNODE;

typedef struct heapMin {
  int sizeMax, size;
  QNODE *a;
  int *pos_a;
} HEAPMIN;

//---------  protótipos das funções disponíveis --------------------

HEAPMIN *build_heap_min(int v[], int n);
void insert(int v, int key, HEAPMIN *q);
int extractMin(HEAPMIN *q);   // retorna v 
void decreaseKey(int v, int newkey, HEAPMIN *q);
int heap_isEmpty(HEAPMIN *q);   // retorna 1 ou 0

void write_heap(HEAPMIN *q);
void destroy_heap(HEAPMIN *q);


//----------------- definição das funções e macros ---------------------

#define POSINVALIDA 0

#define LEFT(i) (2*(i))
#define RIGHT(i) (2*(i)+1)
#define PARENT(i) ((i)/2)

static void heapify(int i,HEAPMIN *q);
static void swap(int i,int j,HEAPMIN *q);
static int compare(int i, int j, HEAPMIN *q);
static int pos_valida(int i,HEAPMIN *q);

static int compare(int i, int j, HEAPMIN *q){
  if (q -> a[i].vertkey < q -> a[j].vertkey)
    return -1;
  if (q -> a[i].vertkey == q -> a[j].vertkey){
    if (q -> a[i].vert < q -> a[j].vert)
      return -1;
    else if (q -> a[i].vert > q -> a[j].vert)
      return 1;
    else 
      return 0;
  }
  return 1;
}


static int pos_valida(int i, HEAPMIN *q) {
  return (i >= 1 && i <= q -> size);
}

int extractMin(HEAPMIN *q) {
  int vertv = q -> a[1].vert;
  swap(1,q->size,q);
  q -> pos_a[vertv] = POSINVALIDA;  // assinala vertv como removido
  q -> size--;
  heapify(1,q);
  return vertv;
}

void decreaseKey(int vertv, int newkey, HEAPMIN *q){
  int i = q -> pos_a[vertv];
  q -> a[i].vertkey = newkey;

  while(i > 1 && compare(i,PARENT(i),q) < 0){
    swap(i,PARENT(i),q);
    i = PARENT(i);
  }
}


static void heapify(int i,HEAPMIN *q) {
  // para heap de minimo
  int l, r, smallest;
  l = LEFT(i);
  if (l > q -> size) l = i;
  r = RIGHT(i);
  if (r > q -> size) r = i;
  
  smallest = i;
  if (compare(l,smallest,q) < 0) 
    smallest = l;
  if (compare(r,smallest,q) < 0) 
    smallest = r;
  
  if (i != smallest) {
    swap(i,smallest,q);
    heapify(smallest,q);
  }
}

static void swap(int i,int j,HEAPMIN *q){
  QNODE aux;
  q -> pos_a[q -> a[i].vert] = j;
  q -> pos_a[q -> a[j].vert] = i;
  aux = q -> a[i];
  q -> a[i] = q -> a[j];
  q -> a[j] = aux;
}



HEAPMIN *build_heap_min(int vec[], int n){
  // supor que vetor vec[.] guarda elementos nas posições 1 a n
  // cria heapMin correspondente em tempo O(n)
  HEAPMIN *q = (HEAPMIN *)malloc(sizeof(HEAPMIN));
  int i;
  q -> a = (QNODE *) malloc(sizeof(QNODE)*(n+1));
  q -> pos_a = (int *) malloc(sizeof(int)*(n+1));
  q -> sizeMax = n; // posicao 0 nao vai ser ocupada
  q -> size = n;   
  for (i=1; i<= n; i++) {
    q -> a[i].vert = i;
    q -> a[i].vertkey = vec[i];
    q -> pos_a[i] = i;  // posicao inicial do elemento i na heap
  }

  for (i=n/2; i>=1; i--) 
    heapify(i,q);
  return q;
}


void insert(int vertv, int key, HEAPMIN *q)
{ 
  if (q -> sizeMax == q -> size) {
    fprintf(stderr,"Heapmin is full\n");
    exit(EXIT_FAILURE);
  }
  q -> size++;
  q -> a[q->size].vert = vertv;
  q -> pos_a[vertv] = q -> size;   // supondo 1 <= vertv <= n
  decreaseKey(vertv,key,q);   // diminui a chave e corrige posicao se necessario
}


int heap_isEmpty(HEAPMIN *q){
  if (q -> size == 0) return 1;
  return 0;
}


// --------- auxiliar para ver conteudo  ---------------------
void write_heap(HEAPMIN *q){
  int i;

  printf("Max size: %d\n", q -> sizeMax);
  printf("Current size: %d\n", q -> size);
  
  printf("(Vert,Key)\n---------\n");
  for(i=1; i <= q -> size; i++)
    printf("(%d,%d)\n",q->a[i].vert,q->a[i].vertkey);

  printf("-------\n(Vert,PosVert)\n---------\n");

  for(i=1; i <= q -> sizeMax; i++)
    if (pos_valida(q -> pos_a[i],q))
      printf("(%d,%d)\n",i,q->pos_a[i]);
}


void destroy_heap(HEAPMIN *q){
  if (q != NULL) {
    free(q -> a);
    free(q -> pos_a);
    free(q);
  }
}


///////////////////////////////
//                           //
//     NEGOCIO ELETRONICO    //
//                           //
///////////////////////////////

int dist[MAXVERTS+1];
int pai[MAXVERTS+1];

GRAFO* ler_construir_grafo(int n) {
  GRAFO* g;
  int i, j, dij;

  g = new_graph(n);

  scanf("%d", &i);
  while (i != -1) {
    scanf("%d %d", &j, &dij);
    if (find_arc(i,j,g) == NULL){
      insert_new_arc(i,j,dij,g);
      insert_new_arc(j,i,dij,g);
    }
    scanf("%d", &i);
  }
  return g;
}

void dijkstra(int start, GRAFO* g) {
  HEAPMIN* q;
  int v, w, i;
  ARCO* cur_adj;

  for (i=1; i<=NUM_VERTICES(g); i++) {
    dist[i] = INT_MAX;
    pai[i] = 0;
  }

  dist[start] = 0;
  printf("%d", start);
  q = build_heap_min(dist, NUM_VERTICES(g));
  while (!heap_isEmpty(q)) {
    v = extractMin(q);
    cur_adj = ADJS_NO(v,g);
    if (dist[v] != INT_MAX) {
      while (cur_adj != NULL) {
        w = EXTREMO_FINAL(cur_adj);
        if (VALOR_ARCO(cur_adj) + dist[v] < dist[w]) {
          dist[w] = VALOR_ARCO(cur_adj) + dist[v];
          pai[w] = v;
          decreaseKey(w,dist[w],q);
        }
        cur_adj = PROX_ADJ(cur_adj);
      }
      if (v != start)
      printf(" %d",v);
    }
  }
  printf("\n");
}
int main() {
  int n_lojas, loja_destino;
  GRAFO* g;

  scanf("%d %d", &n_lojas, &loja_destino);

  g = ler_construir_grafo(n_lojas); 

  dijkstra(loja_destino, g);

  return 0;
}