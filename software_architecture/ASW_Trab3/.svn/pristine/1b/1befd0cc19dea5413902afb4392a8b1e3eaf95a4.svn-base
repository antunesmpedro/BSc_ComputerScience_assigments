package sonc.battle;

abstract class Munition extends MovingObject {
	Ship shipOrigin;
	static double max_Rotation;
	static double max_Speed_Change;
	final double MAXSPEED = 5;
	
	Munition(int status, double heading, double speed) {
		super(status, heading, speed);
	}
	
	/**
	 * Initial movement from its origin, to avoid being considered as hitting it
	 */
	
	void escape() {
		x = shipOrigin.getX();
		y = shipOrigin.getY();
		shipOrigin.getWorld();
		double collisionDistance = World.getCollisionDistance();
		
		setX(x + collisionDistance + 1);
		setY(y + collisionDistance + 1);
	} 
	
	
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
	 * Number of rounds a ship must wait to fire this munition since it fired the last time
	 * @return delay in number of rounds
	 */
	
	abstract int fireDelay();
	
	void setOrigin(Ship origin) {
		this.shipOrigin = origin;
	}

	@Override
	Ship getOrigin() {
		return this.shipOrigin;
	}
}
