package sonc.quad;

import java.util.*;

public class PointQuadtree<T extends HasPoint> {

	NodeTrie<T> node;
	
	public PointQuadtree(double topLeftX,double topLeftY,double bottomRightX,double bottomRightY) {
		super();
		// TODO Auto-generated constructor stub
		
		node = new NodeTrie<T> (topLeftX, topLeftY, bottomRightX, bottomRightY);
		
	}
	
	public void delete(T point) {
		node.delete(point);
	}
	
	public T find(T point) {
		return node.find(point);
	}
	
	public Set<T> findNear(double x, double y, double radius) {
		Set<T> p = new HashSet<T>();
		node.collectNear(x, y, radius, p);
		return p;
	}
	
	public Set<T> getAll() {
		Set<T> p = new HashSet<T>();
		node.collectAll(p);
		return p;
	}
	
	public void insert(T point) {
		node.insert(point);
	}
	
	public void insertReplace(T point) {
		node.insertReplace(point);
	}

}
