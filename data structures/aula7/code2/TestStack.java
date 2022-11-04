import java.util.Stack;

public class TestStack {
  public static void main(String args[]) {
    Stack<Integer> s = new Stack<Integer>();
    for(int i = 8 ; i > 0 ; i--)
      s.push(new Integer(i));

    System.out.println("stack size: " + s.size());
    System.out.println(s);
    s.pop();
    s.pop();
    s.push(new Integer(12));
    System.out.println("stack size: " + s.size());
    System.out.println(s);
    s.pop();
    s.pop();
    s.pop();
    s.pop();
    s.pop();
    s.pop();
    s.pop();
    System.out.println("stack size: " + s.size());
    System.out.println(s);
  }
}
