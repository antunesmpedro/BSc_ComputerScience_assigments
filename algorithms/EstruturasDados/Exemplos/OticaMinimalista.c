/*------------------------------------------------------\
|       Otica Minimalista                               |
|  Exemplos disponiveis  -- Prova pratica  2017         |
|  A.P. Tomas (Dez 2017)                                |
\*-----------------------------------------------------*/


/*-------------------------------------------------------------------*\
|  TAD para implementacao de grafo dirigido com UM peso (int)         |
|                                                                     |
|    Vers�o simplificada;  |V| <=  MAXVERTS;                          |
|     Assume-se que os v�rtices s�o numerados de 1 a |V|.             |
|                                                                     |
|   A.P.Tom�s, CC2001 (material para prova pratica), DCC-FCUP, 2017   |
|   Last modified: 2017.12.18                                         |
\--------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>

#define MAXVERTS 1000
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
  NO verts[MAXVERTS+1];  // n�s implicitamente numerados de 1 a nvs
  int nvs, narcos;
} GRAFO;

//--- prot�tipos das fun��es dispon�veis----------------------------
//    ATEN��O AOS TIPOS DE ARGUMENTOS E DE RESULTADO


GRAFO *new_graph(int nverts);
/* cria um grafo com nverts vertices e sem arcos */
void destroy_graph(GRAFO *g);
/* liberta o espa�o reservado na cria��o do grafo */
void insert_new_arc(int i, int j, int valor_ij, GRAFO *g);
/* insere arco (i,j) no grafo, bem como o seu peso; n�o evita repeti��es */
void remove_arc(ARCO *arco, int i, GRAFO *g);
/* retira adjacente arco da lista de adjacentes de i */
ARCO *find_arc(int i, int j, GRAFO *g);
/* retorna um apontador para o arco (i,j) ou NULL se n�o existir */

//--- macros de acesso aos campos da estrutura --------------------------

#define NUM_VERTICES(g) ( (g) -> nvs )
// numero de vertices
#define NUM_ARCOS(g) ( (g) -> narcos )
// numero de arcos
#define ADJS_NO(i,g) ( (g) -> verts[i].adjs )
// primeiro arco da lista de adjacentes do n� i
#define PROX_ADJ(arco) ((arco) -> prox)
// proximo adjacente 
#define ADJ_VALIDO(arco) (((arco) != NULL))
// se arco � v�lido
#define EXTREMO_FINAL(arco) ((arco) -> no_final)
// qual o extremo final de arco
#define VALOR_ARCO(arco) ((arco) -> valor)
// qual o valor do arco

//======  prot�tipos de fun��es auxiliares (privadas) ======
static ARCO* cria_arco(int, int valor_ij);
static void free_arcs(ARCO *);


//======  Implementa��o (defini��o das fun��es) ========================

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
  ADJS_NO(i,g) = arco;  // novo adjacente fica � cabe�a da lista
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

// retorna um apontador para o arco (i,j) ou NULL se n�o existir 
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


//======================== Heapmax


/*-----------------------------------------------------------------------*\
|  Exemplo de implementacao de fila de prioridade (por heap de m�ximo)    |
|                                                                         |
|   A.P.Tom�s, CC2001 (material para prova pratica), DCC-FCUP, 2017       |
|   Last modified: 2017.12.18                                             |
\*-----------------------------------------------------------------------*/

#include<stdio.h>
#include<stdlib.h>

typedef struct qnode {
  int vert, vertkey;
} QNODE;

typedef struct heapMax {
  int sizeMax, size;
  QNODE *a;
  int *pos_a;
} HEAPMAX;

//---------  prot�tipos das fun��es dispon�veis --------------------

HEAPMAX *build_heap_max(int v[], int n);
void insert(int v, int key, HEAPMAX *q);
int extractMax(HEAPMAX *q);   // retorna v 
void increaseKey(int v, int newkey, HEAPMAX *q);
int heap_isEmpty(HEAPMAX *q);  // retirna 1 ou 0


void write_heap(HEAPMAX *q);
void destroy_heap(HEAPMAX *q);


//----------------- defini��o das fun��es e macros ---------------------

#define POSINVALIDA 0

#define LEFT(i) (2*(i))
#define RIGHT(i) (2*(i)+1)
#define PARENT(i) ((i)/2)

static void heapify(int i,HEAPMAX *q);
static void swap(int i,int j,HEAPMAX *q);
static int compare(int i, int j, HEAPMAX *q);
static int pos_valida(int i,HEAPMAX *q);

static int compare(int i, int j, HEAPMAX *q){
  if (q -> a[i].vertkey < q -> a[j].vertkey)
    return -1;
  if (q -> a[i].vertkey == q -> a[j].vertkey)
    return 0;
  return 1;
}


static int pos_valida(int i, HEAPMAX *q) {
  return (i >= 1 && i <= q -> size);
}

int extractMax(HEAPMAX *q) {
  int vertv = q -> a[1].vert;
  swap(1,q->size,q);
  q -> pos_a[vertv] = POSINVALIDA;  // assinala vertv como removido
  q -> size--;
  heapify(1,q);
  return vertv;
}

void increaseKey(int vertv, int newkey, HEAPMAX *q){
  int i = q -> pos_a[vertv];
  q -> a[i].vertkey = newkey;

  while(i > 1 && compare(i,PARENT(i),q) > 0){
    swap(i,PARENT(i),q);
    i = PARENT(i);
  }
}


static void heapify(int i,HEAPMAX *q) {
  // para heap de maximo
  int l, r, largest;
  l = LEFT(i);
  if (l > q -> size) l = i;
  r = RIGHT(i);
  if (r > q -> size) r = i;
  
  largest = i;
  if (compare(l,largest,q) > 0) 
    largest = l;
  if (compare(r,largest,q) > 0) 
    largest = r;
  
  if (i != largest) {
    swap(i,largest,q);
    heapify(largest,q);
  }
}

static void swap(int i,int j,HEAPMAX *q){
  QNODE aux;
  q -> pos_a[q -> a[i].vert] = j;
  q -> pos_a[q -> a[j].vert] = i;
  aux = q -> a[i];
  q -> a[i] = q -> a[j];
  q -> a[j] = aux;
}



HEAPMAX *build_heap_max(int vec[], int n){
  // supor que vetor vec[.] guarda elementos nas posi��es 1 a n
  // cria heapMax correspondente em tempo O(n)
  HEAPMAX *q = (HEAPMAX *)malloc(sizeof(HEAPMAX));
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


void insert(int vertv, int key, HEAPMAX *q)
{ 
  if (q -> sizeMax == q -> size) {
    fprintf(stderr,"Heapmax is full\n");
    exit(EXIT_FAILURE);
  }
  q -> size++;
  q -> a[q->size].vert = vertv;
  q -> pos_a[vertv] = q -> size;   // supondo 1 <= vertv <= n
  increaseKey(vertv,key,q);   // aumenta a chave e corrige posicao se necessario
}

int heap_isEmpty(HEAPMAX *q){
  if (q -> size == 0) return 1;
  return 0;
}


// --------- auxiliar para ver conteudo  ---------------------
void write_heap(HEAPMAX *q){
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


void destroy_heap(HEAPMAX *q){
  if (q != NULL) {
    free(q -> a);
    free(q -> pos_a);
    free(q);
  }
}
    
//============================ Resolve Otica Minimalista

GRAFO *lerDados(int *custo);
int resolve(GRAFO *g,int nverts,int custo);


GRAFO *lerDados(int *custo){
  int i, origem, fim, rendbruto, nverts, nramos;
  GRAFO *g;

  scanf("%d%d%d",&nverts,&nramos,custo);

  g = new_graph(nverts);

  for(i = 0; i < nramos; i++){
    scanf("%d%d%d",&origem,&fim,&rendbruto);
    insert_new_arc(origem,fim,rendbruto,g);
    insert_new_arc(fim,origem,rendbruto,g);
  }
  return g;
}


#define INFMIN -1
#define TRUE 1
#define FALSE 0

int resolve(GRAFO *g,int nverts,int custo) {
  int dist[nverts + 1], inQueue[nverts + 1], v, w, rendimento;

  for(v = 1;v <= nverts; v++) {
    dist[v] = INFMIN; 
    inQueue[v] = TRUE;
  }
  dist[1] = 0;

  rendimento = 0;

  HEAPMAX *q = build_heap_max(dist,nverts);

  while(! heap_isEmpty(q) ) {
    v = extractMax(q);
    inQueue[v] = FALSE;
    
    if (dist[v] == INFMIN) 
      return INFMIN;  
    
    rendimento += dist[v];
    
    ARCO *a = ADJS_NO(v,g);
    while (a != NULL) {
      w = EXTREMO_FINAL(a);
      if (inQueue[w] == TRUE && VALOR_ARCO(a) > dist[w]){
	dist[w] = VALOR_ARCO(a);
	increaseKey(w,dist[w],q);
      }
      a = PROX_ADJ(a);
    }
  }
  return rendimento-custo*(nverts-1);
}

int main(){
  int rendimento, custo;
  GRAFO *g = lerDados(&custo);

  rendimento = resolve(g,NUM_VERTICES(g),custo);

  if (rendimento == INFMIN)
    printf("impossivel\n");
  else 
    printf("rendimento optimo: %d\n", rendimento);

  return 0;
}
