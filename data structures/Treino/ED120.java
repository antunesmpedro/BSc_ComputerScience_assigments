import java.util.Scanner;
import java.io.*;

class ED120 {
	public static void main(String args[])
	{
		Scanner in = new Scanner(System.in);
		int n = in.nextInt();

		for(int i = 0; i <= n/2; i++)
		{
			for(int j = 0; j < n/2 - i; j++)
				System.out.print(".");
			for(int j = 0; j < i*2 + 1; j++)
				System.out.print("#");
			for(int j = 0; j < n/2 - i; j++)
				System.out.print(".");
			System.out.println();
		}
		for(int i = n/2 - 1; i >= 0 ;i--)
		{
			for(int j = 0; j < n/2 - i; j++)
				System.out.print(".");
			for(int j = 0; j < i*2 + 1; j++)
				System.out.print("#");
			for(int j = 0; j < n/2 - i; j++)
				System.out.print(".");
			System.out.println();
		}
	}
}