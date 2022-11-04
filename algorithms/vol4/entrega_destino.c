/*-------------------------------------------------------------------*\
|  TAD para implementacao de grafo dirigido com DOIS pesos (int)      |
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

#define MAXVERTS 20000
// numero maximo de vertices (alterar se necessario)


typedef struct arco {
  int no_final;
  int valor[2];    // DOIS valores
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
void insert_new_arc(int i, int j, int valor0, int valor1, GRAFO *g);
/* insere arco (i,j) no grafo, bem como os dois pesos; não evita repetições */
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
// acesso ao extremo final de arco
#define VALOR1_ARCO(arco) ((arco) -> valor[0])
// acesso ao valor1 do arco
#define VALOR2_ARCO(arco) ((arco) -> valor[1])
// acesso ao valor2 do arco

//======  protótipos de funções auxiliares (privadas) ======
static ARCO* cria_arco(int, int valor1,int valor2);
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
void insert_new_arc(int i, int j, int valor1, int valor2, GRAFO *g)
{ /* insere arco (i,j) no grafo g, bem como os seus pesos  */

  ARCO *arco = cria_arco(j,valor1,valor2);
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
static ARCO *cria_arco(int j, int valor1, int valor2)
{ // cria um novo adjacente
  ARCO *arco = (ARCO *) malloc(sizeof(ARCO));
  if (arco == NULL) {
    fprintf(stderr,"ERROR: cannot create arc\n");
    exit(EXIT_FAILURE);
  }
  EXTREMO_FINAL(arco) = j;
  VALOR1_ARCO(arco) = valor1;
  VALOR2_ARCO(arco) = valor2;
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
|  Exemplo de implementacao de fila de prioridade (por heap de máximo)    |
|                                                                         |
|   A.P.Tomás, CC2001 (material para prova pratica), DCC-FCUP, 2017       |
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

//---------  protótipos das funções disponíveis --------------------

HEAPMAX *build_heap_max(int v[], int n);
void insert(int v, int key, HEAPMAX *q);
int extractMax(HEAPMAX *q);   // retorna v 
void increaseKey(int v, int newkey, HEAPMAX *q);
int heap_isEmpty(HEAPMAX *q);  // retirna 1 ou 0


void write_heap(HEAPMAX *q);
void destroy_heap(HEAPMAX *q);


//----------------- definição das funções e macros ---------------------

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
  // supor que vetor vec[.] guarda elementos nas posições 1 a n
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
    

////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////

typedef enum {TRUE, FALSE} BOOL;

int cap[MAXVERTS+1];

GRAFO* ler_contruir_grafo(int max) {
	int n_trajetos, n_nos, k, comp, i, j;
	GRAFO* g;
	int n_limites, alt, larg;

	scanf("%d %d", &n_trajetos, &n_nos);
	g = new_graph(n_nos);

	while (n_trajetos) {
		scanf("%d %d", &k, &i);
		k--;
		while (k) {
			scanf("%d %d", &comp, &j);
			if (find_arc(i,j,g) == NULL) {
				insert_new_arc(i,j,max,max,g);
				insert_new_arc(j,i,max,max,g);
			}
			i = j;
			k--;
		}
		n_trajetos--;
	}
	scanf("%d", &n_limites);
	while (n_limites) {
		scanf("%d %d %d %d", &i, &j, &alt, &larg);
		ARCO* arc1 = find_arc(i,j,g);
		int cur_alt = VALOR1_ARCO(arc1);
		int cur_larg = VALOR2_ARCO(arc1);
		remove_arc(arc1,i,g);
		ARCO* arc2 = find_arc(j,i,g);
		remove_arc(arc2,j,g);
		if (larg == -1) {
			insert_new_arc(i,j,alt,cur_larg,g);
			insert_new_arc(j,i,alt,cur_larg,g);
		}
		else if(alt == -1) {
			insert_new_arc(i,j,cur_alt,larg,g);
			insert_new_arc(j,i,cur_alt,larg,g);
		}
		else {
			insert_new_arc(i,j,alt,larg,g);
			insert_new_arc(j,i,alt,larg,g);
		}
		n_limites--;
	}
	return g;
}

int min(int one, int two) {
	if (one > two)
		return two;
	return one;
}

void dijkstra(int start, int cap_max, GRAFO* g) {
	int v,w,i, val;
	HEAPMAX* q;
	ARCO* cur_adj;

	for (i=1;i<=NUM_VERTICES(g);i++) 
		cap[i] = 0;

	cap[start] = cap_max;
	q = build_heap_max(cap,NUM_VERTICES(g));
	while (!heap_isEmpty(q)){
		v = extractMax(q);
		if (cap[v] != 0){
			cur_adj = ADJS_NO(v,g);
			while (cur_adj) {
				w = EXTREMO_FINAL(cur_adj);
				int alt = VALOR1_ARCO(cur_adj);
				int larg = VALOR2_ARCO(cur_adj);
				val = min(alt,larg);
				if (min(val,cap[v]) > cap[w]) {
					cap[w] = min(val,cap[v]);
					//printf("v-%d > w-%d | alt-%d, larg-%d | cap[%d]=%d\n", v, w,alt,larg,w,cap[w]);
					increaseKey(w,cap[w],q);
				}
				cur_adj = PROX_ADJ(cur_adj);
			}
		}
		else break;
	}
}

int main() {
	int origem, larg_min, larg_max, i;
	GRAFO* g;
	BOOL problemas = FALSE;

	scanf("%d %d %d", &origem, &larg_min, &larg_max);
	g = ler_contruir_grafo(larg_max);
	dijkstra(origem,larg_max,g);
	
	for(i=1; i<=NUM_VERTICES(g); i++) {
		//printf("cap[%d]=%d\n",i,cap[i]);
		if (cap[i] < larg_min){
			printf("No %d: 0\n", i);
			problemas = TRUE;
		}
		else if (cap[i] < larg_max){
			printf("No %d: %d\n", i, cap[i]);
			problemas = TRUE;
		}
	}

	if (problemas == FALSE) 
		printf("Ok todos destinos!\n");

	return 0;
}