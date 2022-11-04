package sonc.battle;

import java.util.Random;
import java.util.Set;
//import java.util.List;

import sonc.quad.PointQuadtree;

/**
 * A rectangular area where battles take place. It contains a collection of moving objects, 
 * some of which are ships (other are munitions). It provides methods for updating the state of moving objects 
 * within it. Those that fell of the boundaries are automatically discarded, including ships.
 * 
 * The state of this class includes a PointQuadtree for managing moving objects and efficiently detecting collisions.
 * 
 * The are a number of static properties that parameterize worlds.
 * Their getters are public but the setter cannot be visible to concrete ships (those submitted by players).
 * 
 * The main method provided by this class is battle(List) that receives a list of Ship and returns a Movie. 
 * 
 * @author
 */

public class World {
	static int numberRounds;
	static double marginOfBorder = 50;
	static double worldWidth = 1000;
	static double worldHeight = 1000;
	static double collisionDist;
	Set<Ship> setShips;
	int currRound;
	Set<MovingObject> setMovingObjects;
	PointQuadtree<MovingObject> world = new PointQuadtree<MovingObject>(0, 0, 1000, 1000); // ??
	
	public World() {
	}
	
	/**
	 * Number of rounds in a battle
	 * @return rounds - in a battle
	 */
	
	public static int getRounds() { return numberRounds; }
	
	static void setRounds(int rounds) { numberRounds = rounds; }
	
	public static double getMargin() { return marginOfBorder; }
	
	/**
	 * Set the margin from border used for placing ships within the world. 
	 * @param margin - to border when placing ships
	 */
	
	static void setMargin(double margin) { marginOfBorder = margin; }

	public static double getWidth() { return worldWidth; }
	
	static void setWidth(double width) { worldWidth = width; }
	
	public static double getHeight() { return worldHeight; }
	
	static void setHeight(double height) { worldHeight = height; }
	
	/**
	 * Minimum distance between object to be considered as a collision
	 * @return distance in pixels
	 */
	
	public static double getCollisionDistance() { return collisionDist; }
	
	static void setCollisionDistance(double collisionDistance) { collisionDist = collisionDistance; }

	/**
	 * Add a ship to this world. Set it in a random position.
	 * Initialize the ship and reset its points
	 * @param ship - to be added
	 */
	
	void addShipAtRandom(Ship ship) {
		double margin = getMargin();
		double width = getWidth();
		double height = getHeight();
		Random rand = new Random();
		double rangeMaxX = width-margin;
		double rangeMaxY = height-margin;
		//double x = rand.nextDouble(rangeMaxX) + margin;
		double x = margin + rangeMaxX * rand.nextDouble();
		//double y = rand.nextDouble(height-margin) + margin;
		double y = margin + rangeMaxY * rand.nextDouble();
		
		ship.resetPoints();
		ship.setX(x);
		ship.setY(y);
		
		world.insert(ship);
	}
	
	/**
	 * Add a ship to this world. Define position and heading Initialize the ship and reset its points. 
	 * This method is useful for testing
	 * @param ship - to be added
	 * @param x - coordinate of initial position
	 * @param y - coordinate of initial position
	 * @param heading - of ship at the initial position
	 */
	
	void addShipAt(Ship ship, double x, double y, double heading) {
		ship.setHeading(heading);
		ship.setX(x);
		ship.setY(y);
		world.insert(ship);
	}

	/**
	 * Set of ships in this world
	 * @return set of <b>Ship</b> instances
	 */
	
	public Set<Ship> getShips() { return this.setShips; }

	/**
	 * Make a battle with given ships. The battle unfolds for a number of rounds defined by the rounds property.
	 * The init() method of each of these ships is invoked in the beginning, 
	 * and the method move() is invoked in each turn. 
	 * These two methods are invoked trough the safe executor.
	 * If they raise any exception, including those due to timeout or to attempt to use system resources, then the ship is removed from the battle.
	 * @param ships - as a list of <b>Ship</b> instances
	 * @return movie of the battle
	 */
	
	//public Movie battle(List<Ship> ships) {}
	
	/**
	 * Get the number of round from the initial one (round 0). The current number of rounds is need keeping delays between consecutive firings (of munition). This method is available to concrete ships
	 * @return currentRound of the battle
	 */
	
	public int getCurrentRound() { return currRound; }
	
	/**
	 * Set the number of round from the initial one (round 0). The current number of rounds is need keeping delays between consecutive firings (of munition). This method is not available to concrete ships
	 * @param currentRound - of the battle
	 */
	
	void setCurrentRound(int currentRound) { currRound = currentRound; }

	/**
	 * Update the world by moving objects, removing those outside the boundaries, checking those that were hit by another one,
	 *  reducing their status, terminating those that reach zero. 
	 *  This method uses and creates a new version of the PointQuadtree containing all moving objects in the world instance.
	 */
	
	//void update();
	
	/**
	 * Add a moving object to the world
	 * @param added - object
	 */
	
	void addMovingObject(MovingObject added) { world.insert(added); }
	
	/**
	 * The set of all moving objects in the world. Mostly for tests.
	 * @return set of <b>MovingObject</b> instances
	 */
	
	Set<MovingObject> getMovingObjects() { return this.setMovingObjects; }
}