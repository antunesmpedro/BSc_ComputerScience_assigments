import java.lang.*;
import java.util.Scanner;

class Soup{

	Soup(int rows, int cols){
		// rows = r;
		// cols = c; ?
		m = new char[rows][cols];
	}

	public void SoupReader(Scanner in){
		for(int i = 0; i < rows; i++)
			m[i] = in.next().toCharArray();

	}

	public void WordsReader(Scanner in, int n){
		char word[];
		for(int i = 0; i < n; i++)
			word[i] = in.next().toCharArray();
	}

	public void Finder(int k){
		int counter = 0;
		int pos_inicial, pos_final;
		for(int i = 0; i < rows; i++){
			for(int j = 0; j < cols; j++){
				if(m[i][j] == word[k].chatAt(counter))
				counter++;
			
				else counter = 0;
			// fazer 4 duplos ciclos diferentes para cada um percorrer os 4 sentidos diferentes; como guardar a posição inicial tho?
			}
		}	
		if(counter)
	}
}

public class ED015 {
	public static void main(String[] args){
		Scanner in = new Scanner(System.in);
		int rows = in.nextInt();
		int cols = in.nextInt();

		Sopa s = new Sopa(rows,cols);

	}
}