package sonc.battle;

import sonc.quad.HasPoint;

public class GuidedMissile extends Munition implements HasPoint {
	String color = "grey";
	int size = 8;
	static int fireDelayBullet;
	static double initialSpeed;
	static int power;
	MovingObject enemy;
	
	/**
	 * Create a guided missile with a certain initial heading and a target. The initial position will be that of the ship that fires the missile
	 * @param heading - of the guided missile when fired
	 * @param target - of the guided missile
	 */
	
	GuidedMissile(double heading, MovingObject target) {
		super(5, heading, 0);
		this.escape();
		this.enemy = target;
	}
	
	/**
	 * Description copied from class: <b>MovingObject</b>
	 * Override this method to define the movement of this object. Concrete ships will need it to implement their strategies.
	 */
	
	@Override
	void move() {
		this.updatePosition();
	}
	
	static void setDamage(int damage) { power = damage; }
	
	public static int getDamage() {  return power; }
	
	static double getMaxMissileRotation() { return max_Rotation; }
	
	/**
	 * Set the maximum rotation per turn of a ship. This method should be used before instancing ships and cannot be invoked by concrete ships.
	 * @param maxMissileRotation - of guided missiles
	 */
	
	static void setMaxMissileRotation(double maxMissileRotation) { max_Rotation = maxMissileRotation; }
	
	public static void setInitialSpeed(double speed) { initialSpeed = speed; }
	
	public static double getInitialSpeed() { return initialSpeed; }
	
	static void setFireDelay(int fireDelay) { fireDelayBullet = fireDelay; }
	
	static int getFireDelay() { return fireDelayBullet; }
	
	@Override
	int fireDelay() {
		return getFireDelay();
	}

	@Override
	double getMaxSpeed() {
		return MAXSPEED;
	}

	@Override
	double getMaxRotation() {
		return max_Rotation;
	}

	@Override
	int getImpactDamage() {
		return getDamage();
	}

	@Override
	public int getSize() {
		return this.size;
	}

	@Override
	public String getColor() {
		return this.color;
	}

}
