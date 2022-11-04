package sonc.quad;

import java.util.*;

public abstract class Trie <T extends HasPoint> {

	protected double bottomRightX;
	protected double bottomRightY;
	static int capacity;
	protected double topLeftX;
	protected double topLeftY;

	protected double midY, midX;

	protected Trie(double topLeftX, double topLeftY, double bottomRightX, double bottomRightY){
		this.topLeftX = topLeftX;
		this.topLeftY = topLeftY;
		this.bottomRightX = bottomRightX;
		this.bottomRightY = bottomRightY;

		midY = (topLeftY + bottomRightY)/2;		
		midX = (topLeftX + bottomRightX)/2;
	}

	protected static enum Quadrant {
		NE,NW,SE,SW
	}

	public static Quadrant valueOf(String name) throws IllegalArgumentException, NullPointerException {

		if (name == null)
			throw new NullPointerException();

		switch (name) {
		case "NE" : return Quadrant.NE;
		case "NW" : return Quadrant.NW;
		case "SE" : return Quadrant.SE;
		case "SW" : return Quadrant.SW;
		default : throw new IllegalArgumentException();	
		}		
	}

	public static Quadrant[] values() {
		Trie.Quadrant valores [] = new Trie.Quadrant[4];

		valores[0] = Quadrant.NE;
		valores[1] = Quadrant.NW;
		valores[2] = Quadrant.SE;
		valores[3] = Quadrant.SW;

		return valores;
	}

	public Quadrant getQuadrant(T point) {


		if(point.getY() <= midY && point.getX() >= midX) 
			return Quadrant.NE;

		else if(point.getY() <= midY && point.getX() <= midX)		
			return Quadrant.NW;

		else if(point.getY() >= midY && point.getX() >= midX)	
			return Quadrant.SE;

		else if(point.getY() >= midY && point.getX() <= midX)	
			return Quadrant.SW;


		return null;
	}

	protected abstract void collectAll(Set<T> points);

	protected abstract void collectNear(double x, double y, double radius, Set<T> points);

	protected abstract void delete(T point);

	protected abstract T find(T point);

	public static int getCapacity() {
		return capacity;
	}

	public static double getDistance(double x1, double y1, double x2, double y2) {
		return Math.pow(Math.pow(x2 - x1,2) + Math.pow(y2 - y1,2),0.5);
	}

	protected abstract Trie<T> insert(T point);

	protected abstract Trie<T> insertReplace(T point);


	//https://yal.cc/rectangle-circle-intersection-test/
	protected boolean overlaps(double x, double y, double radius) {

		if (bottomRightX >= x && x >= topLeftX && bottomRightY >= y && y >= topLeftY) {
			return true;
		}

		double deltaX = x - Math.max(topLeftX, Math.min(x, bottomRightX));
		double deltaY = y - Math.max(topLeftY, Math.min(y, bottomRightY));

		return (Math.pow(deltaX,2) + Math.pow(deltaY,2) < Math.pow(radius,2));

	}

	public static void setCapacity (int capacity) {
		Trie.capacity = capacity;
	}

	@Override
	public String toString() {
		return "Trie [bottomRightX=" + bottomRightX + ", bottomRightY="
				+ bottomRightY + ", topLeftX=" + topLeftX + ", topLeftY="
				+ topLeftY + ", getClass()=" + getClass() + ", hashCode()="
				+ hashCode() + ", toString()=" + super.toString() + "]";
	}


}
