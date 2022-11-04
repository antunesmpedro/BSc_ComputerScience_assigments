package sonc.game;

import java.io.Serializable;
import java.util.Set;
import java.util.Vector;
import java.util.List;
import java.util.Hashtable;
import java.util.Iterator;

/**
 * A collection of players, persisted on file. Contains methods for registration, authentication and
 * retrieving players and their names.
 * @author 
 */

public class Players implements Serializable {
	 private static final long serialVersionUID = 1L;
	 static Hashtable<String, Player> tablePlayers = new Hashtable<String, Player>();
	 
	public Players() {
	} 
	 
	 /**
	  * Register a player with given nick and password
	  * @param nick
	  * @param password
	  * @return true if registered and false otherwise
	  */
	 
	boolean register(String nick, String password) {
		if(nick.matches("[a-zA-Z0-9]+") && (!password.isEmpty())) {
			if(!tablePlayers.containsKey(nick)) { 
			 	Player player = new Player(nick, password);
			 	tablePlayers.put(nick, player);
			 	return true;
		 	}
		}
		return false;
	 }
	 
	boolean updatePassword(String nick, String oldPassword, String newPassword) { 
		if(tablePlayers.containsKey(nick)) {
			Player player = tablePlayers.get(nick);
			if(player.password.equals(oldPassword)) { 
				player.setPassword(newPassword);
				return true;
			}
		}
		return false;
	}
	 
	boolean authenticate(String nick, String password) {
		if(tablePlayers.containsKey(nick)) {
			Player player = tablePlayers.get(nick);
			return player.authenticate(password);
		}
		return false;
	}
	 
	Player getPlayer(String name) { return tablePlayers.get(name); }
	 
	 /**
	  * Produces a sorted list of players' names that have an instance of a ship.
	  * @return list of names as strings
	  */
	
	List<String> getPlayersNamesWithShips() { 
		Vector<String> playersWithShips = new Vector<String>(); // or ArrayList ?
		Set<String> keys = tablePlayers.keySet();
		Iterator<String> itr = keys.iterator();
		
		while(itr.hasNext()) {
			String key = itr.next();
			Player player = tablePlayers.get(key);
			if(player.instanceShip != null) playersWithShips.add(player.nick);
		}
		
		return playersWithShips;
	}
}
