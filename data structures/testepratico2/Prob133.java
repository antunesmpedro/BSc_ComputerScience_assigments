import java.util.Scanner;

// Esta classe providencia a leitura de uma lista a partir do stdin
// e chama o metodo simulate
class Prob133 {

    //--HERE--

    public static void process(Queue<String> q, Queue<String> a, Queue<String> b) {

	while(q.size()!=0) {
	    String name = q.remove();
	    char que = q.remove().charAt(0) ;

	    if (que=='A')
		a.add(name);
	    else if (que=='B')
		b.add(name);
	    else if (que=='X') {
		if (a.size() > b.size() )
		    b.add(name);
		else if (b.size() > a.size())
		    a.add(name);
	    }
	}
    }
    
    public static void main(String args[]) {
	Scanner stdin = new Scanner(System.in);
	
	Queue<String> q = new Queue<String>();
	Queue<String> a = new Queue<String>();
	Queue<String> b = new Queue<String>();
	int n = stdin.nextInt();
	for (int i=0; i<2*n; i++)
	    q.add(stdin.next());

	System.out.println("Inicio:");
	System.out.println("q: " + q);
	System.out.println("a: " + a);
	System.out.println("b: " + b);
	process(q, a, b);
	System.out.println("-------------------------------");
	System.out.println("Final:");
	System.out.println("q: " + q);
	System.out.println("a: " + a);
	System.out.println("b: " + b);
    }
}

class Operation {
    int type;
    
}

// Classe para representar uma fila
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

// Classe para representar um no
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

// Classe para representar uma lista
class LinkedList<T> {  
    Node<T> first; 
    int     size;  
                         
    public LinkedList() {    
	first = null; 
	size  = 0; 
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

    public void addFirst(T value) {
	first = new Node<T>(value, first);
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

    public boolean empty() { 
	return (size == 0); 
    }

    public void removeFirst() {
	if (size == 0) 
	    throw new IndexOutOfBoundsException();
	first = first.next;
	size--;
    }

    
}
