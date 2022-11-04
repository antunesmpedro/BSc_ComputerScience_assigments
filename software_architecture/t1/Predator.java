package man;
import robocode.*;
//import robocode.util.Utils;
import java.awt.Color;

/**
 * 
 * nome do robo: Predator
 * @author Andre Rodrigues e Pedro Antunes
 *
 */



public class Predator extends AdvancedRobot {
	private double enemyRobotDistance;
	private int currentNumberOfPlayers = 0;
	private int burstCont = 0;
	private int hitCont = 0;
	private int bulletMissedCont = 0;
	
		// First function called by the robot
		public void run() {
			setBodyColor(Color.green.darker());
			setGunColor(Color.gray);
			setRadarColor(Color.gray);
			setBulletColor(Color.orange);
			setScanColor(Color.white);
			// Set the Radar to be independent of the Gun rotation
			//setAdjustRadarForGunTurn(false);
			
			// Robot main loop
			while (true) {
				currentNumberOfPlayers = getOthers();
				if(currentNumberOfPlayers == 1) setTurnRadarRight(Double.POSITIVE_INFINITY);
				else{
					spinMove();
				}
				execute();
			} 
		} 
		
		/**
		 *  Method that is called when our scan detects an enemy robot and where we define the strategies of our robot
		 */
		
		public void onScannedRobot(ScannedRobotEvent e){
			if(currentNumberOfPlayers == 1){
				lockTarget(e);
				if(bulletMissedCont < 3){
					fireFunction(e);
					scan();
				}
				else if(bulletMissedCont >= 3){ 
					bulletMissedCont = 0;
					double angleBodyNeedsTurn = getHeading() - getRadarHeading();
					turnLeft(angleBodyNeedsTurn);
					ahead(e.getDistance()/2);
				}
				else if(hitCont > 3){
					hitCont = 0;
					movePerpendicularToEnemy(e);
				}
				scan();
			}
			else{
				System.out.println("energy: " + e.getEnergy());
				if(e.getEnergy() < 30){
					lockTarget(e);
					/*if(bulletMissedCont < 4){
						System.out.println("fire");
						fireFunction(e);
						scan();
					}
					else{
						bulletMissedCont = 0;
						spinMove();
					} */
					for(int i = 3 ; i > 0 ; i--) fireFunction(e);
					scan();
				}
				else{ 
					System.out.println("fire");
					fire(3);
					spinMove();
				}
			}
		}
		
		public void onWin(WinEvent e){
			int i = 5;
			while(i > 0){
				turnRight(30);
				turnLeft(30);
				i--;
			}
		}
		
		public void onHitByBullet(HitByBulletEvent e){
			hitCont++;
		}
		
		public void onBulletMissed(BulletMissedEvent e){
			System.out.println("bullet missed");
			bulletMissedCont++;
		}
		
		public void onHitWall(HitWallEvent e){
			double bearing = e.getBearing();
			turnLeft(-bearing);
			ahead(100);
		}
		
		public void onHitRobot(HitRobotEvent e) {
			turnRight(e.getBearing());
			fire(3);
		}
		
		private void movePerpendicularToEnemy(ScannedRobotEvent e){
			turnLeft(90 - e.getBearing());
			ahead(100);
			back(100);
		}
		
		private void spinMove(){
			System.out.println("spin move");
			setAdjustRadarForGunTurn(false);
			double angleGunNeedsTurn = getGunHeading() - getRadarHeading();
			setTurnGunLeft(angleGunNeedsTurn);
			//setAdjustRadarForGunTurn(false);
			setTurnRight(400);
			setMaxVelocity(5);
			ahead(300);
			System.out.println("spin out");
		}
		
		/**
		 *  Method that implements a kind of burst weapon, instead of full auto
		 */
		
		private void fireFunction(ScannedRobotEvent e){
			if(burstCont < 2){
				fire(whatBulletToFire(e));
				burstCont++;
			}
			else if(burstCont < 8){
				burstCont++;
			}
			else burstCont = 0;
		}
		
		private int whatBulletToFire(ScannedRobotEvent e){
			enemyRobotDistance = e.getDistance();
			if (enemyRobotDistance > 200 || getEnergy() < 15) return 1;
			else if (enemyRobotDistance > 50) return 2;
			else return 3;
		}
		
		private void lockTarget(ScannedRobotEvent e){
			setAdjustRadarForGunTurn(true);
			double angleToEnemy = getHeadingRadians() + e.getBearingRadians();
			double angleRadarNeedsTurn = angleToEnemy - getRadarHeadingRadians();
			setTurnRadarRightRadians(angleRadarNeedsTurn);
			double angleGunNeedsTurn = getGunHeading() - getRadarHeading();
			setTurnGunLeft(angleGunNeedsTurn);
		}
}