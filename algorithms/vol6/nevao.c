/*-------------------------------------------------------------------*\
|  TAD para implementacao de grafo dirigido com DOIS pesos (int)      |
|                                                                     |
|    Versão simplificada;  |V| <=  MAXVERTS;                          |
|     Assume-se que os vértices são numerados de 1 a |V|.             |
|                                                                     |
|   A.P.Tomás, CC2001 (material para prova pratica), DCC-FCUP, 2017   |
|   Last modified: 2017.12.18                                         |
\--------------------------------------------------------------------*/
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

#define MAXVERTS 16000
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


////////////////////////////////////////////////// NEVAO
////////////////////////////////////////////////// NEVAO
////////////////////////////////////////////////// NEVAO

int pai[MAXVERTS+1];
BOOL visitados[MAXVERTS+1];
int cont_nos =2;
int nos[MAXVERTS+1];
int **fluxos_matriz;
GRAFO* gf;

// renomear id dos nos
int procura(int val) {
  int k;

  for(k=1;k<=cont_nos;k++){
    //printf("nos[%d]=%d\n",k,nos[k]);
    if (nos[k] == val)
      return k;
  }
  cont_nos++;  
  nos[cont_nos] = val;
  return cont_nos;
}

GRAFO* ler_construir_grafo(int r) {
	int origem, destino, capacidade, fluxo;
	GRAFO* g = new_graph(MAXVERTS);

	while (r){
		scanf("%d %d %d %d", &origem, &destino, &capacidade, &fluxo);
		int novo_i = procura(origem);
		int novo_j = procura(destino);
		if (find_arc(novo_i,novo_j,g) == NULL)
			insert_new_arc(novo_i,novo_j,capacidade,fluxo,g);
		r--;
	}
	return g;
}

BOOL consistencia(int start, int end) {
	for (int i=1; i<=cont_nos; i++){
		for (int j=1; j<=cont_nos; j++) {
			//printf("fluxos_matriz[%d][%d]=%d\n", i, j, fluxos_matriz[i][j]);
			fluxos_matriz[0][j] += fluxos_matriz[i][j];
			fluxos_matriz[i][0] += fluxos_matriz[i][j];
		}
	}

	if ( fluxos_matriz[start][0] != -fluxos_matriz[end][0] ||
		fluxos_matriz[0][end] != -fluxos_matriz[0][start]){
		//printf("0|%d = %d e 0|%d = %d\n", start, fluxos_matriz[0][start], end, fluxos_matriz[0][end]);
		printf("Inconsistente.\n");
		return FALSE;
	}
	for (int i=3; i<=cont_nos; i++){
		//printf("0|%d = %d e %d|0 = %d\n", i, fluxos_matriz[0][i], i, fluxos_matriz[i][0]);
		if (fluxos_matriz[0][i] != 0 || fluxos_matriz[i][0] != 0) {
			printf("Inconsistente.\n");
			return FALSE;
		}
	}

	return TRUE;
}

int atualiza_grafo(int start, int end, int pai[]) {
  int c_min = INT_MAX;
  int t = end;

  while (pai[t] != -1) {
  	ARCO *arc = find_arc(pai[t],t,gf);
  	
  	if (arc && c_min > VALOR1_ARCO(arc))
  		c_min = VALOR1_ARCO(arc);

  	t = pai[t];
  }

  t = end;
  int s = start;

  while (t != s){
    int p = pai[t];
    //printf("%d -> %d\n", p, t);
    ARCO* arc = find_arc(p,t,gf);
    ARCO* reverse_arc = find_arc(t,p,gf);
	int cf_p_t;
	int cf_t_p;

	cf_p_t = VALOR1_ARCO(arc) - c_min;

	if (reverse_arc) {
		cf_t_p = VALOR1_ARCO(reverse_arc) + c_min;
		remove_arc(reverse_arc,t,gf);
		insert_new_arc(t,p,cf_t_p,1,gf);
	}
	remove_arc(arc,p,gf);
	if (cf_p_t > 0) 
		insert_new_arc(p,t,cf_p_t,1,gf);
	
    t = p;
  }
  return c_min;
}

int bfs(int start, int end) {
	QUEUE* qq = mk_empty_queue(cont_nos+1);
	int v,w;
	int pai[cont_nos+1];
	ARCO* cur_adj;

	for(int i=1; i<=cont_nos+1; i++) {
		visitados[i] = FALSE;
		pai[i] = 0;
	}

	pai[start] = -1;
	visitados[start] = TRUE;
	enqueue(start,qq);
	while ( !queue_is_empty(qq) ) {
		v = dequeue(qq);
 
    	if (v == end) break;

		cur_adj = ADJS_NO(v,gf);
		while (cur_adj) {
			w = EXTREMO_FINAL(cur_adj);

			if ( visitados[w] == FALSE && VALOR1_ARCO(cur_adj) > 0) {
        		//printf("%d -> %d\n", v, w);
				visitados[w] = TRUE;
				enqueue(w,qq);
				pai[w] = v;
			}
			
			cur_adj = PROX_ADJ(cur_adj);
		}
	}
	free_queue(qq);
	
	if (visitados[end] == FALSE)	
		return 0;

	return atualiza_grafo(start, end, pai);
}

void construir_gf(GRAFO* g, int elementos, int start, int end) {
	QUEUE* qqq = mk_empty_queue(cont_nos);
	gf = new_graph(cont_nos);

	for (int i=1; i<=cont_nos; i++) {
		visitados[i] = FALSE;
		for (int j=1; j<=cont_nos; j++) {
			if (i == j)
				continue;

			insert_new_arc(i,j,0,1,gf);
			insert_new_arc(j,i,0,1,gf);
		}
	}

	visitados[start] = TRUE;
	enqueue(start,qqq);
	while (!queue_is_empty(qqq)) {
		int v = dequeue(qqq);
		ARCO* cur_adj = ADJS_NO(v,g);
		while (cur_adj) {
			int w = EXTREMO_FINAL(cur_adj);
			ARCO* arc_gf = find_arc(v,w,gf);
			
			int cf_v_w = VALOR1_ARCO(cur_adj) - VALOR2_ARCO(cur_adj);
			VALOR1_ARCO(arc_gf) += cf_v_w;

			int cf_w_v;
			ARCO* reverse_arc = find_arc(w,v,g);
			if (!reverse_arc)
				cf_w_v = VALOR2_ARCO(cur_adj);
			else
				cf_w_v = VALOR1_ARCO(reverse_arc) + VALOR2_ARCO(cur_adj);
			arc_gf = find_arc(w,v,gf);
			VALOR1_ARCO(arc_gf) += cf_w_v;


			if (visitados[w]==FALSE) {
				visitados[w] = TRUE;
				enqueue(w,qqq);
			}

			cur_adj = PROX_ADJ(cur_adj);
		}
	}
	free_queue(qqq);

	return ;
}

void analisa(GRAFO* g, int start, int end, int elementos) {
	QUEUE* q = mk_empty_queue(cont_nos);
	fluxos_matriz = (int **) malloc((cont_nos+1) * sizeof(int*));

	for (int i=0; i<=cont_nos; i++) {
		visitados[i] = FALSE;
		fluxos_matriz[i] = (int *) malloc((cont_nos+1) * sizeof(int));
		for (int j=0; j<=cont_nos; j++) {
			fluxos_matriz[i][j] = 0; 
		}
	}

	visitados[start] = TRUE;
	enqueue(start,q);
	while (!queue_is_empty(q)) {
		int v = dequeue(q);
		ARCO* cur_adj = ADJS_NO(v,g);
		while (cur_adj) {
			int w = EXTREMO_FINAL(cur_adj);

			if (VALOR2_ARCO(cur_adj) > VALOR1_ARCO(cur_adj)){
				printf("Inconsistente.\n");
				return ;
			}

			if (visitados[w] == FALSE) {
				visitados[w] = TRUE;
				enqueue(w,q);
			}

			//printf("%d -> %d = %d\n",v,w, VALOR2_ARCO(cur_adj));
			
			fluxos_matriz[v][w] += VALOR2_ARCO(cur_adj);
			fluxos_matriz[w][v] += -VALOR2_ARCO(cur_adj); 

			cur_adj = PROX_ADJ(cur_adj);
		}
	}
	free_queue(q);
	
	if ( consistencia(start, end) == FALSE ) return ;
	printf("Consistente. ");
	if ( fluxos_matriz[start][0] >= elementos ) {
		printf("Grupo evacuado!\n");
		return ;
	}
	
	construir_gf(g, elementos, start, end);

	int fluxo_max=fluxos_matriz[start][0];
	int c;

	while ( (c = bfs(start,end)) ) {
		//printf("\t%d\n", c);
		fluxo_max += c;
	}

	if ( fluxo_max < elementos )
		printf("Incompleto: %d/%d. Alerta, resgate impossivel!\n", fluxos_matriz[start][0], fluxo_max);
	else
		printf("Incompleto: %d/%d. Resgate possivel!\n", fluxos_matriz[start][0], elementos);
	destroy_graph(gf);
}

int main() {
	int elementos, montanha, abrigo, n_veiculos;
	GRAFO* g;

	scanf("%d %d %d %d", &elementos, &montanha, &abrigo, &n_veiculos);
	nos[1] = montanha;
	nos[2] = abrigo;
	g = ler_construir_grafo(n_veiculos);

	analisa(g, 1, 2, elementos);

	destroy_graph(g);
	return 0;
}