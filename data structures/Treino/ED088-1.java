import java.util.Scanner;

class Game {
	final char DEAD = '.';
	final char ALIVE = 'O';
	private int rows, cols;
	private char m[][];

	Game(int r, int c) {
		rows = r;
		cols = c;
		m = new char[r][c];
	}

	public void read(Scanner in) {
		for(int i = 0; i < rows; i++)
			m[i] = in.next().toCharArray();
	}

	public void write() {
		for(int i = 0; i < rows; i++){
			for(int j = 0; j < cols - 1; j++){
				System.out.print(m[i][j]);
			}
			System.out.println(m[i][cols - 1]);
		}
	}

	public int countAlive (int y, int x) {
		int count = 0;
		/*for(int i = -1; i < 2; i++) {
			if(y+i < 0 || y+i >= rows)
				continue;
			for(int j = -1; j < 2; j++){
				if(x+j < 0 || x+j >= cols) 
					continue;
				if((i != 0 || j != 0) && m[y+i][x+j] == ALIVE)
					count++;
			} 
		}*/

		for(int i=y-1; i<=y+1; i++)
		{
			for(int j=x-1; j<=x+1; j++)
			{
				if( (i>=0 && i<rows) && (j>=0 && j<cols) && m[i][j] == ALIVE) )
					count++; 			
			}
		}
		
		if(m[y][x] == ALIVE)
			count--;
	
		return count;
	}

	public void iterate() {
		char temp_matrix[][] = new char[rows][cols];

		for(int i = 0; i < rows; i++){
			for(int j = 0; j < cols; j++){
				int counter = countAlive(i,j)
				/*
				if(counter < 2 && m[i][j] == ALIVE)
					temp_matrix[i][j] = DEAD;
				else if(counter >= 4 && m[i][j] == ALIVE)
					temp_matrix[i][j] = DEAD;
				else if(counter == 3 && m[i][j] == DEAD)
					temp_matrix[i][j] = ALIVE;
				else
					temp_matrix[i][j] = m[i][j];
				*/			
			
				if(m[i][j] == ALIVE)
				{
					if(counter > 2 && count < 4)
						temp_matrix[i][j] = ALIVE;
					else
						temp_matrix[i][j] = DEAD;
				}
				else if(counter == 3)
				{
					temp_matrix == ALIVE;
				}
				else
				{
					temp_matrix = m[i][j];
				}
			}
		}
			
	
		for(int i = 0; i < rows; i++){
			/*for(int j = 0; j < cols; j++){
				m[i][j] = temp_matrix[i][j];
			}*/
			m[i] = temp_matrix[i].clone();
		}
	}
}

public class ED088 {
	public static void main(String[] args) {
		Scanner in = new Scanner(System.in);

		int rows = in.nextInt();
		int cols = in.nextInt();
		int n    = in.nextInt();

		Game g = new Game(rows, cols);

		g.read(in);
		for(int i = 0; i < n; i++)
			g.iterate();
		g.write();
	}
}
