class Queue<T> {
  LinkedList<T> elements;

  public Queue() {
    elements = new LinkedList<T>();
  }
  public boolean isEmpty() {
    return elements.empty();
  }
  public int size() {
    return elements.size();
  }
  public void add(T value) {
    elements.addLast(value);
  } 
  public T peek() {
    return elements.get(0);
  }
  public T remove() {
    T value = elements.get(0);
    elements.removeFirst();
    return value;
  }
  public String toString() {
    return elements.toString();
  }
}
