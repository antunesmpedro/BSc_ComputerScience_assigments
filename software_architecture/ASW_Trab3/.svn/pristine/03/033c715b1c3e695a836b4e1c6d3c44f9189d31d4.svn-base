package sonc.client;

import com.google.gwt.dom.client.Style.Display;
import com.google.gwt.event.dom.client.ClickEvent;
import com.google.gwt.event.dom.client.ClickHandler;
import com.google.gwt.user.client.DOM;
import com.google.gwt.user.client.rpc.AsyncCallback;
import com.google.gwt.user.client.ui.Button;
import com.google.gwt.user.client.ui.Composite;
import com.google.gwt.user.client.ui.DeckLayoutPanel;
import com.google.gwt.user.client.ui.FlowPanel;
import com.google.gwt.user.client.ui.Label;
import com.google.gwt.user.client.ui.PasswordTextBox;
import com.google.gwt.user.client.ui.PopupPanel;
import com.google.gwt.user.client.ui.RootPanel;
import com.google.gwt.user.client.ui.TextBox;

import sonc.shared.SoncException;

public class AuthenticatorPanel extends Composite {
	final FlowPanel authenticatorPanel = new FlowPanel();
	String nick = "";
	String password = "";
	
	public AuthenticatorPanel(final SoncServiceAsync soncService) {
				
		this.authenticatorPanel.setSize("300px", "250px");
		
		// Appearance Buttons
		Button appearRegisterButton = new Button("Show register");
		Button appearLoginButton = new Button("Show login");
		appearRegisterButton.setSize("150px", "50px");
		appearLoginButton.setSize("150px", "50px");
		this.authenticatorPanel.add(appearRegisterButton);
		this.authenticatorPanel.add(appearLoginButton);
		
		// Panels that will replace the two deckPanels because we need to organize the items inside
		FlowPanel registerPanel = new FlowPanel();
		registerPanel.setSize("300px", "200px");
		FlowPanel loginPanel = new FlowPanel();
		loginPanel.setSize("300px", "200px");
		
		// Register Buttons and textBoxes
		TextBox nameFieldRegister = new TextBox();
		nameFieldRegister.setSize("290px", "50px");
		PasswordTextBox passwordFieldRegister = new PasswordTextBox();
		passwordFieldRegister.setSize("290px", "50px");;
		final Button registerButton = new Button("register");
		registerButton.setSize("300px", "50px");
		registerPanel.add(nameFieldRegister);
		registerPanel.add(passwordFieldRegister);
		registerPanel.add(registerButton);
		
		// Login Buttons and textBoxes
		TextBox nameFieldLogin = new TextBox();
		nameFieldLogin.setSize("290px", "50px");
		PasswordTextBox passwordFieldLogin = new PasswordTextBox();
		passwordFieldLogin.setSize("290px", "50px");;
		final Button loginButton = new Button("login");
		loginButton.setSize("300px", "50px");
		loginPanel.add(nameFieldLogin);
		loginPanel.add(passwordFieldLogin);
		loginPanel.add(loginButton);
		
		
		// Add the DeckPanels
		final DeckLayoutPanel deck = new DeckLayoutPanel();
		deck.setSize("300px", "200px");
		deck.setStyleName("deck");
		deck.add(registerPanel);
		deck.add(loginPanel);
		this.authenticatorPanel.add(deck);
		deck.showWidget(0);
		
		
		
		appearRegisterButton.addClickHandler(new ClickHandler() {
			
			public void onClick(ClickEvent event) {
				nameFieldRegister.setText("");
				passwordFieldRegister.setText("");
				deck.showWidget(0);
			}
		});
		

		appearLoginButton.addClickHandler(new ClickHandler() {
			
			public void onClick(ClickEvent event) {
				nameFieldRegister.setText("");
				passwordFieldRegister.setText("");
				deck.showWidget(1);
			}
		});
		
		
		/**
		  * When the registerButton is pressed, it tries to register, if the service doesn't contain that username, success
		  * otherwise a message is shown saying that user is already registered.
		 */
		registerButton.addClickHandler(new ClickHandler() {
			public void onClick(ClickEvent event) {
							try {
								soncService.register(nameFieldRegister.getValue(), passwordFieldRegister.getValue(), new AsyncCallback<Boolean>() {
									@Override
									public void onSuccess(Boolean result) {
										System.out.println("here");
										if(result == true) {
											nameFieldRegister.setText("");
											passwordFieldRegister.setText("");
											deck.showWidget(1);						
										}
										else {
											nameFieldRegister.setText("");
											passwordFieldRegister.setText("");
											
											
											final PopupPanel popup = new PopupPanel();
											popup.setWidget(new Label("Couldn't Register"));
											popup.setVisible(true);
											popup.center();
											popup.setAutoHideEnabled(true);
											Button ok = new Button("OK");
									         ok.addClickHandler(new ClickHandler() {
									            public void onClick(ClickEvent event) {
									               popup.hide(true);
									            }
									         });
											popup.add(ok);
											RootPanel.get("divA").add(popup);
										}
									}
									
									@Override
									public void onFailure(Throwable caught) {
										final PopupPanel popup = new PopupPanel();
										popup.setAutoHideEnabled(true);
										popup.setWidget(new Label(caught.getMessage()));
										popup.setVisible(true);
										popup.center();
										popup.setAutoHideEnabled(true);
										Button ok = new Button("OK");
								         ok.addClickHandler(new ClickHandler() {
								            public void onClick(ClickEvent event) {
								               popup.hide(true);
								            }
								         });
										popup.add(ok);
										RootPanel.get("divA").add(popup);
									}
								});
							} catch (SoncException e) {
								e.printStackTrace();
							}
			}
		});
		
		loginButton.addClickHandler(new ClickHandler() {
			public void onClick(ClickEvent event) {
						soncService.authenticate(nameFieldLogin.getValue(), passwordFieldLogin.getValue(), new AsyncCallback<Boolean>() {
							@Override
							public void onSuccess(Boolean result) {
								System.out.println("here");
								if(result == true) {
									nick = nameFieldLogin.getValue();
									password = passwordFieldLogin.getValue();
									nameFieldLogin.setText("");
									passwordFieldLogin.setText("");
									
									DOM.getElementById("divA").getStyle().setDisplay(Display.NONE);
									DOM.getElementById("divE").getStyle().setDisplay(Display.BLOCK);
									DOM.getElementById("divC").getStyle().setDisplay(Display.BLOCK);							
								}
								else {
									passwordFieldLogin.setText("");
									final PopupPanel popup = new PopupPanel();
									popup.setWidget(new Label("Couldn't Login"));
									popup.setVisible(true);
									popup.center();
									popup.setAutoHideEnabled(true);
									Button ok = new Button("OK");
							         ok.addClickHandler(new ClickHandler() {
							            public void onClick(ClickEvent event) {
							               popup.hide(true);
							            }
							         });
									popup.add(ok);
									RootPanel.get("divA").add(popup);
								}
							}
							
							@Override
							public void onFailure(Throwable caught) {
								final PopupPanel popup = new PopupPanel();
								popup.setAutoHideEnabled(true);
								popup.setWidget(new Label(caught.getMessage()));
								popup.setVisible(true);
								popup.center();
								popup.setAutoHideEnabled(true);
								Button ok = new Button("OK");
						         ok.addClickHandler(new ClickHandler() {
						            public void onClick(ClickEvent event) {
						               popup.hide(true);
						            }
						         });
								popup.add(ok);
								RootPanel.get("divA").add(popup);
							}
						});
			}
		});
	}
}
