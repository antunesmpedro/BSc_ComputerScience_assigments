package sonc.battle;

public class ChangeSpeedCommand implements ShipCommand {
	Ship shipToChangeSpeed;
	double newSpeed;
	
	/**
	 * Create a ChangeSpeedCommand from given data
	 * @param ship - that changes speed
	 * @param delta - variation in speed
	 */
	
	ChangeSpeedCommand(Ship ship, double delta) {
		this.shipToChangeSpeed = ship;
		this.newSpeed = delta;
	}
	
	/**
	 * <b>Specified by:</b> execute in interface <i>ShipCommand</i>
	 */
	
	public void execute() {
		this.shipToChangeSpeed.doChangeSpeed(this.newSpeed);
	}
	
}
