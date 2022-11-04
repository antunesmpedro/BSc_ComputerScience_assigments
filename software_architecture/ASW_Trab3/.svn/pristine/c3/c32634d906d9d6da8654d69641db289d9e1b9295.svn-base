package sonc.client;

import com.google.gwt.dom.client.Style.Display;
import com.google.gwt.event.dom.client.ClickEvent;
import com.google.gwt.event.dom.client.ClickHandler;
import com.google.gwt.user.client.DOM;
import com.google.gwt.user.client.rpc.AsyncCallback;
import com.google.gwt.user.client.ui.Button;
import com.google.gwt.user.client.ui.FlowPanel;
import com.google.gwt.user.client.ui.Label;
import com.google.gwt.user.client.ui.PasswordTextBox;
import com.google.gwt.user.client.ui.PopupPanel;
import com.google.gwt.user.client.ui.RootPanel;
import com.google.gwt.user.client.ui.TextArea;
import com.google.gwt.user.client.ui.TextBox;

import sonc.shared.SoncException;

public class CommandPanel {
	final FlowPanel commandPanel = new FlowPanel();
	
	public CommandPanel(final SoncServiceAsync soncService, AuthenticatorPanel panelA, TextArea editor) {
		this.commandPanel.setSize("100%", "400px");
		this.commandPanel.setStyleName("commandPanel");
		
		Button appearUpdatePasswordButton = new Button("Update Password");
		appearUpdatePasswordButton.setSize("100%", "80px");
		
		FlowPanel updatePasswordPanel = new FlowPanel();
		updatePasswordPanel.setSize("300px", "200px");
		Label nameLabel = new Label("Nick:");
		nameLabel.setSize("300px", "50px");
		TextBox nameField = new TextBox();
		nameField.setSize("290px", "50px");
		Label passwordLabel = new Label("Password:");
		passwordLabel.setSize("300px", "50px");
		PasswordTextBox passwordField = new PasswordTextBox();
		passwordField.setSize("290px", "50px");
		Label newPasswordLabel = new Label("New Password:");
		newPasswordLabel.setSize("300px", "50px");
		PasswordTextBox newPasswordField = new PasswordTextBox();
		newPasswordField.setSize("290px", "50px");
		final Button updatePasswordButton = new Button("Update Password");
		updatePasswordPanel.setSize("300px", "50px");
		updatePasswordPanel.add(nameLabel);
		updatePasswordPanel.add(nameField);
		updatePasswordPanel.add(passwordLabel);
		updatePasswordPanel.add(passwordField);
		updatePasswordPanel.add(newPasswordLabel);
		updatePasswordPanel.add(newPasswordField);
		updatePasswordPanel.add(updatePasswordButton);
		RootPanel.get("divU").add(updatePasswordPanel);
		
		
		Button logoutButton = new Button("Logout");
		logoutButton.setSize("100%", "80px");
		Button compileButton = new Button("Compile");
		compileButton.setSize("100%", "80px");
		Button getCodeButton = new Button("Get Code");
		getCodeButton.setSize("100%", "80px");
		Button battleButton = new Button("Battle");
		battleButton.setSize("100%", "80px");
		this.commandPanel.add(appearUpdatePasswordButton);
		this.commandPanel.add(logoutButton);
		this.commandPanel.add(compileButton);
		this.commandPanel.add(getCodeButton);
		this.commandPanel.add(battleButton);
		
		
		battleButton.addClickHandler(new ClickHandler() {
            public void onClick(ClickEvent event) {
				final PopupPanel popup = new PopupPanel();
				popup.setWidget(new Label("Not Implemented"));
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
				RootPanel.get().add(popup);
			}
		});
		
		appearUpdatePasswordButton.addClickHandler(new ClickHandler() {
			public void onClick(ClickEvent event) {
				DOM.getElementById("divU").getStyle().setDisplay(Display.BLOCK);
				DOM.getElementById("divA").getStyle().setDisplay(Display.NONE);
				DOM.getElementById("divE").getStyle().setDisplay(Display.NONE);
				DOM.getElementById("divC").getStyle().setDisplay(Display.NONE);	
			}
		});
		
		updatePasswordButton.addClickHandler(new ClickHandler() {
			public void onClick(ClickEvent event) {
							try {
								soncService.updatePassword(nameField.getValue(), passwordField.getValue(), newPasswordField.getValue(), new AsyncCallback<Boolean>() {
									@Override
									public void onSuccess(Boolean result) {
										
										DOM.getElementById("divU").getStyle().setDisplay(Display.NONE);
										DOM.getElementById("divE").getStyle().setDisplay(Display.BLOCK);
										DOM.getElementById("divC").getStyle().setDisplay(Display.BLOCK);
										
										if(result) {
											final PopupPanel popup = new PopupPanel();
											popup.setWidget(new Label("Password updated with sucess!"));
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
											RootPanel.get().add(popup);
										}
										else {
											final PopupPanel popup = new PopupPanel();
											popup.setWidget(new Label("Couldn't update the password"));
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
											RootPanel.get().add(popup);
										}
									}
									
									@Override
									public void onFailure(Throwable caught) {
										final PopupPanel popup = new PopupPanel();
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
										RootPanel.get().add(popup);
									}
								});
							} catch (SoncException e) {
								e.printStackTrace();
							}
			}
		});
		
		
		logoutButton.addClickHandler(new ClickHandler() {
			public void onClick(ClickEvent event) {
				panelA.nick = "";
				panelA.password = "";
				editor.setText("");
				DOM.getElementById("divA").getStyle().setDisplay(Display.BLOCK);
				DOM.getElementById("divE").getStyle().setDisplay(Display.NONE);
				DOM.getElementById("divC").getStyle().setDisplay(Display.NONE);	
				DOM.getElementById("divU").getStyle().setDisplay(Display.NONE);	
			}
		});
		
		getCodeButton.addClickHandler(new ClickHandler() {
			public void onClick(ClickEvent event) {
				try {
					soncService.getCurrentCode(panelA.nick, panelA.password, new AsyncCallback<String>() {
						@Override
						public void onSuccess(String result) {
							editor.setText(result);
						}
						
						@Override
						public void onFailure(Throwable caught) {
							final PopupPanel popup = new PopupPanel();
							popup.setWidget(new Label(caught.getMessage()));
							popup.setVisible(true);
							popup.center();
							popup.setAutoHideEnabled(true);
							Button ok = new Button("OK");;
					         ok.addClickHandler(new ClickHandler() {
					            public void onClick(ClickEvent event) {
					               popup.hide(true);
					            }
					         });
							popup.add(ok);
							RootPanel.get().add(popup);
						}
					});
				} catch (SoncException e) {
					e.printStackTrace();
				}
			}
		});
		
		compileButton.addClickHandler(new ClickHandler() {
			public void onClick(ClickEvent event) {
						try {
							soncService.buildShip(panelA.nick, panelA.password, editor.getText() , new AsyncCallback<Void>() {

								@Override
								public void onFailure(Throwable caught) {
									final PopupPanel popup = new PopupPanel();
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
									RootPanel.get().add(popup);
								}

								@Override
								public void onSuccess(Void result) {
									final PopupPanel popup = new PopupPanel();
									popup.setWidget(new Label("Instantiation of Ship done"));
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
									RootPanel.get().add(popup);
								}
							});
						} catch (SoncException e) {
							final PopupPanel popup = new PopupPanel();
							popup.setWidget(new Label("Couldn't Compile"));
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
							RootPanel.get().add(popup);
							e.printStackTrace();
						}
			}
		});
	}
}
