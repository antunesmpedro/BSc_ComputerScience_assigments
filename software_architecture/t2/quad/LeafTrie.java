package sonc.quad;

import java.util.*;

public class LeafTrie<T extends HasPoint> extends Trie<T> {

	Set<T> leaf;
		
	public LeafTrie(double topLeftX, double topLeftY, double bottomRightX,
			double bottomRightY) {
		super(topLeftX, topLeftY, bottomRightX, bottomRightY);
		// TODO Auto-generated constructor stub

		leaf = new HashSet<T>();

	}

	@Override
	protected void collectAll(Set<T> points) {
		// TODO Auto-generated method stub
		points.addAll(leaf);
	}

	@Override
	protected void collectNear(double x, double y, double radius, Set<T> points) {
		// TODO Auto-generated method stub

		for(T p : leaf) {
			double x1 = p.getX();
			double y1 = p.getY();

			if(getDistance(x1,y1,x,y) <= radius) {
				points.add(p);
			} 
		}
	}

	@Override
	protected void delete(T point) {
		// TODO Auto-generated method stub
		leaf.remove(point);
	}

	@Override
	protected T find(T point) {
		// TODO Auto-generated method stub
		
		if(leaf.contains(point))
			return point;
		
		return null;

	}

	@Override
	protected Trie<T> insert(T point) {
		// TODO Auto-generated method stub
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
	protected Trie<T> insertReplace(T point) {
		// TODO Auto-generated method stub
		
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
