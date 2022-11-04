package sonc.battle;

import sonc.quad.HasPoint;

/**
 * Common class to all moving objects in the game, including ships and the munitions they throw at each other
 * @author
 */

public abstract class MovingObject implements HasPoint {
	int status;
	double heading;
	double speed;
	double x = 0;
	double y = 0;
	
	/**
	 * Initialize a moving object with given status, heading and speed
	 * @param status - of this moving object at start
	 * @param heading - of this moving object at start
	 * @param speed - of this moving object at start
	 */
	
	MovingObject(int status, double heading, double speed) {
		this.status = status;
		this.heading = heading;
		this.speed = speed;
	}
	
	@Override
	public double getX() {
		return this.x;
	}
	
	void setX(double x) { this.x = x; }

	@Override
	public double getY() {
		return this.y;
	}
	
	void setY(double y) { this.y = y; }
	
	public double getHeading() { return this.heading; }
	
	void setHeading(double heading) { 
		if(heading > (2*Math.PI) || heading < 0) this.heading = normalizeAngle(heading);
		else this.heading = heading;
	}

	public double getSpeed() { return this.speed; }
	
	/**
	 * Normalize angles in range [0,2*PI[ in radians. The value is added, or subtracted 2xPI, respectively while it is less than 0, or greater or equal than 2xPI. The method is available to concrete ships
	 * @param angle - to normalize
	 * @return normalized angle in range [0,2*PI[
	 */
	
	protected double normalizeAngle(double angle) { 
		double newAngle = angle;
		
		while(newAngle >= (2*Math.PI)) newAngle -= 2*Math.PI;
		
		while(newAngle < 0) newAngle += 2*Math.PI;
		
		return newAngle;
	}

	/**
	 * Distance from this moving object to another given as parameter
	 * @param other - moving object
	 * @return distance to other
	 */
	
	protected double distanceTo(MovingObject other) {
		double x1 = this.getX();
		double x2 = other.getX();
		double y1 = this.getY();
		double y2 = other.getY();
		
		return Math.sqrt(Math.pow((x2-x1), 2) + Math.pow((y2-y1), 2));
	}

	/**
	 * Angle from this moving object to another given as parameter. 
	 * Angles are in radians in the range [0,2*PI: 0 is right, PI/2 is down, PI is left and 3/2*PI is up
	 * @param other - moving object
	 * @return angle to other object or NaN if some coordinates is not defined
	 */
	
	protected double headingTo(MovingObject other) {
		double otherY = other.getY();
		double otherX = other.getX();
		double cx = this.getX();
		double cy = this.getY();
		
		//if((otherY == -1) || (otherX == -1) || (cx == -1) || (cy == -1)) return Double.NaN;
		//coordinates are initialized with 0
		
		double dy = otherY - cy;
		double dx = otherX - cx;
		
		double angle = Math.atan2(dy , dx);
		
		if(angle > (2*Math.PI) || angle < 0) return normalizeAngle(angle);
		return angle;
	}

	/**
	 * Update the position - (x,y) coordinates - of this moving object taking in consideration the current speed and heading. This method cannot be invoked by a concrete ship.
	 */
	
	final void updatePosition() {
		this.x = this.getX() + this.speed * Math.cos((2*Math.PI) - this.heading);
		this.y = this.getY() + (-1) * this.speed * Math.sin((2*Math.PI) - this.heading);
	}
	
	/**
	 * Change heading of this moving object by given variation. Positive variation correspond to clockwise rotations and negative variations to counterclockwise rotations. If the absolute value of variation exceeds the predefined maximum rotation than it is limited to that value (with the corresponding signal). This method cannot be invoked by a concrete ship.
	 * @param delta - angle in radians
	 */
	
	final void doRotate(double delta) {
		double newAngle = 0;
		
		newAngle = getHeading() + delta;
		
		double maxRotation = getMaxRotation();
		
		if(newAngle > maxRotation) setHeading(maxRotation);
		else {
			if(newAngle > (2*Math.PI) || newAngle < 0) setHeading(normalizeAngle(newAngle));
			else setHeading(newAngle);
		}
	}
	
	/**
	 * Change speed of this moving object. Positive values increase the speed and negative values decrease it. 
	 * If either the absolute value of variation, or the absolute value of the changed speed, 
	 * exceeds their respective predefined maximums (getMaxSpeedChange() and getMaxSpeed() then 
	 * they are limited to that value (with the corresponding signal). 
	 * This method cannot be invoked by a concrete ship.
	 * @param delta - angle variation (in radians)
	 */
	
	final void doChangeSpeed(double delta) { 
		boolean flagNegative = false;
		double newSpeed = this.speed + delta;
		
		if(newSpeed < 0) flagNegative = true;
		
		double absValueVariation = Math.abs(delta - this.speed);
		double absValueChangedSpeed = Math.abs(newSpeed);
		
		// limited by the MaxSpeedChange
		if(absValueVariation > getMaxSpeedChange() && (getMaxSpeed() > absValueChangedSpeed)) {
			if(flagNegative) this.speed -= getMaxSpeedChange();
			else this.speed = getMaxSpeedChange();
		}
		// limited by the MaxSpeed
		else if(absValueVariation < getMaxSpeedChange() && (getMaxSpeed() < absValueChangedSpeed)) {
			if(flagNegative) this.speed -= getMaxSpeed();
			else this.speed = getMaxSpeed();
		}
		// respect the bounds
		else this.speed = newSpeed;

	}
	
	/**
	 * Override this method to define the movement of this object. Concrete ships will need to do it to implement their strategies
	 */

	void move() {}
	
	/**
	 * Change status to reflect damage inflicted by given moving object
	 * @param moving - object that hit this one
	 */
	
	void hitdBy(MovingObject moving) {
		this.status -= moving.getImpactDamage();
	}
	
	/**
	 * Check if this moving object was destroyed
	 * @return true if this object is destroyed, false otherwise
	 */
	
	public boolean isDestroyed() {
		if(status <= 0) return true;
		return false;
	}
	
	public int getStatus() { return this.status; }
	
	abstract double getMaxSpeed();
	
	abstract double getMaxSpeedChange();
	
	abstract double getMaxRotation();
	
	abstract int getImpactDamage();

	abstract Ship getOrigin();
	
	public abstract int getSize();
	
	public abstract String getColor();
}