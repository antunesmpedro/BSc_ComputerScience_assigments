import java.lang.*;
import java.util.*;
import java.io.*;

class ED120
{
    public static void main(String args[])
    {
	Scanner in = new Scanner(System.in);
	int n = in.nextInt();

	int chars = 1;
	int dots = n-chars; 
	
	for(int i=0; i<n; i++)
	{
	    for(int j=0; j<(dots/2); j++)
	    {
		System.out.print(".");
	    }

	    for(int j=0; j<chars; j++)
	    {
		System.out.print("#");
	    }

	    for(int j=0; j<(dots/2); j++)
	    {
		System.out.print(".");
	    }

	    System.out.println("");
	    
	    chars = i >= (n/2) ? chars-2 : chars+2;
	    dots = n-chars;
	}
    }
}
