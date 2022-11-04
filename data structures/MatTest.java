import java.io.*;
import java.util.*;

// classe que define uma matriz
class Matriz {
    private int A[][]; // matriz
    private int NL;    // num. linhas
    private int NC;    // num. colunas

    // método construtor - inicializa um objecto matriz
    Matriz(int n, int m) {
	A= new int[n][m];
        NL= n;
        NC= m;
    }

    // leitura dos NLxNC elementos da matriz
    public void leMatriz(Scanner in) {
	
	for (int i=0; i<NL; i++)
	    for (int j=0; j<NC; j++)
		A[i][j]= in.nextInt();

    }
    public int maiorElemento() {
	int maior; 

	maior= A[0][0]; // maior começa por ser este valor

        for (int lin= 0; lin < NL; lin++) 
	    for (int col= 0; col < NC; col++) {
		if (maior < A[lin][col])
		    maior= A[lin][col];
	    }
	return maior;
    }

    public int linhaMaiorSoma() {
	int soma,maiorsoma=Integer.MIN_VALUE,l=0;

	for(int i=0; i<NL; i++){
	    soma=0;
	    for(int j=0; j<NC; j++){
		soma+=A[i][j];
	    }
	    if(soma>maiorsoma){
		maiorsoma=soma;
		l=i;
	    }
	}

	return l;
    }

    public static Matriz soma(Matriz m1, Matriz m2)
    {
	Matriz mSoma = new Matriz(m1.NL, m1.NC);

	for(int i=0; i<m1.NL; i++)
	{
	    for(int j=0; j<m1.NC; j++)
	    {
		mSoma.A[i][j] = m1.A[i][j] + m2.A[i][j];
	    }
	}
	
	return mSoma;
    }

    public static Matriz multiplicacao(Matriz m1, Matriz m2){

        if(m1.NC != m2.NL)
	    return null;

	Matriz mMul = new Matriz(m1.NL, m2.NC);

	for(int i=0; i<m1.NL; i++)
	{
	    for(int j=0; j<m2.NC; j++)
	    {
		for(int k=0; k<m1.NC; k++)
		{
		    mMul.A[i][j] += m1.A[i][k] * m2.A[k][j];
		}
	    }
	}
	
	return mMul;
    }

    public static void print(Matriz m1)
    {
	for(int i=0; i<m1.NL; i++)
	{
	    for(int j=0; j<m1.NC; j++)
	    {
		System.out.printf("%d ", m1.A[i][j]);
	    }
	    System.out.print("\n");
	}
    }
}


// classe principal do programa
class MatTest {

    public static void main(String args[]) {

	// canal de leitura
	Scanner stdin = new Scanner(System.in); 
	Matriz a; // objecto representando uma matriz

	// ler o num. linhas e num. colunas
	int nl= stdin.nextInt();
        int nc= stdin.nextInt();

        // cria o objecto matriz, coma a dimensão lida
        a= new Matriz(nl,nc);

	// ler os valores da matriz
	a.leMatriz(stdin);
	
	Matriz b = new Matriz(stdin.nextInt(), stdin.nextInt());
	b.leMatriz(stdin);
	
	//calcula o maior elemento da matriz e escreve-o
	System.out.printf("Maior valor da matriz: %d\n", a.maiorElemento());

	System.out.printf("Linha com maior soma: %d\n", a.linhaMaiorSoma());

	// 2xA
	Matriz.print(Matriz.multiplicacao(a,b));
    }
}
