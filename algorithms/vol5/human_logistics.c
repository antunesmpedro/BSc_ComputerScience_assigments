#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAX 100000

/*-----------------------------------------------------------------------*\
|  Exemplo de implementacao de fila de prioridade (por heap de máximo)    |
|                                                                         |
|   A.P.Tomás, CC2001 (material para prova pratica), DCC-FCUP, 2017       |
|   Last modified: 2017.12.18                                             |
\*-----------------------------------------------------------------------*/

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
int heap_isEmptyMax(HEAPMAX *q);  // retirna 1 ou 0


void write_heapMax(HEAPMAX *q);
void destroy_heapMax(HEAPMAX *q);


//----------------- definição das funções e macros ---------------------

#define POSINVALIDA 0

#define LEFT(i) (2*(i))
#define RIGHT(i) (2*(i)+1)
#define PARENT(i) ((i)/2)

static void heapifyMax(int i,HEAPMAX *q);
static void swapMax(int i,int j,HEAPMAX *q);
static int compareMax(int i, int j, HEAPMAX *q);
static int pos_validaMax(int i,HEAPMAX *q);

static int compareMax(int i, int j, HEAPMAX *q){
  if (q -> a[i].vertkey < q -> a[j].vertkey)
    return -1;
  if (q -> a[i].vertkey == q -> a[j].vertkey){
  	if (q -> a[i].vert < q -> a[j].vert)
  		return 1;
    else
    	return -1;
  }
  return 1;
}


static int pos_validaMax(int i, HEAPMAX *q) {
  return (i >= 1 && i <= q -> size);
}

int extractMax(HEAPMAX *q) {
  int vertv = q -> a[1].vert;
  swapMax(1,q->size,q);
  q -> pos_a[vertv] = POSINVALIDA;  // assinala vertv como removido
  q -> size--;
  heapifyMax(1,q);
  return vertv;
}

void increaseKey(int vertv, int newkey, HEAPMAX *q){
  int i = q -> pos_a[vertv];
  q -> a[i].vertkey = newkey;

  while(i > 1 && compareMax(i,PARENT(i),q) > 0){
    swapMax(i,PARENT(i),q);
    i = PARENT(i);
  }
}


static void heapifyMax(int i,HEAPMAX *q) {
  // para heap de maximo
  int l, r, largest;
  l = LEFT(i);
  if (l > q -> size) l = i;
  r = RIGHT(i);
  if (r > q -> size) r = i;
  
  largest = i;
  if (compareMax(l,largest,q) > 0) 
    largest = l;
  if (compareMax(r,largest,q) > 0) 
    largest = r;
  
  if (i != largest) {
    swapMax(i,largest,q);
    heapifyMax(largest,q);
  }
}

static void swapMax(int i,int j,HEAPMAX *q){
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
    heapifyMax(i,q);
  return q;
}


void insertMax(int vertv, int key, HEAPMAX *q)
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

int heap_isEmptyMax(HEAPMAX *q){
  if (q -> size == 0) return 1;
  return 0;
}


// --------- auxiliar para ver conteudo  ---------------------
void write_heapMax(HEAPMAX *q){
  int i;

  printf("Max size: %d\n", q -> sizeMax);
  printf("Current size: %d\n", q -> size);
  
  printf("(Vert,Key)\n---------\n");
  for(i=1; i <= q -> size; i++)
    printf("(%d,%d)\n",q->a[i].vert,q->a[i].vertkey);

  printf("-------\n(Vert,PosVert)\n---------\n");

  for(i=1; i <= q -> sizeMax; i++)
    if (pos_validaMax(q -> pos_a[i],q))
      printf("(%d,%d)\n",i,q->pos_a[i]);
}


void destroy_heapMax(HEAPMAX *q){
  if (q != NULL) {
    free(q -> a);
    free(q -> pos_a);
    free(q);
  }
}
//////////////////////////////////////////////////
//////////////////////////////////////////////////

int main() {
	int datas[MAX+1];
	int lucro[MAX+1];
	int res[MAX+1];
	int visitados[MAX+1];

	int tarefas;
	scanf("%d", &tarefas);
	
	//inicializacao
	lucro[0] = -1;
	datas[0] = -1;
	res[0] = 0;
	for(int i=1; i<=tarefas; i++) {
		res[i] = i;
		visitados[i] = 0;
		scanf("%d %d", &datas[i], &lucro[i]);
	}

	HEAPMAX* q_max = build_heap_max(lucro, tarefas);

	for(int i=1; i<=tarefas; i++){
		int tarefa_max_lucro = extractMax(q_max);
		int k = datas[tarefa_max_lucro];

		// alocar a tarefa escolhida da heap na data possivel
		while (res[k] != k){
			res[k] = res[res[k]];  // atualizar valor do slot
			k = res[k];
		}
		// slot disponivel
		if (k != 0){
			visitados[tarefa_max_lucro] = 1;
			//printf("%d <- %d\n", res[k], res[k-1]);
			res[k] = res[k-1];
			res[datas[tarefa_max_lucro]] = res[k-1];
		}
		else
			res[datas[tarefa_max_lucro]] = 0;    // tarefa nao selecionada
		/*
		
		//COMPLEXIDADE ELEVADA

		for(int j = datas[tarefa_max_lucro]; j>=1; j--){
			if (res[j] == 0){
				res[j] = tarefa_max_lucro;
				visitados[tarefa_max_lucro] = 1;
				//printf("%d -> %d\n", j, tarefa_max_lucro);	
				break;
			}
		}
		*/
	}
	//printf("\n");
	for(int i=1; i<=tarefas; i++){
		if(visitados[i] == 1)
			printf("%d\n", i);
	}
	
	return 0;
}