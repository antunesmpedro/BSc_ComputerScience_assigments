package sonc.quad;

import java.util.HashMap;
import java.util.Map;
import java.util.Set;

public class NodeTrie<T extends HasPoint> extends Trie<T> {
	Map<Trie.Quadrant,Trie<T>> nTrie;


	public NodeTrie(double topLeftX, double topLeftY, double bottomRightX,
		double bottomRightY) {
		super(topLeftX, topLeftY, bottomRightX, bottomRightY);

		nTrie = new HashMap<Trie.Quadrant,Trie<T>>();

		nTrie.put(Trie.Quadrant.NE,new LeafTrie<T>(midX,topLeftY,bottomRightX,midY));
		nTrie.put(Trie.Quadrant.NW,new LeafTrie<T>(topLeftX,topLeftY,midX,midY));
		nTrie.put(Trie.Quadrant.SE,new LeafTrie<T>(midX,midY,bottomRightX,bottomRightY));
		nTrie.put(Trie.Quadrant.SW,new LeafTrie<T>(topLeftX,midY,midX,bottomRightY));

	}

	@Override

	public void collectAll(Set<T> points) {

		for (Trie.Quadrant q : Trie.Quadrant.values()) {
			nTrie.get(q).collectAll(points);
		}		
	}

	@Override
	public void collectNear(double x, double y, double radius, Set<T> points) {

		for(Trie.Quadrant q : Trie.Quadrant.values()) {
			nTrie.get(q).collectNear(x,y,radius,points);
		}
	}

	@Override
	public void delete(T point) {

		Trie.Quadrant q = getQuadrant(point);
		nTrie.get(q).delete(point);

	}

	@Override
	public T find(T point) {
		
		Trie.Quadrant q = getQuadrant(point);
		return nTrie.get(q).find(point);	
	}

	@Override
	public Trie<T> insert(T point) {
		
		Trie.Quadrant q = getQuadrant(point);
		
		nTrie.put(q, nTrie.get(q).insert(point));
		
		return this;
	}

	@Override
	public Trie<T> insertReplace(T point) {
		
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
