import java.io.*;
import java.net.*;
import java.util.*;
import java.awt.*;
import java.awt.event.*;
import javax.swing.*;


public class ChatClient {

    // Variáveis relacionadas com a interface gráfica --- * NÃO MODIFICAR *
	JFrame frame = new JFrame("Chat Client");
	private JTextField chatBox = new JTextField();
	private JTextArea chatArea = new JTextArea();
    // --- Fim das variáveis relacionadas coma interface gráfica

    // Se for necessário adicionar variáveis ao objecto ChatClient, devem
    // ser colocadas aqui
	Socket clientSocket;
	DataOutputStream outToServer;
	BufferedReader inFromServer;
	String username;
	String channel;
	String prevMessage;
	String print;

    // Método a usar para acrescentar uma string à caixa de texto
    // * NÃO MODIFICAR *
	public void printMessage(final String message) {
		chatArea.append(message + "\n");
	}


    // Construtor
	public ChatClient(String server, int port) throws IOException {

        // Inicialização da interface gráfica --- * NÃO MODIFICAR *
		frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		JPanel panel = new JPanel();
		panel.setLayout(new BorderLayout());
		panel.add(chatBox);
		frame.setLayout(new BorderLayout());
		frame.add(panel, BorderLayout.SOUTH);
		frame.add(new JScrollPane(chatArea), BorderLayout.CENTER);
		frame.setSize(500, 300);
		frame.setVisible(true);
		chatArea.setEditable(false);
		chatBox.setEditable(true);
		chatBox.addActionListener(new ActionListener() {
			@Override
			public void actionPerformed(ActionEvent e) {
				try {
					newMessage(chatBox.getText());
				} catch (IOException ex) {
				} finally {
					chatBox.setText("");
				}
			}
		});
        // --- Fim da inicialização da interface gráfica

        // Se for necessário adicionar código de inicialização ao
        // construtor, deve ser colocado aqui
		boolean connect = false;
		try {
			clientSocket = new Socket(server,port);
			outToServer = new DataOutputStream(clientSocket.getOutputStream());
			inFromServer = new BufferedReader(new InputStreamReader(clientSocket.getInputStream(),"UTF-8"));
			connect = true;
		}
		finally { 
			if(connect) {
				frame.setTitle("ChatClient(" + server + ":" + port + ")");
				printMessage("Connected to " + server + ":" + port);
			}
			else {
				printMessage("Unable to connect to the server.");
			}
		}
	}


    // Método invocado sempre que o utilizador insere uma mensagem
    // na caixa de entrada
	public void newMessage(String message) throws IOException {
        // PREENCHER AQUI com código que envia a mensagem ao servidor
		prevMessage = message;
		message = message + "\n";
		byte [] msg = message.getBytes("UTF-8");
		outToServer.write(msg);
	}

	public void errorHandler(String error) { 
		String[] temp = prevMessage.split(" "); 
		switch(temp[0]) {
			
			case "/nick":
			if(error.equals("OK")) {
				username = temp[1];
				printMessage("<!> Username changed to " + username);
			}
			else if(error.equals("ERROR")) {
				printMessage("<!> Username null or already in use.");
			}
			break;

			case "/join":
			if(error.equals("OK")) {
				channel = temp[1];
				printMessage("<!> You joined channel #" + channel + ".");
			}
			else if(error.equals("ERROR") && username=="null") {
				printMessage("<!> Set a username before joining a channel.");
			}
			else {
				printMessage("<!> Channel Invalid.");
			}
			break;

			case "/leave":
			if(error.equals("OK")) {
				printMessage("<!> You left channel #" + channel + ".");
				channel = "";
			}
			else if(error.equals("ERROR")) {
				printMessage("<!> ou can't leave if you aint't in a channel.");
			}
			break;

			default:
			if(error.equals("ERROR")){
				if(temp[0].charAt(0) == '/') {
					printMessage("<!>Invalid command: " + temp[0]);
					break;
				}
				else if(username == null) {
					printMessage("<!> Please set your username before doing that!");
				}
				else if(channel == null) {
					printMessage("<!> Please join a channel before sending any message!");
				}
			}
			break;
		}
	}

    // Método principal do objecto
	public void run() throws IOException {
        // PREENCHER AQUI
		String tempLine; 
		while(!clientSocket.isClosed()) {
			if((tempLine = inFromServer.readLine()) != null) {
				String[] lineFromServer = tempLine.split(" ");
				String[] lineToServer = prevMessage.split(" ");
				System.out.println("Received " + tempLine);

				switch(lineFromServer[0]){
					case "OK":
					errorHandler("OK");
					break;
					
					case "ERROR":
					errorHandler("ERROR");
					break; 
					
					case "MESSAGE":
					print = "[" + channel + "] <" + lineFromServer[1] + "> -";
					for(int i = 2; i < lineFromServer.length ; i++){
						print += " " + lineFromServer[i];  
					}
					printMessage(print);
					break;

					case "NEWNICK":
					print ="<!> " + lineFromServer[1] + " changed username to: " + lineFromServer[2];
					printMessage(print);
					break;

					case "JOINED":
					print ="<!> " +  lineFromServer[1] + " joined the room";
					printMessage(print);
					break;

					case "LEFT":
					print ="<!> " +  lineFromServer[1] + " left the room";
					printMessage(print);
					break;

					case "BYE":
					printMessage("Disconnected from the server!");
					clientSocket.close();
					frame.dispose();
					break;
				}
			}
		}
	}



    // Instancia o ChatClient e arranca-o invocando o seu método run()
    // * NÃO MODIFICAR *
	public static void main(String[] args) throws IOException {
		ChatClient client = new ChatClient(args[0], Integer.parseInt(args[1]));
		client.run();
	}

}
