import java.io.*;
import java.util.*;

class ReadNumbers {
    public static void main(String[] args) {

	int soma=0, max=Integer.MIN_VALUE, min=Integer.MAX_VALUE;
        int howmany;
        Scanner stdin = new Scanner(System.in);

        // Ler a quantidade de numeros que se seguem
        howmany = stdin.nextInt();

	int v[] = new int[howmany];

        // Ler os numeros a partir do stdin
        for (int i=0; i<howmany; i++){
            v[i] = stdin.nextInt();
	    soma+=v[i];
	    if(v[i]>max)
		max=v[i];
	    if(v[i]<min)
		min=v[i];
	}

        // Escrever os numeros no stdout
        for (int i=0; i<howmany; i++)
            System.out.println("v[" + i + "] = " + v[i]);
	
	System.out.printf("%d\n%.2f\n%d\n",soma,soma/(float)howmany,max-min);
	

    }
}
