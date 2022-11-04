package sonc.quad;

import java.util.*;

public class NodeTrie<T extends HasPoint> extends Trie<T> {

	Map<Trie.Quadrant,Trie<T>> nTrie;


	protected NodeTrie(double topLeftX, double topLeftY, double bottomRightX,
			double bottomRightY) {
		super(topLeftX, topLeftY, bottomRightX, bottomRightY);
		// TODO Auto-generated constructor stub

		nTrie = new HashMap<Trie.Quadrant,Trie<T>>();

		nTrie.put(Trie.Quadrant.NE,new LeafTrie<T>(midX,topLeftY,bottomRightX,midY));
		nTrie.put(Trie.Quadrant.NW,new LeafTrie<T>(topLeftX,topLeftY,midX,midY));
		nTrie.put(Trie.Quadrant.SE,new LeafTrie<T>(midX,midY,bottomRightX,bottomRightY));
		nTrie.put(Trie.Quadrant.SW,new LeafTrie<T>(topLeftX,midY,midX,bottomRightY));

	}

	@Override

	protected void collectAll(Set<T> points) {
		// TODO Auto-generated method stub

		for (Trie.Quadrant q : Trie.Quadrant.values()) {
			nTrie.get(q).collectAll(points);
		}		
	}

	@Override
	protected void collectNear(double x, double y, double radius, Set<T> points) {
		// TODO Auto-generated method stub

		for(Trie.Quadrant q : Trie.Quadrant.values()) {
			nTrie.get(q).collectNear(x,y,radius,points);
		}
	}

	@Override
	protected void delete(T point) {
		// TODO Auto-generated method stub

		Trie.Quadrant q = getQuadrant(point);
		nTrie.get(q).delete(point);

	}

	@Override
	protected T find(T point) {
		// TODO Auto-generated method stub
		
		Trie.Quadrant q = getQuadrant(point);
		return nTrie.get(q).find(point);	
	}

	@Override
	protected Trie<T> insert(T point) {
		// TODO Auto-generated method stub
		
		Trie.Quadrant q = getQuadrant(point);
		
		nTrie.put(q, nTrie.get(q).insert(point));
		
		return this;
	}

	@Override
	protected Trie<T> insertReplace(T point) {
		// TODO Auto-generated method stub
		
		Trie.Quadrant q = getQuadrant(point);
		
		return nTrie.put(q, nTrie.get(q).insertReplace(point));
		
	}

	@Override
	public String toString() {
		return "NodeTrie [bottomRightX=" + bottomRightX + ", bottomRightY="
				+ bottomRightY + ", topLeftX=" + topLeftX + ", topLeftY="
				+ topLeftY + ", toString()=" + super.toString()
				+ ", getClass()=" + getClass() + ", hashCode()=" + hashCode()
				+ "]";
	}
}