public static void reverse(Stack<Integer> s, int n) {
    //int[] invert = new int[n];
    
    LinkedList<Integer> invert = new LinkedList<Integer>();
    
    
    for (int i=0; i<n; i++) {
	//invert[i]=s.pop();
	invert.addLast(s.pop());
	
    }
    for (int i=0; i<n; i++) {
	//s.push(invert[i]);
	s.push(invert.get(i));
	
    }
}
