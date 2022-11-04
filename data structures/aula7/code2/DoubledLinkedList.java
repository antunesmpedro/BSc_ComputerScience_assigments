class DNode<T> {
   T    value;
   DNode<T> prev;
   DNode<T> next;

   DNode(T v, DNode<T> p, DNode<T> n) {
     value = v;
     prev  = p;
     next  = n;
   }

   DNode(T v) {
     value = v;
     prev  = null;
     next  = null;
   }
}

public class DoubledLinkedList<T> {  
  DNode<T> first; 
  DNode<T> last; 
  int     size;  
                         
  public DoubledLinkedList() {    
    first = null; 
    last  = null; 
    size  = 0; 
  }

  public boolean empty() { 
    return (size == 0); 
  }

  public int size() { 
    return size; 
  }

  public String toString() {
    if (size == 0) 
      return new String("[]");
    else {
      String  s = new String("[");
      DNode<T> p = first;
      while (p.next != null) {
        s += p.value + ",";
        p = p.next;
      }
      s += p.value + "]";
      return s;
    }
  }

  public int indexOf(T value) {
    int     index = 0;
    DNode<T> p     = first;
    while (p != null) {
      T  currVal = p.value;
      if (currVal.equals(value))
        break;
      p = p.next;
      index++;
    } 
    return (p == null)? -1: index;
  }

  public void addFirst(T value) {
    if(size == 0) {
      DNode<T> node = new DNode<T>(value);
      first         = node;
      last          = node;
    } else 
      first = new DNode<T>(value, null, first);
    size++;
  }
 
  public void add(T value, int index) {
    if ( index < 0 || index > size - 1 ) 
      throw new IndexOutOfBoundsException();
    if ( index == 0 ) 
      first = new DNode<T>(value, null, first);
    else {
      DNode<T> p = first;
      for( int i = 0 ; i < index - 1 ; i++)
        p = p.next;
      DNode<T> node = new DNode<T>(value, p, p.next);
      p.next.prev  = node;
      p.next       = node; 
    }
    size++;
  } 

  public void addLast(T value) {
    if(size == 0) {
      DNode<T> node = new DNode<T>(value);
      first         = node;
      last          = node;
    } else {
      DNode<T> node = new DNode<T>(value, last, null); 
      last.next     = node;
      last          = node;
    }
    size++;
  }
  
  public void removeFirst() {
    if (size == 0) 
      throw new IndexOutOfBoundsException();
    if (size == 1) {
      first = null;
      last  = null;
    } else
      first = first.next;
    size--;
  }

  public void remove(int index) {
    if ( index < 0 || index > size - 1 )
      throw new IndexOutOfBoundsException();
    if (size == 0) 
      throw new IndexOutOfBoundsException();
    if ( index == 0 ) 
      removeFirst();
    else {
      DNode<T> p = first;
      for ( int i = 0; i < index - 1; i++ ) 
        p = p.next;
      DNode<T> q = p.next.next;
      p.next = q;
      q.prev = p;
    }
    size--;
  }

  public void removeLast() {
    if (size == 0) 
      throw new IndexOutOfBoundsException();
    if (size == 1) {
      first = null;
      last  = null;
    } else {
      last = last.prev;
      last.next = null;
    }
    size--;
  }

  public T get(int index) {
    if (size == 0) 
      throw new IndexOutOfBoundsException();
    if ( index < 0 || index > size - 1 )
      throw new IndexOutOfBoundsException();
    DNode<T> p = first;
    for ( int i = 0; i < index ; i++ ) 
      p = p.next;
    return p.value;
  }
}
