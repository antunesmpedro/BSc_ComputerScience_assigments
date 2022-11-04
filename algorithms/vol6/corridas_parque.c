#include <stdio.h>

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

#define MAXVERTS 15
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

/*--------------------------------------------------------------------\
| Definição de um tipo abstracto de dados QUEUE:                      |
|   filas  (FIFO) com valores do tipo int                             |
|                                                                     |
|   A.P.Tomás, CC211 (material para prova pratica), DCC-FCUP, 2012    |
|   Last modified: 2012.12.28                                         |
\--------------------------------------------------------------------*/


#include <stdio.h>
#include <stdlib.h>

typedef enum {FALSE,TRUE} BOOL;


typedef struct fila {
  int inicio, fim, nmax;
  int *queue;
} QUEUE;


// criar fila com capacidade para n inteiros
QUEUE *mk_empty_queue(int n);
// colocar valor na fila
void enqueue(int v,QUEUE *f);
// retirar valor na fila
int dequeue(QUEUE *f);
// verificar se a fila está vazia
BOOL queue_is_empty(QUEUE *f);
// verificar se a fila não admite mais elementos
BOOL queue_is_full(QUEUE *f);
// liberta fila
void free_queue(QUEUE *f);


//-------------- Implementação ---------------------------------------




// funcao auxiliar (privada)

static void queue_exit_error(char *msg);

static void queue_exit_error(char *msg)
{ 
  fprintf(stderr,"Error: %s.\n",msg);
  exit(EXIT_FAILURE);
}




// criar fila com capacidade para n inteiros
QUEUE *mk_empty_queue(int n)
{
  QUEUE *q = (QUEUE *) malloc(sizeof(QUEUE));
  if (q == NULL) 
    queue_exit_error("sem memoria");

  q -> queue =  (int *) malloc(sizeof(int)*n);
  if (q -> queue == NULL) 
    queue_exit_error("sem memoria");

  q -> nmax = n;
  q -> inicio = -1;
  q -> fim = 0;
  return q;
}

// libertar fila
void free_queue(QUEUE *q)
{
  if (q != NULL) {
    free(q -> queue);
    free(q);
  } else 
    queue_exit_error("fila mal construida");
}


// colocar valor na fila
void enqueue(int v,QUEUE *q)
{  
  if (queue_is_full(q) == TRUE) 
    queue_exit_error("fila sem lugar");

  if (q -> queue == NULL) 
    queue_exit_error("fila mal construida");

  if (queue_is_empty(q)==TRUE) 
    q -> inicio = q -> fim; // fila fica com um elemento
  q -> queue[q->fim] = v;
  q -> fim = (q -> fim+1)%(q->nmax);
}

// retirar valor na fila
int dequeue(QUEUE *q)
{  
  int aux;
  if (queue_is_empty(q) == TRUE) 
    queue_exit_error("fila sem valores");

  if (q -> queue == NULL) 
    queue_exit_error("fila mal construida");

  aux = q ->queue[q ->inicio];
  q -> inicio = (q -> inicio+1)%(q -> nmax);
  if (q -> inicio ==  q -> fim) {  // se só tinha um elemento
    q -> inicio = -1; q -> fim = 0;  
  }
  return aux;
}

// verificar se a fila está vazia
BOOL queue_is_empty(QUEUE *q)
{ 
  if (q == NULL) 
    queue_exit_error("fila mal construida");

  if (q -> inicio == -1) return TRUE;
  return FALSE;
}

// verificar se a fila não admite mais elementos
BOOL queue_is_full(QUEUE *q)
{ 
  if (q == NULL) 
    queue_exit_error("fila mal construida");

  if (q -> fim == q -> inicio) return TRUE;
  return FALSE;
}

///////////////////////////////////////////
///////////////////////////////////////////
///////////////////////////////////////////

int pai[MAXVERTS+1];
BOOL visitados[MAXVERTS+1];

GRAFO* ler_construir_grafo() {
	GRAFO* g;
	int n, e, x, y;

	scanf("%d %d", &n, &e);
	g = new_graph(n);
	while (e) {
		scanf("%d %d", &x, &y);
		if ( find_arc(x,y,g)==NULL ){
			insert_new_arc(x,y,1,g);
			insert_new_arc(y,x,1,g);
		}
		e--;
	}
	return g;
}

void atualiza_grafo(GRAFO*g) {
  int t = NUM_VERTICES(g);
  int s = 1;
  while (t != s){
    int p = pai[t];

    ARCO* arc = find_arc(p,t,g);
    remove_arc(arc,p,g);
    insert_new_arc(p,t,0,g); 
  
    t = p;
  }
}

int bfs(int start, GRAFO* g) {
	QUEUE* q = mk_empty_queue(NUM_VERTICES(g));
	int v,w;
	ARCO* cur_adj;

	for(int i=1; i<=NUM_VERTICES(g); i++) {
		visitados[i] = FALSE;
		pai[i] = 0;
	}

	pai[start] = -1;
	visitados[start] = TRUE;
	enqueue(start,q);
	while ( !queue_is_empty(q) ) {
		v = dequeue(q);
    
    if (v == NUM_VERTICES(g)) break;

		cur_adj = ADJS_NO(v,g);
		while (cur_adj != NULL) {
			w = EXTREMO_FINAL(cur_adj);

			if (visitados[w] == FALSE && VALOR_ARCO(cur_adj) == 1) {
        //printf("%d -> %d\n", v, w);
				visitados[w] = TRUE;
				enqueue(w,q);
				pai[w] = v;
			}
			
			cur_adj = PROX_ADJ(cur_adj);
		}
	}
  
  if (visitados[NUM_VERTICES(g)] == FALSE)
    return 0;
  
  atualiza_grafo(g);
  return 1;
}

int main() {
	GRAFO* g;
  int caminhos = 0;
	g = ler_construir_grafo();
	while ( bfs(1,g) ) {
    caminhos++;
	}

  printf("%d\n", caminhos);

	return 0;
}