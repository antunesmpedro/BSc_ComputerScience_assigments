//import java.io.*;
import java.io.File;
import java.util.Scanner;

// Este programa ilustra o uso da classe Scanner
// Lê o input a partir de um ficheiro aula2_1.txt
class ScannerTest 
{
    public static void main(String[] args) throws Exception // ????
    {
	
	// inp será o canal de leitura
	Scanner inp = new Scanner(new File("aula2_1.txt"));
	
	System.out.println("Processamento do input vindo de aula2_1.txt!");
	System.out.println("Leitura de int, long, double; ignora mudancas de linha");
      
	int i    = inp.nextInt();
	long l   = inp.nextLong();
	
	double d = inp.nextDouble();
	String s = inp.nextLine(); // ignora o resto
	
	
      System.out.println(i + " " + l + " " + d + " " + s);
      
      System.out.println("Escreve tudo numa string:");
      
      // Preparar para ler uma linha por inteiro
      String line= inp.nextLine(); 
      
      System.out.println(line);
      
      // Preparar para ler por palavras (tokens) da linha anterior
      System.out.println("Cada palavra:");
      
      Scanner newIn = new Scanner(line);

      while (newIn.hasNext()) {
	  System.out.println(newIn.next());
      }
      
      // Retorna à leitura normal do canal inp...
      System.out.println("Leitura de inteiros...");
      while (inp.hasNext()) 
	  System.out.println(inp.nextInt() + " " +inp.nextInt());
      
    }
}
