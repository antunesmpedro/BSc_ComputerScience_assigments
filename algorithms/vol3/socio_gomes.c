/*-------------------------------------------------------------------*\
|  grafos0.h  --- TAD para implementacao de grafo dirigido SEM pesos  |
|                                                                     |
|    Versão simplificada;  |V| <=  MAXVERTS;                          |
|     Assume-se que os vértices são numerados de 1 a |V|.             |
|                                                                     |
|   A.P.Tomás, CC2001 (material para prova pratica), DCC-FCUP, 2017   |
|   Last modified: 2017.12.18                                         |
\--------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>

#define MAXVERTS 1000
// numero maximo de vertices (alterar se necessario)


typedef struct arco {
  int no_final;
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
void insert_new_arc(int i, int j, GRAFO *g);
/* insere arco (i,j) no grafo; não evita repetições */
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


//======  protótipos de funções auxiliares (privadas) ======
static ARCO* cria_arco(int);
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
void insert_new_arc(int i, int j, GRAFO *g)
{ /* insere arco (i,j) no grafo g  */

  ARCO *arco = cria_arco(j);
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
static ARCO *cria_arco(int j)
{ // cria um novo adjacente
  ARCO *arco = (ARCO *) malloc(sizeof(ARCO));
  if (arco == NULL) {
    fprintf(stderr,"ERROR: cannot create arc\n");
    exit(EXIT_FAILURE);
  }
  EXTREMO_FINAL(arco) = j;
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

// definição de BOOL 
typedef enum {FALSE,TRUE} BOOL;


//-----------------------------------------------------------------------
// definicao do tipo STACK (top indica a primeira posicao livre e
// a stack pode ter maxstack elementos no maximo; maxstack fixado na criacao)
//-----------------------------------------------------------------------

typedef struct {
  int top, maxstack;
  int *stack;
} STACK;

// protótipos das funções para interface a uma pilha 
STACK *st_make_empty(int nmax);
void st_destroy(STACK *pstack);
BOOL st_is_empty(STACK *pstack);
BOOL st_is_full(STACK *pstack);
void st_push(STACK *pstack,int x);
int st_pop(STACK *pstack);



// ------------------- implementacao ------------------------------------

// funcao auxiliar (privada)

static void st_exit_error(char *msg);

static void st_exit_error(char *msg)
{ 
  fprintf(stderr,"Error: %s.\n",msg);
  exit(EXIT_FAILURE);
}


STACK *st_make_empty(int nmax)
{ 
  if (nmax <= 0) 
    st_exit_error("invalid stack");

  STACK *ps = (STACK *) malloc(sizeof(STACK));
  if (ps == NULL) 
    st_exit_error("invalid stack");

  ps -> stack = (int *) malloc(sizeof(int)*nmax);
  if (ps -> stack == NULL) 
    st_exit_error("invalid stack");
  
  ps -> top = 0;  
  ps -> maxstack = nmax;
  return ps;
}

BOOL st_is_empty(STACK *ps) 
{
  if (ps == NULL) 
    st_exit_error("invalid stack");

  if (ps -> top == 0) 
    return TRUE;
  return FALSE;
}

BOOL st_is_full(STACK *ps)
{ 
  if (ps == NULL) 
    st_exit_error("invalid stack");

  if (ps -> top == ps -> maxstack) 
    return TRUE;
  return FALSE;
}

void st_destroy(STACK *ps)
{ 
  if (ps == NULL) 
    st_exit_error("invalid stack");

  free(ps -> stack);
  free(ps);
}


void st_push(STACK *ps, int x)
{ 
  if (st_is_full(ps) == TRUE) 
    st_exit_error("stack is full");

  if (ps -> stack == NULL)     
    st_exit_error("invalid stack");

  ps -> stack[ps -> top] = x;
  ps -> top++; 
}

int st_pop(STACK *ps)
{ 
  if (st_is_empty(ps)== TRUE) 
    st_exit_error("stack is empty");

  if (ps -> stack == NULL)     
    st_exit_error("invalid stack");

  ps -> top--;  
  return ps -> stack[ps ->top]; 
}


GRAFO *ler_grafo(){
  int n_alunos;
  scanf("%d", &n_alunos);
  GRAFO *g;
  g =new_graph(n_alunos);
  while(n_alunos>0){
    int id, t;
    scanf("%d %d", &id, &t);
    while(t>0){
      int adj;
      scanf("%d", &adj);
      insert_new_arc(id,adj, g);
      t--;
    }
    n_alunos--;
  }
  return g;
}

GRAFO *construir_trans(GRAFO *g, BOOL visited[]){
  GRAFO *gt;
  int n = NUM_VERTICES(g);
  gt = new_graph(n);
  for (int i = 1; i <=n; ++i){
    ARCO *adj=ADJS_NO(i,g);
    while(adj!=NULL){
      int w=EXTREMO_FINAL(adj);
      insert_new_arc(w,i,gt);
      adj=PROX_ADJ(adj);
    }
  }
  return gt;
}

void dfs(GRAFO *g, STACK *s, BOOL visitado[], int v){
  visitado[v]=TRUE;
  ARCO *adj =ADJS_NO(v,g);
  while(adj!=NULL){
    int w = EXTREMO_FINAL(adj);
    if(visitado[w]==FALSE){
      dfs(g,s,visitado,w);
    }
    adj=PROX_ADJ(adj);
  }
  st_push(s,v);
}

int dfs_visit(GRAFO *gt, int v, BOOL visitado[]){
  ARCO *adj=ADJS_NO(v,gt);
  visitado[v]=TRUE;
  int cont=1;
  while(adj!=NULL){
    int w=EXTREMO_FINAL(adj);
   
    if(visitado[w]==FALSE){
      cont +=dfs_visit(gt,w,visitado);
    }
    adj=PROX_ADJ(adj);
  }
  return cont;
}

void ler_analisa(GRAFO *g){
  int n= NUM_VERTICES(g);
  STACK *s = st_make_empty(n);
  BOOL visitado[n+1];
  BOOL visited[n+1];
  for (int i = 1; i <= n; ++i)
  {
    visitado[i]=FALSE;
  }
  for (int i = 1; i <=n; ++i)
  {
    if(visitado[i]==FALSE)
      dfs(g,s,visitado, i);
  }
  for (int i = 1; i <= n; ++i)
  {
    visitado[i]=FALSE;
    visited[i]=FALSE;
  }
  GRAFO *gt=construir_trans(g, visited);
  int dentro=0, fora=0;

  while(st_is_empty(s)==FALSE){
    int v =st_pop(s);
    if(visitado[v]==FALSE){
      int numero = dfs_visit(gt, v, visitado);
     
      if(numero>=4)
        dentro++;
      else
        fora+=numero;
    }
  }
  printf("%d %d\n",dentro, fora );
}

int main(){
  int n;
  scanf("%d", &n);
  int i=1;
  while(i<=n){
    GRAFO *g=ler_grafo();
    printf("Caso #%d\n", i);
    ler_analisa(g);
    i++;
  }
}