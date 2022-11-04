import java.util.Scanner;


class Game {
    private int rows, cols;  // Numero de linhas e colunas
    private char m[][];      // Matriz para representar o estado do jogo
    
    // Construtor: inicializa as variaveis tendo em conta a dimensao dada
    Game(int r, int c) {
	rows = r;
	cols = c;
       	m = new char[r][c];
    }
    
    // Metodo para ler o estado inicial para a matriz m[][]
    void read(Scanner in) {
	for (int i=0; i<rows; i++)
	    m[i]= in.next().toCharArray();
    }
    
    public void Count1() {
	
	int flag1=0;
	for (int i=0; i<rows; i++)
	    for (int j=0; j<cols; j++) {
		if (m[i][j]=='#')
		    flag1++;
	    }
	System.out.println(flag1);
    }
    public void Count2() {
	int tam=0;
	int cont=0;
	int max=0;
	int num=0;

	for (int i=0;i<rows;i++) {
	    for (int j=0;j<cols;j++) {  
		cont=0;
		while(j<cols && m[i][j]=='#') {
		    j++;
		    cont++;  }
		if(cont>max) {
		    max=cont;
		    num=1;  }
		else if (cont==max)num++;
	    }
	}
	for (int j=0;j<cols;j++){
	    for (int i=0;i<rows;i++){  
		cont=0;
		while(i<rows && m[i][j]=='#'){
		    i++;
		    cont++;
		}
		if(cont>max){
		    max=cont;
		    num=1;
		}
		else if (cont==max)num++;
	    }
	}
	System.out.println(max + " " + num);
    }
}
// Classe principal com o main()
public class ED123 {
    public static void main(String[] args) {
		    
	    
	Scanner in = new Scanner(System.in);
	
	// Ler linhas, colunas e flags
	
	int nflag = in.nextInt();
	int rows = in.nextInt();
	int cols = in.nextInt();
	
	
	// Criar objecto para conter o jogo e ler estado inicial
	Game g = new Game(rows, cols);
	g.read(in);
	
	if (nflag == 1)
	    g.Count1();
	else if (nflag == 2)
	    g.Count2();
    }
}

