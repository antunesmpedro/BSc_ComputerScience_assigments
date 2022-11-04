import java.util.Stack;


public class parentisis {

    public boolean balanced(String s) {
	
	Stack <Character> balance = new Stack<Character>();
	String y = s;
	
	for (int i=0; i <y.length(); i++) {
	    balance.addElement(y.charAt(i));
	}
    }
    public static void main(String args[]) {

	balanced("(()()(");
	/*	System.out.println(balanced("([()])"));
		System.out.println(balanced("[()()]"));
		System.out.println(balanced("(()]"));
		System.out.println(balanced("[()[])"));
		System.out.println(balanced("[()[]"));
	*/
    }
}
