package il.co.ilrd.chat_server;

import java.io.ByteArrayOutputStream;
import java.io.IOException;
import java.io.ObjectOutputStream;
import java.nio.ByteBuffer;
import java.util.HashMap;

public class ChatProtocol implements Protocol{
	private HashMap<String, Connection> clientMap = new HashMap<>();
	private HashMap<Connection, String> verificationMap = new HashMap<>();
	
	@Override
	public void handleMsg(Message<?, ?> clientMsg, Connection connection) {
		System.out.println((ChatMsgTypeUser)clientMsg.getKey());
		
		/******************************Send Message*******************************/
		if((ChatMsgTypeUser)clientMsg.getKey() == ChatMsgTypeUser.PUBLIC_MESSAGE){
			sendMessage(clientMsg, connection);
		}

		/***************************Registration****************************/
		else if((ChatMsgTypeUser)clientMsg.getKey() == ChatMsgTypeUser.SUBSCRIBE){
			Subscribe(clientMsg, connection);
		}

		/******************************Exit*******************************/
		else if((ChatMsgTypeUser)clientMsg.getKey() == ChatMsgTypeUser.EXIT){
			Disconnect(clientMsg, connection);
		}		
	}
	
	/**************************Server requests*****************************/
	private void Subscribe(Message<?, ?> clientMsg, Connection connection) {
		String ResponseStr = null;
		ChatMessage responseMsg = null;
		String userName = null;
		
		if((clientMsg.getData()) instanceof String) {
			userName = (String)(clientMsg.getData());
			
			//if the user name is already existing
			if(isUserNameExisting(userName) == true || " " == userName || null == userName) {
				ResponseStr = "Username is Already taken or illegal, please choose another one";
				responseMsg = new ChatMessage(ChatMsgTypeServer.SUBSCRIBE_ERROR, ResponseStr);
			}

			//if the user connection is already existing
			else if(isConnectionExisting(connection)){
				ResponseStr = "Connection already established, please stop trying";
				responseMsg = new ChatMessage(ChatMsgTypeServer.SUBSCRIBE_ERROR, ResponseStr);
			}

			//if the user name is acceptable
			else {
				ResponseStr = userName + " has joined.";
				responseMsg = new ChatMessage(ChatMsgTypeServer.PUBLIC_MESSAGE, ResponseStr);
				sendToAll(responseMsg);
				clientMap.put(userName, connection);
				verificationMap.put(connection, userName);

				ResponseStr = "Hey " + userName + ", Registration approved.";
				responseMsg = new ChatMessage(ChatMsgTypeServer.SUBSCRIBE_ACKNOWLEDGE, ResponseStr);
			}

			sendToSpecific(connection, responseMsg);
		}
	}
	
	/**************************************/
	
	private void Disconnect(Message<?, ?> clientMsg, Connection connection) {
		String ResponseStr = null;
		ChatMessage responseMsg = null;
		
		if(isConnectionExisting(connection)) {
			ResponseStr = "Bye-Bye. Its not going to be the same without you";
			responseMsg = new ChatMessage(ChatMsgTypeServer.PUBLIC_MESSAGE, ResponseStr);
			sendToSpecific(connection, responseMsg);

			//remove a specific user from the maps
			String removableUser = verificationMap.remove(connection);
			clientMap.remove(removableUser);

			ResponseStr = removableUser + " has left the building (finally...)";
			responseMsg = new ChatMessage(ChatMsgTypeServer.PUBLIC_MESSAGE, ResponseStr);
			sendToAll(responseMsg);
		}

		else {
			ResponseStr = "Unfamiliar connection";
			responseMsg = new ChatMessage(ChatMsgTypeServer.PUBLIC_MESSAGE, ResponseStr);
			sendToSpecific(connection, responseMsg);
		}
	}
	
	/**************************************/
	
	private void sendMessage(Message<?, ?> clientMsg, Connection connection) {
		String ResponseStr = null;
		ChatMessage responseMsg = null;
		
		if(isConnectionExisting(connection)) {
			//remove a specific user from the maps
			String removableUser = verificationMap.get(connection);
			clientMap.remove(removableUser);
			ResponseStr = removableUser + ": " + (String)(clientMsg.getData());
			responseMsg = new ChatMessage(ChatMsgTypeServer.PUBLIC_MESSAGE, ResponseStr);
			sendToAll(responseMsg);
			
			clientMap.put(removableUser, connection);
		}

		else {
			ResponseStr = "Unauthorized user. please subscribe first";
			responseMsg = new ChatMessage(ChatMsgTypeServer.UNAUTHORIZED_USER, ResponseStr);
			
			sendToSpecific(connection, responseMsg);
		}
	}
	
	/***********************assistance functions*****************************/
	
	//checks if a user-name is valid
	private boolean isUserNameExisting(String name) {
		return clientMap.containsKey(name);
	}

	//checks if a connection is valid
	private boolean isConnectionExisting(Connection connection) {
		return verificationMap.containsKey(connection);
	}

	//send a message to all of the connections
	private void sendToAll(ChatMessage sentMessage) {		
		for(Connection usersConnection : clientMap.values()) {
			sendToSpecific(usersConnection, sentMessage);
		}
	}

	//send a message to a specific connection
	private void sendToSpecific(Connection connection, ChatMessage sentMessage) {
		((SendableConnection)connection).sendMsg(intoByteBuffer(sentMessage));
	}

	//Turns an object to a byte-buffer
	private static ByteBuffer intoByteBuffer(Object obj){
		ByteArrayOutputStream out = new ByteArrayOutputStream();
		ObjectOutputStream os;

		try {
			os = new ObjectOutputStream(out);
			os.writeObject(obj);
		} catch (IOException e) {
			e.printStackTrace();
		}

		return ByteBuffer.wrap(out.toByteArray());
	}
}