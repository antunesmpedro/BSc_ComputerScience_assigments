import java.util.Scanner;

class Game {
    
    private int rows, cols, flag;  // Numero de linhas e colunas
    private  char m[][];      // Matriz para representar o estado do jogo
    
    Game(int r, int c) {
	rows = r;
	cols = c;
	m = new char[r][c];
    }
    
    public void read(Scanner hp) {
	for (int i=0; i<rows; i++)
	    m[i] = hp.next().toCharArray();
    }
    public void countCard() {
	int flag1=0;
	for (int i=0; i<rows; i++)
	    for (int j=0; j<cols; j++) {
		if (m[i][j] == '#') {
		    flag1++;
		    System.out.println(flag1);
		}
	    }
    }
    public void countLinColCard() {
	int anterior=0;
	int maxsize=0;
	int maxsizecount=0; 
	
	int countsize=0;
	
	for (int i=0; i<rows; i++)
	    for (int j=0; j<cols; j++) {
		if (m[j] == '#' && anterior == 1) {
		    countsize++;
		    if (countsize = maxsize) {
			maxsizecount++; }
		    else if( countsize > maxsize) {
			maxsize=countsize;
			maxsizecount=1; }
		}
		    
		else if (m[j] =='#' && anterior == 0)
		    countsize++;
		else if (m[j] != '#') {
		    countsize=0;
		    anterior=0;
		}
		    
	    }
	countsize=0;
	anterior=0;
	    
	    
	for (int i=0; i<cols; i++)
	    for (int j=0; j<rows; j++) {
		if (m[j] == '#' && anterior == 1) {
		    countsize++;
		    if (countsize = maxsize) {
			maxsizecount++; }
		    else if( countsize > maxsize) {
			maxsize=countsize;
			maxsizecount=1; }
		}
		    
		else if (m[j] =='#' && anterior == 0)
		    countsize++;
		else if (m[j] != '#') {
		    countsize=0;
		    anterior=0;
		}
	    }
	System.out.println(maxsize + maxsizecount);
    }
}


public class ED123 {
    public static void main(String[] args) {
	
	Scanner hp  = new Scanner (System.in);
	int f = hp.nextInt();
	int rows = hp.nextInt ();
	int cols = hp.nextInt ();


	
	Game g = new Game(rows, cols);
	g.read(hp);
	
	if (f == 1) {
	    g.countCard();    
	}
	else if (f == 2) {
	    g.countLinColCard();   

	}
    }

}
