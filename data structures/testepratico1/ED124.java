import java.util.Scanner;

class Game {
    
    private int rows, cols;  // Numero de linhas e colunas
    private  int  m[][];      // Matriz para representar o estado do jogo
    
    Game(int r, int c) {
	rows = r;
	cols = c;
	m = new int[r][c];
    }

    public void read (Scanner in) {
	for (int i=0; i<rows; i++)
	    for(int j=0; j<cols; j++)
		m[i][j]=in.nextInt();
    }
    
    public void count1() {

	int conta1=0;
	for (int i=0; i<rows; i++)
	    for(int j=0; j<cols; j++)
		if(m[i][j]%2==1)
		    conta1++;
	System.out.println(conta1);
    }
    
    public void count2() {
	int tamanho=0, tamanhomax=0, isave=0, jsave=0, soma=0;
	for(int i=0; i<rows; i++)
	    for(int j=0; j<cols; j++)
		for(tamanho=1; ; tamanho++) {
		    if (i+tamanho>rows || j+tamanho>cols)
			break;
		    else if  (checksquare(i,j,tamanho)) {

			if(tamanho > tamanhomax) {
				tamanhomax = tamanho;
				isave=i;
				jsave=j;

			    }
			}
		}
	
	for(int i=isave; i<(isave+tamanhomax); i++)
	    for(int j=jsave; j<(jsave+tamanhomax); j++)
		soma= m[i][j] + soma;

	System.out.println(tamanhomax + " " + soma);
	
    }
    private boolean checksquare(int x, int y, int tam)  {
	
	for(int a=x; a<y+tam; a++)
	    for (int b=y; b<x+tam; b++)
		if (m[a][b]%2!=1) return false;
	return true;
    }
    
    
}

public class ED124 {
    public static void main(String[] args) {
	
	Scanner in =new Scanner(System.in);
	int f = in.nextInt();
	int rows = in.nextInt();
	int cols= in.nextInt();

	Game g = new Game(rows, cols);
	g.read(in);

	if (f==1)
	    g.count1();
	else if (f==2)
	    g.count2();
    }
}
