import java.lang.*;
import java.util.*;
import java.io.*;

class ED004
{
    public static void main(String args[]) throws IOException
    {
	BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
	StringTokenizer tokenizer = new StringTokenizer(reader.readLine());

	int n = Integer.parseInt(tokenizer.nextToken());
	char tabuleiro[][] = new char[n][n];

	for(int i=0; i<n; i++)
	{
	    tokenizer = new StringTokenizer(reader.readLine());
	    tabuleiro[i] = tokenizer.nextToken().toCharArray();
	}

	boolean foundWinner = false;
	for(int i=0; i<n; i++)
	{
	    if(winLinhaColuna(tabuleiro, i, n))
	    {
		foundWinner = true;
		break;
	    }
	}

	// winner not found?
	if(!foundWinner)
	{
	    // last checks (diags and draw case)
	    if(!winDiags(tabuleiro, n) && !isDraw(tabuleiro, n))
	    {
		// false for every check, incomplete game
		System.out.println("Jogo incompleto");
	    }
	}
    }

    // check col and line of given index
    static boolean winLinhaColuna(char tabuleiro[][], int index, int n)
    {
	int linhaX=0, linhaO=0, colunaX=0, colunaO=0;

	for(int i=0; i<n; i++)
	{
	    // line
	    if(tabuleiro[index][i] == 'X')
		linhaX++;
	    else if(tabuleiro[index][i] == 'O')
		linhaO++;

	    // col
	    if(tabuleiro[i][index] == 'X')
		colunaX++;
	    else if(tabuleiro[i][index] == 'O')
		colunaO++;
	}

	return ( winner(n, linhaX, linhaO) || winner(n, colunaX, colunaO) );
    }

    // check both diags of game matrix
    static boolean winDiags(char tabuleiro[][], int n)
    {
	int pX=0, pO=0, sX=0, sO=0;

	for(int i=0; i<n; i++)
	{
	    //
	    if(tabuleiro[i][i] == 'X')
		pX++;
	    else if(tabuleiro[i][i] == 'O')
		pO++;
	    
	    // secondary
	    if(tabuleiro[n-1-i][i] == 'X')
		sX++;
	    else if(tabuleiro[n-1-i][i] == 'O')
		sO++;
	}

	return ( winner(n, pX, pO) || winner(n, sX, sO) );
    }

    // check draw
    static boolean isDraw(char tabuleiro[][], int n)
    {
	for(int i=0; i<n; i++)
	{
	    for(int j=0; j<n; j++)
	    {
		if(tabuleiro[i][j] == '.')
		    return false;
	    }
	}
	
	System.out.println("Empate");    
	return true;
    }						 
    
    // check if there is winner
    // print winner
    static boolean winner(int n, int x, int o)
    {
	if(x==n || o==n)
	{
	    System.out.println("Ganhou o " + ( x==n ? 'X' : 'O') );
	    return true;
	}

	return false;
    }
}
