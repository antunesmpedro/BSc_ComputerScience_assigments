import java.io.*;
import java.lang.*;
import java.util.*;

class ED004 {
	public static void main(String[] args){

		Scanner input = new Scanner(System.in);
		int n = input.nextInt();
		char v[][] = new char[n][n];

		int incompleto = 0;
		char k;

		input.nextLine();

		for(int i = 0; i < n; i++){
			String frase = input.nextLine(); 
			for(int j = 0; j < n; j++){
				v[i][j] = frase.charAt(j);
				if(frase.charAt(j) == '.')
					incompleto++;
			}
		}

		if(xwins(v, n))
			System.out.println("Ganhou o X");
		else if(owins(v, n))
			System.out.println("Ganhou o O");
		else if(incompleto == n*n)
			System.out.println("Jogo incompleto");
		else
			System.out.println("Empate");
	}

		

	static boolean xwins(char v[][], int n){

		int pointsdiagonal1 = 0;
		int pointsdiagonal2 = 0;

		for(int i = 0; i < n; i++){
			int pointshorizontal = 0;
			int pointsvertical = 0;
			for(int j = 0; j < n; j++){
				if(v[i][j] == 'X')
					pointshorizontal++;
				if(v[j][i] == 'X')
					pointsvertical++;
				if(pointshorizontal == n || pointsvertical == n)
					return true;
			}
			if(v[i][i] == 'X')
				pointsdiagonal1++;
			if(v[n-i-1][i] == 'X')
				pointsdiagonal2++;
		}

	if(pointsdiagonal1 == n || pointsdiagonal2 == n)
		return true;

	return false;
}

	static boolean owins(char v[][], int n){

		int pointsdiagonal1 = 0;
		int pointsdiagonal2 = 0;

		for(int i = 0; i < n; i++){
			int pointshorizontal = 0;
			int pointsvertical = 0;
			for(int j = 0; j < n; j++){
				if(v[i][j] == 'O')
					pointshorizontal++;
				if(v[j][i] == 'O')
					pointsvertical++;
				if(pointshorizontal == n || pointsvertical == n)
					return true;
			}
			if(v[i][i] == 'O')
				pointsdiagonal1++;
			if(v[n-i-1][i] == 'O')
				pointsdiagonal2++;
		}

	if(pointsdiagonal1 == n || pointsdiagonal2 == n)
		return true;
	return false;
	}
}