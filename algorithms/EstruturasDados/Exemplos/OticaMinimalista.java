/*------------------------------------------------------\
|       Otica Minimalista                               |
|  Exemplos disponiveis  -- Prova pratica  2017         |
|  A.P. Tomas (Dez 2017)                                |
\*-----------------------------------------------------*/

import java.lang.*;
import java.util.*;



//========================== Grafo (um peso)

class Arco {
    int no_final;
    int valor;
    
    Arco(int fim, int v){
	no_final = fim;
	valor = v;
    }

    int extremo_final() {
	return no_final;
    }

    int valor_arco() {
	return valor;
    }

    void novo_valor(int v) {   // novo metodo
	valor = v;
    }
}


class No {
    //int label;
    LinkedList<Arco> adjs;

    No() {
	adjs = new LinkedList<Arco>();
    }
}


class Grafo {
    No verts[];
    int nvs, narcos;
			
    public Grafo(int n) {
	nvs = n;
	narcos = 0;
	verts  = new No[n+1];
	for (int i = 0 ; i <= n ; i++)
	    verts[i] = new No();
        // para vertices numerados de 1 a n (posicao 0 nao vai ser usada)
    }
    
    public int num_vertices(){
	return nvs;
    }

    public int num_arcos(){
	return narcos;
    }

    public LinkedList<Arco> adjs_no(int i) {
	return verts[i].adjs;
    }
    
    public void insert_new_arc(int i, int j, int valor_ij){
	verts[i].adjs.addFirst(new Arco(j,valor_ij));
        narcos++;
    }

    public Arco find_arc(int i, int j){
	for (Arco adj: adjs_no(i))
	    if (adj.extremo_final() == j) return adj;
	return null;
    }
}


//========================== Heapmax 


class Qnode {
    int vert;
    int vertkey;
    
    Qnode(int v, int key) {
	vert = v;
	vertkey = key;
    }
}

class Heapmax {
    private static int posinvalida = 0;
    int sizeMax,size;
    
    Qnode[] a;
    int[] pos_a;

    Heapmax(int vec[], int n) {
	a = new Qnode[n + 1];
	pos_a = new int[n + 1];
	sizeMax = n;
	size = n;
	for (int i = 1; i <= n; i++) {
	    a[i] = new Qnode(i,vec[i]);
	    pos_a[i] = i;
	}

	for (int i = n/2; i >= 1; i--)
	    heapify(i);
    }

    boolean isEmpty() {
	if (size == 0) return true;
	return false;
    }


    int extractMax() {
	int vertv = a[1].vert;
	swap(1,size);
	pos_a[vertv] = posinvalida;  // assinala vertv como removido
	size--;
	heapify(1);
	return vertv;
    }

    void increaseKey(int vertv, int newkey) {
	int i = pos_a[vertv];
	a[i].vertkey = newkey;

	while (i > 1 && compare(i, parent(i)) > 0) { 
	    swap(i, parent(i));
	    i = parent(i);
	}
    }

    
    private int parent(int i){
	return i/2;
    }
    private int left(int i){
	return 2*i;
    }
    private int right(int i){
	return 2*i+1;
    }

    private int compare(int i, int j) {
	if (a[i].vertkey < a[j].vertkey)
	    return -1;
	if (a[i].vertkey == a[j].vertkey)
	    return 0;
	return 1;
    }

  
    private void heapify(int i) {
	int l, r, largest;

	l = left(i);
	if (l > size) l = i;

	r = right(i);
	if (r > size) r = i;

	largest = i;
	if (compare(l,largest) > 0)
	    largest = l;
	if (compare(r,largest) > 0)
	    largest = r;
	
	if (i != largest) {
	    swap(i, largest);
	    heapify(largest);
	}
	
    }

    private void swap(int i, int j) {
	Qnode aux;
	pos_a[a[i].vert] = j;
	pos_a[a[j].vert] = i;
	aux = a[i];
	a[i] = a[j];
	a[j] = aux;
    }
    
    private boolean pos_valida(int i) {
	return (i >= 1 && i <= size);
    }
}





//=======================  Resolve Otica Minimalista



class OticaMinimalista {
    public static final int infmin = -1;
    public static int custo;


    public static Grafo lerGrafo(Scanner stdin){
	int origem, fim, rendbruto;

	int nverts = stdin.nextInt();
	int nramos = stdin.nextInt();
	custo = stdin.nextInt();

	Grafo g = new Grafo(nverts);

	for(int i = 0; i < nramos; i++){
	    origem = stdin.nextInt();
	    fim = stdin.nextInt();
	    rendbruto = stdin.nextInt();
	    g.insert_new_arc(origem,fim,rendbruto);
	    g.insert_new_arc(fim,origem,rendbruto);
	}
	return g;
    }

    public static int resolve(Grafo g) {
	int nverts = g.num_vertices();
	int[] dist = new int[nverts + 1];
	Boolean [] inQueue = new Boolean[nverts + 1];

	for(int v = 1;v <= nverts; v++) {
	    dist[v] = infmin; 
	    inQueue[v] = true;
	}
	dist[1] = 0;

	int rendimento = 0;

	Heapmax q = new Heapmax(dist,nverts);

	while(!q.isEmpty()){
	    int v = q.extractMax();
	    inQueue[v] = false;

	    if (dist[v] == infmin) 
		return infmin;  

	    rendimento += dist[v];

	    LinkedList<Arco> adjs = g.adjs_no(v);
	    for(Arco a: adjs){
		int w = a.extremo_final();
		if (inQueue[w] && a.valor_arco() > dist[w]){
		    dist[w] = a.valor_arco();
		    q.increaseKey(w,dist[w]);
		}
	    }
	}
	return rendimento-custo*(nverts-1);
    }

    public static void main(String[] args){
	Scanner stdin = new Scanner(System.in);
	Grafo g = lerGrafo(stdin);

	int rendimento = resolve(g);

	if (rendimento == infmin)
	    System.out.println("impossivel");
	else 
	    System.out.println("rendimento optimo: " + rendimento);
    }
}
