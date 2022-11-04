package sonc.quad;

import java.util.HashSet;
import java.util.Set;

public class LeafTrie<T extends HasPoint> extends Trie<T> {
	Set<T> leaf;
	
	public LeafTrie(double topLeftX, double topLeftY, double bottomRightX,
			double bottomRightY) {
		super(topLeftX, topLeftY, bottomRightX, bottomRightY);

		leaf = new HashSet<T>();

	}

	@Override
	public void collectAll(Set<T> points) {
		points.addAll(leaf);
	}

	@Override
	public void collectNear(double x, double y, double radius, Set<T> points) {

		for(T p : leaf) {
			double x1 = p.getX();
			double y1 = p.getY();

			if(getDistance(x1,y1,x,y) <= radius) {
				points.add(p);
			} 
		}
	}

	@Override
	public void delete(T point) {
		leaf.remove(point);
	}

	@Override
	public T find(T point) {
		
		if(leaf.contains(point))
			return point;
		
		return null;

	}

	@Override
	public Trie<T> insert(T point) {
	if (leaf.size() < capacity) {
		leaf.add(point);
		return this;
	}
		NodeTrie<T> n = new NodeTrie<T>(topLeftX,topLeftY,bottomRightX,bottomRightY);
		n.insert(point);
		
		for(T p : leaf) 
			n.insert(p);
		
		return n;
		
	}

	@Override
	public Trie<T> insertReplace(T point) {
		
		for (T p : leaf) {
			if(p.getX() == point.getX() && p.getY() == point.getY()) {
				leaf.remove(p);
				leaf.add(point);
				return this;
			}
		}		
		return null;		
	}

	@Override
	public String toString() {
		return "LeafTrie [bottomRightX=" + bottomRightX + ", bottomRightY="
				+ bottomRightY + ", topLeftX=" + topLeftX + ", topLeftY="
				+ topLeftY + ", toString()=" + super.toString()
				+ ", getClass()=" + getClass() + ", hashCode()=" + hashCode()
				+ "]";
	}
}
