class Node<T> {
    T    value;
    Node<T> next;

    Node(T v, Node<T> n) {
	value = v;
	next  = n;
    }

    Node(T v) {
	value = v;
	next  = null;
    }
}

public class LinkedList<T> {  
    Node<T> first; 
    int     size;  
                         
    public LinkedList() {    
	first = null; 
	size  = 0; 
    }
    public LinkedList(LinkedList<T> l) {  
	first = l.first;
	size  = l.size; 
    }

    public Node<T> getFirst() { 
	return first; 
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
	    Node<T> p = first;
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
	Node<T> p     = first;
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
	first = new Node<T>(value, first);
	size++;
    }
 
    public void add(T value, int index) {
	if ( index < 0 || index > size - 1 )
	    throw new IndexOutOfBoundsException();
	if ( index == 0 ) 
	    first = new Node<T>(value, first);
	else {
	    Node<T> p = first;
	    for( int i = 0 ; i < index - 1 ; i++)
		p = p.next;
	    p.next = new Node<T>(value, p.next);
	}
	size++;
    } 

    public void addLast(T value) {
	if(size == 0) 
	    first = new Node<T>(value, first);
	else {
	    Node<T> p = first;
	    for( int i = 0 ; i < size - 1 ; i++)
		p = p.next;
	    p.next = new Node<T>(value);
	}
	size++;
    } 
  
    public void removeFirst() {
	if (size == 0) 
	    throw new IndexOutOfBoundsException();
	first = first.next;
	size--;
    }

    public void remove(int index) {
	if ( index < 0 || index > size - 1 )
	    throw new IndexOutOfBoundsException();
	if (size == 0) 
	    throw new IndexOutOfBoundsException();
	if ( index == 0 ) 
	    first = first.next;
	else {
	    Node<T> p = first;
	    for ( int i = 0; i < index - 1; i++ ) 
		p = p.next;
	    p.next = p.next.next;
	}
	size--;
    }

    public void removeLast() {
	if (size == 0) 
	    throw new IndexOutOfBoundsException();
	remove(size - 1);
    }

    public T get(int index) {
	if (size == 0) 
	    throw new IndexOutOfBoundsException();
	if ( index < 0 || index > size - 1 )
	    throw new IndexOutOfBoundsException();
	Node<T> p = first;
	for ( int i = 0; i < index ; i++ ) 
	    p = p.next;
	return p.value;
    }
    
    public int count(T value) {

	int count = 0;
	int     index = 0;
	Node<T> p     = first;
	while (p != null) {
	    T  currVal = p.value;
	    if (currVal.equals(value))
		count++;
	    p = p.next;
	    index++;
	} 
	return (count);
    }
    public static void main(String args[] ) {
	LinkedList<Integer> list = new LinkedList<Integer>();
	list.addFirst(1);
	list.addFirst(2);
	list.addFirst(1);
	list.addFirst(3);
	list.addFirst(1);
	list.addFirst(2);
	list.addFirst(1);
	System.out.println(list);
	System.out.println("Ocorrencias de 1: " + list.count(1));
	System.out.println("Ocorrencias de 2: " + list.count(2));
	System.out.println("Ocorrencias de 3: " + list.count(3));

    }

}


