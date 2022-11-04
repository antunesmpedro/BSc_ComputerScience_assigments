package sonc.quad;

import java.util.HashSet;
import java.util.Set;

/**
 * This class follows the <b>Facade</b> design pattern and presents a single access point to manage quad trees.
 * It provides methods for inserting, deleting and finding elements implementing <b>HasPoint</b>.
 * This class corresponds to the <b>Client</b> in the <b>Composite</b> design pattern used in this package.
 * @author
 * @param <T> - a type extending <b>HasPoint</b>
 */

public class PointQuadtree<T extends HasPoint> {
	NodeTrie<T> node;
	
	public PointQuadtree(double topLeftX,double topLeftY,double bottomRightX,double bottomRightY) {
		super();
		
		node = new NodeTrie<T> (topLeftX, topLeftY, bottomRightX, bottomRightY);
	}
	
	public void delete(T point) { node.delete(point); }
	
	public T find(T point) { return node.find(point); }
	
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
	
	public void insert(T point) { node.insert(point); }
	
	public void insertReplace(T point) { node.insertReplace(point); }
}