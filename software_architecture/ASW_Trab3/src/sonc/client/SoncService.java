package sonc.client;

import java.util.List;

import com.google.gwt.user.client.rpc.RemoteService;
import com.google.gwt.user.client.rpc.RemoteServiceRelativePath;

import sonc.shared.Movie;
import sonc.shared.SoncException;

@RemoteServiceRelativePath("sonc")
public interface SoncService extends RemoteService {

	boolean authenticate(String nick, String password);

	boolean register(String userId, String password) throws SoncException;

	boolean updatePassword(String nick, String oldPassword, String newPassword) throws SoncException;

	void buildShip(String nick, String password, String code) throws SoncException;

	String getCurrentCode(String nick, String password) throws SoncException;
	
	//Movie battle(List<String> nicks) throws SoncException;
}