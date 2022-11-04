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

#define MAXVERTS 500    // numero maximo de vertices (alterar se necessario)
#define BRANCO   0
#define CINZENTO 1
#define PRETO    2

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

/*--------------------------------------------------------------------\
|                                                                     |
|  Definição dum tipo abstracto de dados  STACK:                      |
|    ("pilha" com elementos do tipo int)                              |
|                                                                     |
|   A.P.Tomás, CC211 (material para prova pratica), DCC-FCUP, 2012    |
|   Last modified: 2012.12.28                                         |
\--------------------------------------------------------------------*/


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

////////////////////////////
//                        //
//        SOCIOLOGIA      // 
//                        //
////////////////////////////


//variaveis globais
STACK* s;
int cor[MAXVERTS+1];
int contador_alunos;
int cont_groups = 0;
int cont_outsiders = 0;
int n_alunos;
BOOL imprime;

GRAFO* ler_construir_grafo() {
  GRAFO* g;
  int i, n_amigos, aluno_id, amigo_id;

  scanf("%d", &n_alunos);
  g = new_graph(n_alunos);
  for (i=1; i<=n_alunos; i++) {
    scanf("%d %d", &aluno_id, &n_amigos);
    while (n_amigos){
      scanf("%d", &amigo_id);
      if (find_arc(aluno_id,amigo_id,g) == NULL)
        insert_new_arc(aluno_id,amigo_id,g);
      n_amigos--;
    }
  }
  return g;
}

void dfs(GRAFO* g){
  int i;
  s = st_make_empty(n_alunos);
  for (i=1; i<=n_alunos; i++)
    cor[i] = BRANCO;

  for (i=1; i<=n_alunos; i++) {
    if(cor[i] == BRANCO)
      dfs_visit(i,g);
  }
}

GRAFO* construir_transposto(GRAFO* g) {
  GRAFO* gt;
  ARCO* cur_adj;
  int w, i;

  gt = new_graph(n_alunos);
  for (i=1; i<=n_alunos; i++) {
    cur_adj = ADJS_NO(i,g);
    while (cur_adj != NULL) {
      w = EXTREMO_FINAL(cur_adj);
      if(find_arc(w,i,gt) == NULL)
        insert_new_arc(w,i,gt);
      cur_adj = PROX_ADJ(cur_adj);
    }
  }
  return gt;
}

void dfs_visit(int start, GRAFO* g) {
  int w;
  ARCO* cur_adj;

  cor[start] = CINZENTO;
  cur_adj = ADJS_NO(start,g);
  while (cur_adj != NULL) {
    w = EXTREMO_FINAL(cur_adj);
    if (cor[w] == BRANCO) {
      dfs_visit(w,g);
      if(imprime == TRUE)
        contador_alunos++;
    }
    else if (cor[w] == CINZENTO) {
      /* erro, declarar ciclo */
      printf("ERRO!! Ciclo existente no grafo\n");
    }
    cur_adj = PROX_ADJ(cur_adj);
  }
  cor[start] = PRETO;
  if (imprime == FALSE) {
    st_push(s,start);
  }
}

int main() {
  int v, n_cenarios, i, j;
  GRAFO* g;
  GRAFO* gt;
  
  scanf("%d", &n_cenarios);
  for (i = 1; i < n_cenarios; i++) {
    imprime = FALSE;
    cont_groups = 0;
    cont_outsiders = 0;
    g = ler_construir_grafo();
    dfs(g);
    gt = construir_transposto(g);
    imprime = TRUE;

    // redefinir array de cores para voltar a fazer o dfs
    for (j=1; j<=n_alunos; j++) 
      cor[j] = BRANCO;

    while (!st_is_empty) {
      v = st_pop(s);
      if (cor[v] == BRANCO){
        contador_alunos = 1;
        dfs_visit(v,gt);
        if (contador_alunos >= 4) 
          cont_groups++;
        else
          cont_outsiders += contador_alunos;
      }
    }
    printf("Caso #%d\n%d %d\n", i, cont_groups, cont_outsiders); 
  }
  return 0;
}