package sonc.client;

import java.util.List;

import com.google.gwt.user.client.rpc.AsyncCallback;

import sonc.shared.Movie;
import sonc.shared.SoncException;

public interface SoncServiceAsync {
	
	// all methods need to return void and the callback function return the value defined on the Sync Class
	
	void authenticate(String nick, String password, AsyncCallback<Boolean> callback);

	void register(String userId, String password, AsyncCallback<Boolean> callback) throws SoncException;

	void updatePassword(String nick, String oldPassword, String newPassword, AsyncCallback<Boolean> callback) throws SoncException;

	void buildShip(String nick, String password, String code, AsyncCallback<Void> callback) throws SoncException;

	void getCurrentCode(String nick, String password, AsyncCallback<String> callback) throws SoncException;
	
	//void battle(List<String> nicks, AsyncCallback<Movie> callback) throws SoncException;
}