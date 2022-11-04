package sonc.battle;

public class FireCommand implements ShipCommand {
	World world;
	Ship ship;
	Munition typeMunition;
	
	/**
	 * Create a FireCommand from given data
	 * @param world - where munition will be created
	 * @param ship - that fires munition
	 * @param munition - to be fired (may be of different types)
	 */
	
	FireCommand(World world, Ship ship, Munition munition) {
		this.world = world;
		this.ship = ship;
		this.typeMunition = munition;
	}
	
	/**
	 *  <b>Specified by:</b> execute in interface <i>ShipCommand</i>
	 *  Method that executes the command. Arguments for command execution can be passed to the instance using the constructor
	 */
	
	public void execute() {
		this.ship.lastFireRound = this.world.getCurrentRound();
		this.world.addMovingObject(this.typeMunition);
	}
}
