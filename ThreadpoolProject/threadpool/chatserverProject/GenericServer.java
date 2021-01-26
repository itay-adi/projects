package il.co.ilrd.chat_server;

import il.co.ilrd.factory.Factory;

import java.io.ByteArrayInputStream;
import java.io.IOException;
import java.io.ObjectInputStream;
import java.net.InetSocketAddress;
import java.net.SocketAddress;
import java.nio.ByteBuffer;
import java.nio.channels.ClosedSelectorException;
import java.nio.channels.DatagramChannel;
import java.nio.channels.SelectionKey;
import java.nio.channels.Selector;
import java.nio.channels.ServerSocketChannel;
import java.nio.channels.SocketChannel;
import java.util.HashMap;
import java.util.Iterator;
import java.util.Map;
import java.util.Scanner;
import java.util.Set;

public class GenericServer {
	private final MessageHandler msgHandler = new MessageHandler();
	private final ConnectionHandler connectionHandler;
	private final int TIMEOUT = 6000;
	private final int CAPACITY = 1024;
	private int version = 1;
	private boolean isServerRunning = true;

	public static void main(String[] args) {
		GenericServer myServer = new GenericServer();

		myServer.addConnection(45454, ConnectionType.TCP);
		myServer.addConnection(40153, ConnectionType.UDP);
		myServer.addConnection(40154, ConnectionType.BROADCAST);

		myServer.startServer();
	}

	public GenericServer() {
		connectionHandler = new ConnectionHandler();
		//msgHandler.addProtocol(ProtocolType.PINGPONG, new PingPongProtocol());
		msgHandler.addProtocol(ProtocolType.CHAT, new ChatProtocol());
	}

	public void addConnection(int port, ConnectionType type) {
		connectionHandler.addConnection(port, type);
	}

	public void removeConnection(int port, ConnectionType type) {
		connectionHandler.removeConnection(port, type);
	}

	public void startServer() {
		connectionHandler.startConnections();
	}

	public void closeServer() {
		connectionHandler.stopConnections();
		isServerRunning = false;
	}

	private class ExitThread implements Runnable {
		private Scanner scanner = new Scanner(System.in);

		@Override
		public void run() {
			while(!scanner.nextLine().equalsIgnoreCase("exit")) {
				System.out.println("Press 'exit' to stop the server");
			}

			closeServer();
		}
	}

	private class ConnectionHandler implements Runnable {
		private Factory<ConnectionType, Connection, Integer> connectionFactory = new Factory<>();
		private Map<Integer, Connection> connectionMap = new HashMap<>();

		public Selector selector;

		public ConnectionHandler() {
			try {
				initFactory();
				selector = Selector.open();
			} catch (IOException e) {
				e.printStackTrace();
			}
		}

		@Override
		public void run() {
			selectorStart();
		}

		private void selectorStart() {
			while(isServerRunning) {
				assert selector != null;
				// Wait for a client to connect
				try {
					while ((selector.select(TIMEOUT)) == 0) {
						//System.out.println("Selector waiting for a client to connect");
					}
					
					// Get the SelectionKey objects for the channels
					Set<SelectionKey> keys = selector.selectedKeys();
					Iterator<SelectionKey> keyiter = keys.iterator();
					// Iterate through the Set of keys
					while(keyiter.hasNext()) {
						// Get the Connection associated with the key
						SelectionKey key = keyiter.next();
						Connection con = (Connection) key.attachment();

						// Now test the key and the channel to find out
						// whether something happened
						if(key.isAcceptable()) {
							TCPServerConnection tcpServerCon = (TCPServerConnection)con;
							tcpServerCon.acceptConnection();
						}

						else if(key.isReadable()) {
							SendableConnection sendCon = (SendableConnection)key.attachment();
							sendCon.receiveMsg();
						}

						keyiter.remove();
					}
					
				} catch (Exception e1) {
					if(e1 instanceof ClosedSelectorException) {
						System.out.println("Server has stopped. Thank you Bye-Bye");
					}
					
					else {
						System.out.println("something went wrong");
						e1.printStackTrace();
					}
				}		
			}			
		}

		private void initFactory() {
			connectionFactory.add(ConnectionType.TCP, TCPServerConnection::new);
			connectionFactory.add(ConnectionType.UDP, UDPConnection::new);
			connectionFactory.add(ConnectionType.BROADCAST, UDPConnection::new);
		}

		public void addConnection(int port, ConnectionType type) {
			Connection connection = connectionFactory.create(type, port);
			connectionMap.put(connection.getId(), connection);
		}

		public void removeConnection(int connectionID, ConnectionType type) {
			connectionMap.remove(connectionID);
		}

		public void startConnections() {
			for(Map.Entry<Integer, Connection> connection : connectionMap.entrySet()) {
				connection.getValue().initConnection();
			}

			new Thread (new ExitThread()).start();
			new Thread (this).start();
		}

		public void stopConnections() {
			try {
				selector.close();
				for(Connection connection : connectionMap.values()) {
					connection.stopConnection();
				}
			} catch (IOException e) {
				e.printStackTrace();
			}

		}

		/*********************TCPServer*********************/
		private class TCPServerConnection implements Connection {
			private	ServerSocketChannel tcpChannel;
			private SocketAddress tpcLocalPort;
			private SocketChannel clientSocket;
			private TCPConnection clientConnection;
			private int port;
			private Integer connectionId;

			public TCPServerConnection(int port) {
				this.port = port;
				
				synchronized (connectionHandler) {
					++version;
					connectionId = version;
				}
			}

			public void acceptConnection() {
				try {
					clientSocket = tcpChannel.accept();
					clientConnection = new TCPConnection(clientSocket);
					clientConnection.initConnection();
					connectionMap.put(port, clientConnection);
				} catch (IOException e) {
					e.printStackTrace();
				}
			}

			@Override
			public void initConnection() {
				try {
					tcpChannel = ServerSocketChannel.open();
					tpcLocalPort = new InetSocketAddress("localhost", port);//Arik
					tcpChannel.socket().bind(tpcLocalPort);
					tcpChannel.configureBlocking(false);
					tcpChannel.register(selector, SelectionKey.OP_ACCEPT, this);
				} catch (IOException e) {
					e.printStackTrace();
				};
			}

			@Override
			public void stopConnection() {
				try {
					tcpChannel.close();
				} catch (IOException e) {
					e.printStackTrace();
				}
			}
			
			@Override
			public int getId() {
				return connectionId;
			}
		}

		/*********************TCPClient*********************/
		private class TCPConnection implements SendableConnection {
			private SocketChannel clientSocket;
			private Integer connectionId;

			public TCPConnection(SocketChannel clientSocket) {
				this.clientSocket = clientSocket;
				
				synchronized (connectionHandler) {
					++version;
					connectionId = version;
				}
			}

			@Override
			public void initConnection() {
				try {
					clientSocket.configureBlocking(false);
					clientSocket.register(selector, SelectionKey.OP_READ, this);
				} catch (IOException e) {
					e.printStackTrace();
				}
			}

			@Override
			public void stopConnection() {
				try {
					clientSocket.close();
				} catch (IOException e) {
					e.printStackTrace();
				}
			}

			@Override
			public void sendMsg(ByteBuffer buffer) {
				try {
					clientSocket.write(buffer);
					buffer.clear();
				} catch (IOException e) {
					e.printStackTrace();
				}
			}

			@Override
			public void receiveMsg() {
				ByteBuffer tcpReceivedBuffer  = ByteBuffer.allocate(CAPACITY);;

				try {
					if(clientSocket.read(tcpReceivedBuffer) == -1) {
						stopConnection();
						tcpReceivedBuffer.clear();
						return;
					}

					msgHandler.extractAndExecuteProtocol(this, tcpReceivedBuffer);
					System.out.println(intoServerMessage(tcpReceivedBuffer).getData().getData());
					tcpReceivedBuffer.clear();
				} catch (IOException | ClassNotFoundException e) {
					e.printStackTrace();
				}				
			}
			
			@Override
			public int getId() {
				return connectionId;
			}
		}

		/*********************UDPServer*********************/
		private class UDPConnection implements SendableConnection{
			private int port;
			private DatagramChannel udpChannel = null;
			private SocketAddress socketAddress = null;
			private Integer connectionId;

			public UDPConnection(int port) {
				this.port = port;
				
				synchronized (connectionHandler) {
					version++;
					connectionId = version;
				}
			}

			@Override
			public void initConnection() {
				try {
					udpChannel = DatagramChannel.open();
					SocketAddress datagramSocketAddress = new InetSocketAddress("localhost", port);
					udpChannel.socket().bind(datagramSocketAddress);
					udpChannel.configureBlocking(false);
					udpChannel.register(selector, SelectionKey.OP_READ, this);
				} catch (IOException e) {
					e.printStackTrace();
				}			
			}

			@Override
			public void sendMsg(ByteBuffer buffer) {
				try {
					udpChannel.send(buffer, socketAddress);
					buffer.clear();
				} catch (IOException e) {
					e.printStackTrace();
				}
			}

			@Override
			public void receiveMsg() {
				try {
					ByteBuffer udpReceivedBuffer = ByteBuffer.allocate(CAPACITY);
					socketAddress = udpChannel.receive(udpReceivedBuffer);
					msgHandler.extractAndExecuteProtocol(this, udpReceivedBuffer);
					System.out.println(intoServerMessage(udpReceivedBuffer).getData().getData());
					udpReceivedBuffer.clear();
				} catch (IOException | ClassNotFoundException e) {
					e.printStackTrace();
				}	
			}

			@Override
			public void stopConnection() {
				try {
					udpChannel.close();
				} catch (IOException e) {
					e.printStackTrace();
				}
			}
			
			@Override
			public int getId() {
				return connectionId;
			}
		}
	}

	private static ServerMessage intoServerMessage(ByteBuffer byteBuffer) throws IOException, ClassNotFoundException {
		//byte buffer to object       
		ByteArrayInputStream in = new ByteArrayInputStream(byteBuffer.array());
		ObjectInputStream is = new ObjectInputStream(in);

		return (ServerMessage)is.readObject();
	} 

	private class MessageHandler {
		private Map<ProtocolType, Protocol> protocolMap = new HashMap<>();

		public void extractAndExecuteProtocol(Connection connection, ByteBuffer byteBuffer) {
			try {
				ServerMessage serverMessage = intoServerMessage(byteBuffer);
				ProtocolType type = serverMessage.getKey();
				Protocol myProtocol = protocolMap.get(type);
				myProtocol.handleMsg(serverMessage.getData(), connection);
			} catch (ClassNotFoundException | IOException e) {
				e.printStackTrace();
			}
		}

		public void addProtocol(ProtocolType type, Protocol protocol){
			protocolMap.put(type, protocol);
		}
	}
}


