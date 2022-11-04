package sonc.client;

import com.google.gwt.core.client.EntryPoint;
import com.google.gwt.core.client.GWT;
import com.google.gwt.user.client.ui.RootPanel;
import com.google.gwt.user.client.ui.TextArea;

public class ASW_Trab3 implements EntryPoint {

	/**
	 * Create a remote service proxy to talk to the server-side Greeting service.
	 */
	private final SoncServiceAsync soncService = GWT.create(SoncService.class);
	
	public void onModuleLoad() {
		
		AuthenticatorPanel panelA = new AuthenticatorPanel(soncService);
		RootPanel.get("divA").add(panelA.authenticatorPanel);
		
		// Definition Panel Editor of Code
		TextArea editor = new TextArea();
		editor.setStyleName("editor");
		editor.setVisible(true);
		RootPanel.get("divE").add(editor);
		
		CommandPanel panelC = new CommandPanel(soncService, panelA, editor);
		RootPanel.get("divC").add(panelC.commandPanel);
	}
}