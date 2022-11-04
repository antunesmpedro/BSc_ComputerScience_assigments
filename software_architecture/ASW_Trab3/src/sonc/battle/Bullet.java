package sonc.battle;

public class Bullet extends Munition {
	String color = "grey";
	static int power;
	static double speedBullet;
	static int fireDelayBullet;
	int size = 5;

	/**
	 * Create a bullet with a certain heading. The initial position will be that of the ship that fires the missile.
	 * @param heading - of the bullet
	 */
	
	public Bullet(double heading) {
		super(5, heading, 0);
	}
	
	/**
	 * Set the damage inflicted by a bullet in the status of ship it hits. This method should be invoked before any battle.
	 * @param damage - inflicted by guided missiles
	 */
	
	static void setDamage(int damage) { power = damage; }
	
	/**
	 * Get the damage inflicted by a guided missile in the status of ship it hits.
	 * @return damage inflicted by a guided missile
	 */
	
	static int getDamage() { return power; }
	
	static void setInitialSpeed(double speed) { speedBullet = speed; }
	
	static double getInitialSpeed() { return speedBullet; }
	
	static void setFireDelay(int fireDelay) { fireDelayBullet = fireDelay; }

	/**
	 * Get the delay for firing this kind of munition
	 * @return delay in number of rounds
	 */
	
	static int getFireDelay() { return fireDelayBullet; }
	
	@Override
	double getMaxSpeed() {
		return MAXSPEED;
	}

	@Override
	double getMaxSpeedChange() {
		return max_Speed_Change;
	}

	@Override
	double getMaxRotation() {
		return max_Rotation;
	}

	/**
	 * Description copied from class: <b>MovingObject</b>
	 * Damage inflicted by this moving object when it hits another
	 * @return - amount of status removed from another moving object on collision
	 */
	
	@Override
	int getImpactDamage() {
		return getDamage();
	}
	
	/**
	 * Description copied from class: <b>Munition</b>
	 * Number of rounds a ship must wait to fire this munition sice it fired the last time
	 * @return - delay in number of rounds
	 */
	
	@Override
	int fireDelay() {
		return getFireDelay();
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
