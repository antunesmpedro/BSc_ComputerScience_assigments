package sonc.battle;

/**
 * This class integrates the concrete part of the Command design pattern. It defines a rotation executed by the rotate() method, that is delayed until the Ship.move() command is completed. This ensures that a single command is executed per turn.
 * @author
 */

public class RotateCommand implements ShipCommand {
	double rotationAngle;
	Ship shipToRotate;
	
	/**
	 * Create a RotateCommand from given data
	 * @param ship - that is rotated
	 * @param delta - rotation angle
	 */
	RotateCommand(Ship ship, double delta) { 
		this.shipToRotate = ship;
		this.rotationAngle = delta;
	}
	
	/**
	 * <b>Specified by:</b> execute in interface <i>ShipCommand</i>
	 */
	
	public void execute() {
		this.shipToRotate.doRotate(this.rotationAngle); 
	}
}
