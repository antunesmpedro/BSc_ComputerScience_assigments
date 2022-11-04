public class TestQueue {
  public static void main(String args[]) {
    Queue<Integer> q = new Queue<Integer>();
    for(int i = 8 ; i > 0 ; i--) {
      q.add(new Integer(i));
      System.out.println(q);
    }
    System.out.println("queue size: " + q.size());
    System.out.println(q);
    System.out.println(q.remove());
    System.out.println(q.remove());
    q.add(new Integer(12));
    System.out.println("queue size: " + q.size());
    System.out.println(q);
    System.out.println(q.remove());
    System.out.println(q.remove());
    System.out.println(q.remove());
    System.out.println(q.remove());
    System.out.println(q.remove());
    System.out.println(q.remove());
  }
}
