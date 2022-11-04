public class TestDoubledLinkedList {
  public static void main(String args[]) {
    DoubledLinkedList<Integer> l = new DoubledLinkedList<Integer>();
    for(int i = 8 ; i > 0 ; i--)
      l.addFirst(new Integer(i));
    l.add(new Integer(55), 5); 
    System.out.println("list size: " + l.size());
    System.out.println(l);
    l.removeFirst(); 
    l.remove(3);
    System.out.println("indexOf(6): " + l.indexOf(6));
    System.out.println(l);
  }
}
