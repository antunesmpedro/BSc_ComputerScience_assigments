class TestDeque {
  public static void main(String[] args) {
    final int N = 10;
    Deque<Integer> dq = new Deque<Integer>();

    for (int i = N ; i > 0 ; i--) 
      dq.addFirst(new Integer(i));
    System.out.println(dq);
    for (int i = 0 ; i < N ; i++)
      dq.addLast(new Integer(i + 1 + N));
    System.out.println(dq);
    for (int i = 0 ; i < N ; i++) {
      Integer j, k;
      j = dq.removeFirst();
      k = dq.removeLast();
      System.out.printf("(%2d,%2d)%n", j.intValue(), k.intValue());
    }
  }
}
