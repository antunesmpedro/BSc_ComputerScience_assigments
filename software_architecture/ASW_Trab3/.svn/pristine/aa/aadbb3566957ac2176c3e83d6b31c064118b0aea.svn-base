package sonc.game;

import java.io.Serializable;

import sonc.battle.Ship;
import sonc.shared.SoncException;
import sonc.utils.AgentBuilder;

/**
 * A player of the SonC game. An instance of this class records the player's authentication and the last code submitted.
 */

public class Player implements Serializable {
	private static final long serialVersionUID = 1L;
	String nick = null;
	String password = null;
	//String code = null;
	String code = "debug";
	Ship instanceShip = null;

	Player(String nick, String password) {
		this.nick = nick;
		this.password = password;
	}
	
	String getNick() { return this.nick; }
	
	void setNick(String nick) { this.nick = nick; }
	
	String getPassword() { return this.password; }
	
	public void setPassword(String password) { this.password = password; }
	
	String getCode() { return this.code; }
	
	void setCode(String code) { this.code = code; }
	
	/**
	 * Try to compile and instance the submitted code and report errors. It uses the AgentBuilder class.
	 * @throws IOException 
	 */
	
	void checkCode() throws SoncException {
		try {
			AgentBuilder builder = new AgentBuilder();
			this.instanceShip = builder.getInstance(Ship.class, this.code, "sonc.battle");
		}
		catch(Exception e) {
			this.instanceShip = null;
			throw new SoncException("error detected on checkCode", e);
		}
	}
	
	/**
	 * Make an instance of Ship after compiling and instancing the submitted code. This instance is stored in this class.
	 * @return Ship or null if exceptions occurred when compiling the code or instancing the class
	 */
	
	Ship instanceShip() throws SoncException {
		if((this.instanceShip == null) && (this.code != null)) { 
			checkCode();
		}
		return this.instanceShip;
	}
	
	boolean authenticate(String password) {
		if(this.password.equals(password)) return true;
		else return false;
	}
}
