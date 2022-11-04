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
