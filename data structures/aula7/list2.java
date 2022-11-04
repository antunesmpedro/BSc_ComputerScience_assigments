import java.util.*;

class Pair <L,R> {

private L l;
private R r;
		public Pair(L l, R r) {
			this.l = l;
			this.r = r;
		}
		public L getL() {return l;}
		public R getR() {return r;}		
		
	
}
public class list2 {
	public static void main(String agrs[]){
		List<Pair<Integer,Integer>> l= new ArrayList<Pair<Integer,Integer>> ;
		
		l.addLast(1,1);
		l.addLast(1,2);
		l.addLast(1,3);
		l.addLast(2,1);
		l.addLast(2,2);
		l.addLast(2,3);
		l.addLast(3,1);
		l.addLast(3,2);
		l.addLast(3,3);
		
		System.out.println(l);
