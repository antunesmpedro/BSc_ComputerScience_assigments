class Deque<T> {
  DoubledLinkedList<T> elements;

  public Deque() {
    elements = new DoubledLinkedList<T>();
  }

  public boolean isEmpty() {
    return elements.empty();
  }

  public void addFirst(T value) {
    elements.addFirst(value);
  } 

  public void addLast(T value) {
    elements.addLast(value);
  } 

  public T peekFirst() {
    return elements.get(0);
  }

  public T peekLast() {
      return elements.get(elements.size() - 1);
  }

  public T removeFirst() {
    T value = elements.get(0);
    elements.removeFirst();
    return value;
  }

  public T removeLast() {
    T value = elements.get(elements.size() - 1);
    elements.removeLast();
    return value;
  }

  public String toString() {
    return elements.toString();
  }
}
