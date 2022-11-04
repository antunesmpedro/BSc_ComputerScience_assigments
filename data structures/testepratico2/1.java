  public void duplicate() {
	if (size==0)
	    return;	
	Node<T> p = first;
	for(int i=0; i<size(); i++) {
	    Node<T> n = new Node<T>(p.value, p.next);
	    p.next=n;
	    p= n.next;
	}
	size = size*2; 
    }
