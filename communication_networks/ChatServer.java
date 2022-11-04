import java.io.*;
import java.net.*;
import java.nio.*;
import java.nio.channels.*;
import java.nio.charset.*;
import java.util.*;

class Client{
  private SocketChannel sc;
  private String username;
  private String status;
  private String channel;

  public Client(SocketChannel sc){
    this.sc = sc;
    this.username="UNKNOWN";
    this.status = "init";
    this.channel = "";
  }

  public void changeUsername(String name) {
    if (this.username.equals("UNKNOWN"))
      status = "outside";
    System.out.println(this.username + " changed to " + name);
    //broadcast NEWNICK to everyone
    this.username = name;
  }

  public void setStatus(String stat) {
    this.status = stat;
  }

  public void setChannel(String channel) {
    this.channel = channel;
    if(channel != "") 
      status = "inside";
    else status = "outside";
  }

  public String getUsername() {
    return username;
  }

  public String getStatus() {
    return status;
  }

  public String getChannel() {
    return channel; 
  }

  public SocketChannel getSocket() {
    return sc;
  }
}

class Channel{

  private String name;
  private LinkedList<Client> clients;

  public Channel(String name){
    this.name = name;
    clients = new LinkedList<>();
  }

  public void removeClient(Client client) {
    client.setChannel("");
    clients.remove(client);
    System.out.println(client.getUsername() + " left " + this.name); // configurar
    //DELETED SOME ThINGS
  }

  public void addClient(Client client) {
    client.setChannel(this.name);
    System.out.println(client.getUsername() + " joined " + this.name);
  }

  public String getName() {
    return name;
  }

  public LinkedList<Client> getClients() {
    return clients;
  }

}

public class ChatServer {
  // A pre-allocated buffer for the received data
  static private final ByteBuffer buffer = ByteBuffer.allocate( 16384 );

  // Decoder for incoming text -- assume UTF-8
  static private final Charset charset = Charset.forName("UTF8");
  static private final CharsetDecoder decoder = charset.newDecoder();
  static private final CharsetEncoder encoder = charset.newEncoder();
  static LinkedList<Client> clients = new LinkedList<>();
  static LinkedList<Channel> channels = new LinkedList<>();
  static private String message = "";
  static private Client returnClient(SocketChannel sc){
    if(clients.isEmpty()) return null;
    for(int i = 0; i<clients.size(); i++)
      if(clients.get(i).getSocket() == sc) return clients.get(i);
    return null;
  }


  static private Client getClient(String username){
    for(int i=0; i<clients.size(); i++) {
      if(clients.get(i).getUsername().equals(username)) 
        return clients.get(i);
    }
    return null;
  }

  static private Channel checkChannel(String channel) {
    if(channels.isEmpty()) 
      return null;
    for(int i=0; i<channels.size(); i++){
      if(channels.get(i).getName() == channel)
        return channels.get(i);
    }
    return null;
  }

  static private  Channel addChannel(Channel channel) {
    channels.add(channel);
    System.out.println("Created channel:" + channel);
    return null;

  }

  static private Channel removeChannel(Channel channel) {
    System.out.println("removed channel: " + channel);
    channels.remove(channel);
    return null;

  }


    // Just read the message from the socket and send it to stdout
  static private boolean processInput( SocketChannel sc ) throws IOException {
    // Read the message to the buffer
    buffer.clear();
    sc.read( buffer );
    buffer.flip();

    // If no data, close the connection
    if (buffer.limit()==0) {
      return false;
    }

  // Creates temporary client
    Client temporary_client = returnClient(sc);
    if(temporary_client == null) {
      temporary_client = new Client(sc);
      clients.push(temporary_client);
      System.out.println("[INFO] New client created.");
    }

    // Decode and print the message to stdout
    String message = decoder.decode(buffer).toString();
    if(message.contains("\n")) {
      System.out.print("MESSAGEM CRL:" + message);
      processMessage(temporary_client, message);
      message = "";
    }
    return true;
  }

  static private void processMessage(Client client, String message) throws CharacterCodingException, IOException {
    String[] split_message = message.split(" ");
    boolean is_command = (split_message[0].charAt(0) == '/' && split_message[0].charAt(1) != '/');

  //handling commands 
    if(is_command) {
      switch(split_message[0]) {

        case("/nick"):
        if (split_message[1] == null) {
          broadcast(client, "ERROR");
        }
        else if(getClient(split_message[1]) != null) {
          client.changeUsername(split_message[1]);
          broadcast(client, "OK");
        }
        break;

        case("/join"):
        if(client.getStatus().equals("init")) {
         broadcast(client, "ERROR");
       }
       if(!(client.getChannel().isEmpty())) {
//broadcast to every client in room that client LEFT
        checkChannel(client.getChannel()).removeClient(client);
      }
      if (checkChannel(split_message[1]) != null) {
        Channel temp_channel = new Channel(split_message[1]);
        channels.add(temp_channel);
        temp_channel.addClient(client);
        client.setStatus("inside");
        broadcast(client, "OK");
//broadcast to everyone in new ROOM
      }
      break;

      case("/leave"):
      if(client.getChannel().isEmpty() || client.getChannel() == null) {
        broadcast(client, "ERROR");
      }
      else{
        checkChannel(client.getChannel()).removeClient(client);
        broadcast(client, "OK");
        client.setStatus("outside");
      }
      break;

      case("/bye"):
      if (checkChannel(client.getChannel()) != null) {
        broadcast(client, "BYE");
  //broadcast CLIENT BYED
        checkChannel(client.getChannel()).removeClient(client);
      }
      broadcast(client, "BYE");
      clients.remove(client);
      System.out.println("Closed connection from: " + client.getSocket().socket());     
      client.getSocket().close();
      break;

      default: 
      broadcast(client, "ERROR");
      break;
    }
  }

}

static private void broadcast(Client client, String msg) throws CharacterCodingException, IOException {
  client.getSocket().write(encoder.encode(CharBuffer.wrap(msg + "\n")));
  return;
}

static private void broadcastRoom(Client client, String msg) throws CharacterCodingException, IOException {
 Channel ch = checkChannel(client.getChannel());
 for(int i=0; i < ch.getClients().size(); i++ ) {
  if((message.startsWith("MESSAGE") && ch.getClients().get(i) == client) || (ch.getClients().get(i) != client))
    ch.getClients().get(i).getSocket().write(encoder.encode(CharBuffer.wrap(msg+"\n")));
}
return;
}



static public void main( String args[] ) throws Exception {
    // Parse port from command line
  int port = Integer.parseInt( args[0] );

  try {
      // Instead of creating a ServerSocket, create a ServerSocketChannel
    ServerSocketChannel ssc = ServerSocketChannel.open();

      // Set it to non-blocking, so we can use select
    ssc.configureBlocking( false );

      // Get the Socket connected to this channel, and bind it to the
      // listening port
    ServerSocket ss = ssc.socket();
    InetSocketAddress isa = new InetSocketAddress( port );
    ss.bind( isa );

      // Create a new Selector for selecting
    Selector selector = Selector.open();

      // Register the ServerSocketChannel, so we can listen for incoming
      // connections
    ssc.register( selector, SelectionKey.OP_ACCEPT );
    System.out.println( "Listening on port "+port );

    while (true) {
        // See if we've had any activity -- either an incoming connection,
        // or incoming data on an existing connection
      int num = selector.select();

        // If we don't have any activity, loop around and wait again
      if (num == 0) {
        continue;
      }

        // Get the keys corresponding to the activity that has been
        // detected, and process them one by one
      Set<SelectionKey> keys = selector.selectedKeys();
      Iterator<SelectionKey> it = keys.iterator();
      while (it.hasNext()) {
          // Get a key representing one of bits of I/O activity
        SelectionKey key = it.next();

          // What kind of activity is it?
        if ((key.readyOps() & SelectionKey.OP_ACCEPT) ==
          SelectionKey.OP_ACCEPT) {

            // It's an incoming connection.  Register this socket with
            // the Selector so we can listen for input on it
          Socket s = ss.accept();
        System.out.println( "Got connection from "+s );

            // Make sure to make it non-blocking, so we can use a selector
            // on it.
        SocketChannel sc = s.getChannel();
        sc.configureBlocking( false );

            // Register it with the selector, for reading
        sc.register( selector, SelectionKey.OP_READ );

      } else if ((key.readyOps() & SelectionKey.OP_READ) ==
        SelectionKey.OP_READ) {

        SocketChannel sc = null;

        try {

              // It's incoming data on a connection -- process it
          sc = (SocketChannel)key.channel();
          boolean ok = processInput( sc );

              // If the connection is dead, remove it from the selector
              // and close it
          if (!ok) {
            key.cancel();

            Socket s = null;
            try {
              s = sc.socket();
              System.out.println( "Closing connection to "+s );
              s.close();
            } catch( IOException ie ) {
              System.err.println( "Error closing socket "+s+": "+ie );
            }
          }

        } catch( IOException ie ) {

              // On exception, remove this channel from the selector
          key.cancel();

          try {
            sc.close();
          } catch( IOException ie2 ) { System.out.println( ie2 ); }

          System.out.println( "Closed "+sc );
        }
      }
    }

        // We remove the selected keys, because we've dealt with them.
    keys.clear();
  }
} catch( IOException ie ) {
  System.err.println( ie );
}
}



}