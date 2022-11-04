package sonc.battle;

import java.util.HashSet;
import java.util.Set;

import sonc.quad.HasPoint;

public class Ship extends MovingObject implements HasPoint {
	String shipName;
	String shipColor = "blue";
	static int damageOnCollision;
	static double maxShip_Rotation;
	static double maxShip_SpeedChange;
	static int maxShipStatus;
	int lastFireRound = Integer.MIN_VALUE;
	World thisShipWorld;
	ShipCommand lastCommand;
	int currentShipPoints = 0;
	int shipSize = 25;
	final double MAXSPEED = 5;
	
	public Ship() {
		super(100, 0, 0);
	}
	
	
	/**
	 * Set the amount of damage produced by ships. Should be invoked before instancing any ships. This method cannot be invoked by concrete ships.
	 * @param damage produced by ships when they collide
	 */
	
	static void setDamage(int damage) { damageOnCollision = damage; }
	
	/**
	 * The damaged produced by ship when it collides with another ship
	 * @return damage produced by ships when they collide
	 */
	
	static int getDamage() { return damageOnCollision; }
	
	static void setMaxShipRotation(double maxShipRotation) { maxShip_Rotation = maxShipRotation; }

	static double getMaxShipRotation() { return maxShip_Rotation; }
	
	public static void setMaxShipSpeedChange(double maxShipSpeedChange) { maxShip_SpeedChange = maxShipSpeedChange; }
	
	static double getMaxShipSpeedChange() { return maxShip_SpeedChange; }

	static void setMaxStatus(int maxStatus) { maxShipStatus = maxStatus; }
	
	static int getMaxStatus() { return maxShipStatus; }

	/**
	 * The world where the ship sails. This method is available to concrete ships. 
	 * @return world instance
	 */
	
	protected World getWorld() { return this.thisShipWorld; }
	
	/**
	 * Set this ship in a world. This method is not available to concrete ships
	 * @param world where ship will sail
	 */

	void setWorld(World world) { this.thisShipWorld = world; }
	
	/**
	 * Get the last round when this ship fired a munition. This method is available to concrete ships.
	 * @return last round when ship fired or Integer.MIN_VALUE if it never fired
	 */
	
	protected int getLastFireRound() { return this.lastFireRound;  }
	
	/**
	 * Check if this ship can fire the given munition. The difference between the current round and the 
	 * last fired round must be greater than the fire delay for this munition.
	 * @param munition - to be fired
     * @return true if munition can be fired or false otherwise 
	 */
	
	protected boolean canFire(Munition munition) {
		int fireDelay = munition.fireDelay();
		int currentRound = this.thisShipWorld.getCurrentRound();
		if((currentRound - getLastFireRound()) > fireDelay) return true;
		return false;
	}

	void setLastFireRound(int lastFireRound) { this.lastFireRound = lastFireRound; }
	
	/**
	 * The latest command set by the concrete ship
	 * @return command set by concrete ship
	 */
	
	ShipCommand getCommand() { return this.lastCommand; }
	
	/**
	 * Set a command resulting from a method invoked by the {code move()} method executed by a concrete ship. 
	 * This method should only be invoked from a {code World} instance and cannot be invoked by concrete ships.
	 * @param command to be executed
	 */
	
	void setCommand(ShipCommand command) { this.lastCommand = command; }
	
	public int getPoints() { return this.currentShipPoints; }
	
	void resetPoints() { this.currentShipPoints = 0; }
	
	void addPoints(int points) { this.currentShipPoints += points; }
	
	/**
	 * Specified by: getMaxSpeed in class MovingObject
	 * @returns maximum speed
	 */
	
	double getMaxSpeed() { return Math.abs(this.MAXSPEED); }
	
	/**
	 * Specified by: getMaxSpeedChange in class MovingObject
	 * @return maximum speed variation
	 */

	double getMaxSpeedChange() { return maxShip_SpeedChange; }
	
	/**
	 * Specified by: getMaxRotation in class MovingObject
	 * @return maximum rotation
	 */
	
	double getMaxRotation() { return maxShip_Rotation; }
	
	/**
	 * Execute the latest command defined by the concrete ship. 
	 * This method should only be invoked from a World instance and cannot be invoked by concrete ships.
	 */
	
	void execute() {
		//if(this.getClass().equals(World.class)) { // JUNIT
			ShipCommand cmd = this.getCommand();
			cmd.execute();
		//}
	}
	
	/**
	 * Change the speed of this ship by given delta. This command will be effective only if it is the last executed in a round
	 * @param delta - variation of speed
	 */
	
	protected final void changeSpeed(double delta) {
		ChangeSpeedCommand speedCmd = new ChangeSpeedCommand(this, delta);
		setCommand(speedCmd);
	}

	/**
	 * Rotate the ship by given angle. This command will be effective only if it is the last executed in a round. This command cannot be override by concrete ships.
	 * @param delta - the rotation angle
	 */
	
	
	protected final void rotate(double delta) {
		RotateCommand rotateCmd = new RotateCommand(this, delta);
		setCommand(rotateCmd);
	}
	
	/**
	 * Initialize your ship. This method is called when the ship starts sailing. Use this method
	 */
	
	/**
	 * Fire a munition given as parameter, start in current position (e.g. {code fire(new Bullet(headingTo(enemy)))}. 
	 * This command will be effective only if it is the last executed in a round. 
	 * This command cannot be override by concrete ships.
	 * @param munition - to be fired from ship
	 */
	
	protected final void fire(Munition munition) {
		FireCommand fireCmd = new FireCommand(this.thisShipWorld, this, munition);
		setCommand(fireCmd);
	}
	
	/**
	 * A set of all other ships in the world, except this one
	 * @return a set of ships
	 */
	
	 protected final Set<Ship> getOtherShips() {
		 //usar antes this.thisShipWorld.getShips()
		 // é preciso definir no world um campo set thisWorldShips
		 // e adicionar a esse set nos metodos addShipAt e addShipRandom
		 Set<MovingObject> setMovingObjects = this.thisShipWorld.getMovingObjects();
		 Set<Ship> setShips = new HashSet<Ship>();
		 for (MovingObject o : setMovingObjects) {
			    if(o.getOrigin() == null) {
			    	setShips.add((Ship) o);
			    }
			}
		 return setShips;
	 }
	
	 //since the constructor is never called, init is used to substitute the constructor
	protected void init() {
	}
	
	/**
	 * Move your ship. Redefine this method to implement how this ship must be moved
	 * @overrides move in class MovingObject
	 */
	
	@Override
	protected void move() { 
		this.updatePosition();
	}
	
	/**
	 * Specified by: getImpactDamage in class MovingObject
	 * @return amount of status removed from another moving object on collision
	 */
	
	final int getImpactDamage() { return damageOnCollision; }
	
	/**
	 * Specified by: getOrigin in class MovingObject
	 * @return ship from which this moving object started (Munition class) or (or null if a ship)
	 */
	
	final Ship getOrigin() { return null; }
	
	/**
	 * Specified by: getSize in class MovingObject
	 * @return size of this moving object
	 */
	
	public final int getSize() { return this.shipSize; }
	
	/**
	 * Specified by: getColor in class MovingObject
	 * @return color as a HTML/CSS string or basic color
	 */
	
	public String getColor() { return this.shipColor; }
	
	public String getName() { return this.shipName; }
}
