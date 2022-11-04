import java.util.Stack;


public class binari {
    public static void main(String args[]) {

	int n= 22;

	Stack <Integer> binari = new Stack<Integer>();
	while (n>0) {
	    binari.push( new Integer (n%2) );
	    n = n/2;
	}
	while( !(binari.empty())) {
	    System.out.print(binari.pop());

	}
	System.out.println();
    }
}


	
