package pack.client;

import com.google.gwt.core.client.EntryPoint;
import com.google.gwt.core.client.GWT;
import com.google.gwt.user.client.ui.Panel;
import com.google.gwt.user.client.ui.RootPanel;
import com.google.gwt.user.client.ui.TextArea;

public class Trab3 implements EntryPoint {

	/**
	 * Create a remote service proxy to talk to the server-side Greeting service.
	 */
	private final PackServiceAsync packService = GWT.create(PackService.class);
	
	public void onModuleLoad() {
		
		Panel divA = RootPanel.get("divA");
		Panel divE = RootPanel.get("divE");
		Panel body = RootPanel.get();
		
		AuthenticatorPanel panelA = new AuthenticatorPanel(packService, body, divE);
		divA.add(panelA.authenticatorPanel);
		
	}
}