
import java.io.*;
import java.util.*;

// Programa para ilustrar o uso de output formatado

class FormatTest {

   public static void main(String args[]) {

      String discip= "Estruturas de Dados";
      String aluno = "Manuel";
      long cod = 80725;

      double nota = 12.5;

      System.out.printf("Resultados de %s\n", discip); 
      System.out.printf("Codigo %d, aluno %s, nota %f \n\n", cod, aluno, nota); 
      System.out.printf("Codigo %d, aluno %s, nota %f \n\n", 80726, "Maria", 13.2); 

      double sam = 24.56789;

      // 8.2f significa 8 caracteres incluindo o ponto, com dois decimais
      // bbb24.57 onde b é espaço
      System.out.printf("2 decimais:%8.2f \n", sam);

      System.out.printf("\nNotacao Cientifica:   %e \n", sam);//vírgula flutuante
      //arg pode ser codigo ASCII
      System.out.printf("\nExistem dois tipos de A's: %c %c \n\n", 'a', 65);

      int num;
   }
}
