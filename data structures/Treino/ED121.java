import java.util.*;
import java.lang.*;
import java.io.*;

class ED121 {
	public static void main(String args[]){

		Scanner in = new Scanner(System.in);

		int n = in.nextInt();
		System.out.println(n);

		in.nextLine(); // ignorar \n

		for(int i = 0; i < n; i++){
			String frase = in.nextLine();
			System.out.println(isPal(frase) ? "sim" : "nao");
		}
	}

	static boolean isPal(String str){
		str = clean(str);
		for(int i = 0, j = str.length() - 1; i < j; j--, i++){
			if(str.charAt(i) != str.charAt(j))
				return false;
		}
		return true;
	}

	static String clean(String str){
		String newStr = "";
		for(int i = 0; i < str.length(); i++){
			if(Character.isLetter(str.charAt(i)))
				newStr += Character.toLowerCase(str.charAt(i));
		}
		return newStr;
	} 
}