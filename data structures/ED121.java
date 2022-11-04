import java.lang.*;
import java.io.*;
import java.util.*;

class ED121
{
    public static void main(String args[]) throws IOException
    {
	BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
	StringTokenizer tokenizer = new StringTokenizer(reader.readLine());
	
	int n = Integer.parseInt(tokenizer.nextToken());
	System.out.println(n);
	
	for(int i=0; i<n; i++)
	{
	    tokenizer = new StringTokenizer(reader.readLine(), "\n");
	    String frase = tokenizer.nextToken();
	    System.out.println(isPal(frase) ? "sim" : "nao");
	}
    }

    static boolean isPal(String str)
    {
	str = clean(str);
	for(int i=0, j=str.length()-1; i<j; i++, j--)
	{
	    if(str.charAt(i) != str.charAt(j))
	    {
		return false;
	    }
	}

	return true;
    }

    static String clean(String str)
    {
	String newStr = "";
	for(int i=0; i<str.length(); i++)
	{
	    char c = str.charAt(i);
	    if(Character.isLetter(c))
	    {
		newStr += Character.toLowerCase(c);
	    }
	}

	return newStr;
    }
}
