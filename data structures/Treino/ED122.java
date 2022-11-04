import java.lang.*;
import java.util.*;
import java.io.*;

class ED122 {
	public static void main(String[] args){

		Scanner input = new Scanner(System.in);

		int n = input.nextInt();
		
		double x = Math.floor(Math.sqrt(4*n+1));
		double y = n - Math.floor((int)x^2/4);



		System.out.println("(" + x + "," + y + ")");
	}
}