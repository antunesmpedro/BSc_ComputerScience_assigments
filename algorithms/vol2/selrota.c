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

#define MAXVERTS 50000
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

/////////////////////////////
//       SELEC ROTA        //
/////////////////////////////

GRAFO* ler_construir_grafo() {
  GRAFO* g;
  int n_nos, n_ramos, i, start, end, ha_problemas;

  scanf("%d %d", &n_nos, &n_ramos);
  g = new_graph(n_nos);
  for (i=0; i< n_ramos; i++) {
    scanf("%d %d %d", &start, &end, &ha_problemas);
    insert_new_arc(start, end, ha_problemas, g);
  }

  return g;
}

int detecta_localizacoes(int origem_grupo, int destino_grupo, int bussula, int start, int end) {
  if (bussula == 2)
    return 2;
  else if (bussula == 1) {
    if (end == destino_grupo)
      return 2;
    else
      return 1;
  }
  else {
    if (start == origem_grupo){
      if (end == destino_grupo)
        return 2;
      else
        return 1;
    }
    else
      return 0;
  }
}

int main() {
  GRAFO* g;
  ARCO* arc;
  int n_elementos_grupo, local_origem, local_destino, n_nos_rota, i, j;
  int start, end, lugares, gps = 0, new_gps, n_rotas;
  int rota_probs[100+1], max_probs=MAXVERTS, rota_alvo=0;
  int sem_lugares, problemas;

  scanf("%d %d %d", &n_elementos_grupo, &local_origem, &local_destino);
  g = ler_construir_grafo();
  scanf("%d", &n_rotas);
  for (i=1; i<=n_rotas; i++) 
    rota_probs[i] = 0;

  for (i=1; i<=n_rotas; i++) {
    gps = 0;
    sem_lugares = 0;
    problemas = 0;
    scanf("%d %d", &n_nos_rota, &start);
    for (j=1; j< n_nos_rota; j++) {
      scanf("%d %d", &lugares, &end);
      arc = find_arc(start, end, g);
      new_gps = detecta_localizacoes(local_origem, local_destino, gps, start, end);
      switch (new_gps) {
        case 0: 
          rota_probs[i] += VALOR_ARCO(arc);
          problemas += VALOR_ARCO(arc);
          break;
        case 1: 
          if(sem_lugares == 0){
            if (lugares >= n_elementos_grupo){
              rota_probs[i] += VALOR_ARCO(arc);
              problemas += VALOR_ARCO(arc);
            }
            else{
              rota_probs[i] = -1;
              sem_lugares = 1;
            }
          }
          break;
        case 2:
          if (sem_lugares == 0 && gps != 2) {
            if (lugares >= n_elementos_grupo){
              rota_probs[i] += VALOR_ARCO(arc);
              problemas += VALOR_ARCO(arc);
              if(problemas < max_probs) {
                rota_alvo = i;
                max_probs = problemas;
              }
            }
            else{
              rota_probs[i] = -1;
              sem_lugares = 1;
            }
          }
          break;
      }
      start = end;
      gps = new_gps;
      //printf("rota > %d | gps > %d | new_gps > %d | lugares > %d\n", i, gps, new_gps, sem_lugares);
    }
    if( new_gps != 2 )
      rota_probs[i] = -1;
  }

  //for(i=1; i<=n_rotas; i++)
    //printf("falhas  %d > %d\n",i, rota_probs[i]);

  if(rota_alvo == 0)
    printf("Impossivel\n");
  else
    printf("Reserva na rota %d: %d\n", rota_alvo, max_probs);

  return 0;
}