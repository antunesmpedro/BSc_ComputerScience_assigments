class Stack<T> {
  LinkedList<T> elements;

  public Stack() {
    elements = new LinkedList<T>();
  }
  public boolean isEmpty() {
    return elements.empty();
  }
  public int size() {
    return elements.size();
  }
  public T pop() {
    T value = elements.get(0);
    elements.removeFirst();
    return value;
  }
  public void push(T value) {
    elements.addFirst(value);
  } 
  public T top() {
    return elements.get(0);
  }
  public String toString() {
    return elements.toString();
  }
}
