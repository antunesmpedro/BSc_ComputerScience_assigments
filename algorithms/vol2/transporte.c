/*-------------------------------------------------------------------*\
|  TAD para implementacao de grafo dirigido com TRES pesos (int)      |
|                                                                     |
|    Versão simplificada;  |V| <=  MAXVERTS;                          |
|     Assume-se que os vértices são numerados de 1 a |V|.             |
|                                                                     |
|   A.P.Tomás, CC2001 (material para prova pratica), DCC-FCUP, 2017   |
|   Last modified: 2017.12.18                                         |
\--------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>

#define MAXVERTS 500
// numero maximo de vertices (alterar se necessario)


typedef struct arco {
  int no_final;
  int valor[3];    // TRES valores
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
void insert_new_arc(int i, int j, int valor0, int valor1, int valor2, GRAFO *g);
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
#define VALOR3_ARCO(arco) ((arco) -> valor[2])
// acesso ao valor3 do arco

//======  protótipos de funções auxiliares (privadas) ======
static ARCO* cria_arco(int, int valor1,int valor2, int valor3);
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
void insert_new_arc(int i, int j, int valor1, int valor2, int valor3, GRAFO *g)
{ /* insere arco (i,j) no grafo g, bem como os seus pesos  */

  ARCO *arco = cria_arco(j,valor1,valor2,valor3);
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
static ARCO *cria_arco(int j, int valor1, int valor2, int valor3)
{ // cria um novo adjacente
  ARCO *arco = (ARCO *) malloc(sizeof(ARCO));
  if (arco == NULL) {
    fprintf(stderr,"ERROR: cannot create arc\n");
    exit(EXIT_FAILURE);
  }
  EXTREMO_FINAL(arco) = j;
  VALOR1_ARCO(arco) = valor1;
  VALOR2_ARCO(arco) = valor2;
  VALOR3_ARCO(arco) = valor3;
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

/////////////////////////////////
//      TRANSPORTE RAPIDO      //
/////////////////////////////////

GRAFO * g;
int j_larg_minima, j_larg_maxima, j_comp_minima, j_comp_maxima, j_alt_minima;
int pai[MAXVERTS];

GRAFO* construir_grafo(int n) {
  GRAFO* g;
  int start, end, larg_t_max, comp_t_max, alt_t_max;

  g = new_graph(n);
  scanf("%d", &start);
  while (start != -1) {
    scanf("%d %d %d %d", &end, &larg_t_max, &comp_t_max, &alt_t_max);
    if (find_arc(start,end,g) == NULL &&
       start>=1 && start<=n &&
       end>=1 && end<=n) {
      insert_new_arc(start,end,larg_t_max,comp_t_max,alt_t_max,g);
      insert_new_arc(end,start,larg_t_max,comp_t_max,alt_t_max,g);
    }
    scanf("%d", &start);
  }
  return g;
}

void conta_caminho(int v, int pai[], int val){
  if(pai[v]!=-1)
    conta_caminho(pai[v], pai, val+1);
  else 
    printf("%d\n", val);
}

int bfs(int origem, int destino, GRAFO* g) {
  int i, v, w;
  //BOOL encontrou = FALSE;
  QUEUE* q;
  ARCO* arc;
  int visitados[NUM_VERTICES(g)+1];

  for (i=1; i<=NUM_VERTICES(g); i++){
    visitados[i] = FALSE;
    pai[i] = 0;
  }

  q= mk_empty_queue(NUM_VERTICES(g));
  visitados[origem] = TRUE;
  pai[origem] = -1;
  enqueue(origem,q);
  while (queue_is_empty(q) == FALSE) {
    v = dequeue(q);
    arc = ADJS_NO(v,g);
    while (arc != NULL) {
      w = EXTREMO_FINAL(arc);
      //printf("\tadjacente %d > %d\n", v,w);
      //printf("\t %d | larg %d<=%d<=%d | comp %d<=%d<=%d | alt %d<=%d\n",
       //visitados[w], j_larg_minima, VALOR1_ARCO(arc), j_larg_maxima, j_comp_minima, VALOR2_ARCO(arc), j_comp_maxima, j_alt_minima, VALOR3_ARCO(arc));
      if (visitados[w] == FALSE && j_alt_minima<=VALOR3_ARCO(arc) &&
          j_larg_minima<=VALOR1_ARCO(arc) && j_comp_minima<=VALOR2_ARCO(arc)) {
        visitados[w] = TRUE;
        pai[w] = v;
        enqueue(w,q);
        //printf("\tvalido %d > %d\n", v,w);
      }
      arc = PROX_ADJ(arc);
    }
  }
  if (pai[destino] == 0)
      return 0;
  else
    return 1;
}

int main() {
  int n_locais;
  int origem_animal, destino_animal;

  scanf("%d", &n_locais);
  scanf("%d %d %d %d %d", &j_larg_minima, &j_larg_maxima, &j_comp_minima, &j_comp_maxima, &j_alt_minima);
  scanf("%d %d", &origem_animal, &destino_animal);

  g = construir_grafo(n_locais);

  if (bfs(origem_animal,destino_animal,g) == 0) {
    if (bfs(destino_animal,origem_animal,g) == 0)
      printf("Impossivel\n");
    else
      conta_caminho(destino_animal,pai,0);
  }
  else
    conta_caminho(destino_animal,pai,0);
  
  return 0;
}

/*if (visitados[w] == FALSE && j_alt_minima<=VALOR3_ARCO(arc) &&
          j_larg_minima<=VALOR1_ARCO(arc) && j_larg_maxima>=VALOR1_ARCO(arc) &&
          j_comp_minima<=VALOR2_ARCO(arc) && j_comp_maxima>=VALOR2_ARCO(arc)) {
        visitados[w] = TRUE;
        pai[w] = v;
        enqueue(w,q);
        //printf("\tvalido %d > %d\n", v,w);
}*/