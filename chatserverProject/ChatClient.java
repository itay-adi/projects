package il.co.ilrd.chat_server;

import java.io.BufferedReader;
import java.io.ByteArrayInputStream;
import java.io.ByteArrayOutputStream;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import java.net.InetSocketAddress;
import java.nio.ByteBuffer;
import java.nio.channels.SocketChannel;

public class ChatClient {
	private static final int CAPACITY = 1024;

	public static void main(String[] args) {
		TCPChatClient tcpClient = new TCPChatClient(45454, "localhost");
		tcpClient.communicate();
	}

	/*****************Tools Methods*********************/

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

	static class TCPChatClient  implements Runnable{
		private SocketChannel channel;
		private boolean isRunning = true;

		public TCPChatClient(int port, String address){
			try {
				channel = SocketChannel.open(new InetSocketAddress(address, port));
			} catch (IOException e) {
				e.printStackTrace();
			}
		}

		public void communicate() {
			subScribe();
			new Thread(this).start();
			sendMsg();
		}

		private String scanFromKeyboard() {
			BufferedReader bufferRead = new BufferedReader(new InputStreamReader(System.in));
			String input = null;

			try {
				input = bufferRead.readLine();
			} catch (IOException e) {
				e.printStackTrace();
			}

			return input;
		}

		void subScribe() {
			System.out.println("Welcome to the Chat, please select a user-name:");
			String name = scanFromKeyboard();
			ByteBuffer receivedBuffer = ByteBuffer.allocate(CAPACITY);
			ByteBuffer sendableBuffer = ByteBuffer.allocate(CAPACITY);
			ServerMessage message = null;

			try {
				message = new ServerMessage(ProtocolType.CHAT, new ChatMessageClient(ChatMsgTypeUser.SUBSCRIBE, name));
				sendableBuffer = intoByteBuffer(message);
				channel.write(sendableBuffer);
				channel.read(receivedBuffer);

				ChatMessage receivedChatMessage = intoServerMessage(receivedBuffer);

				while(receivedChatMessage.getKey() == ChatMsgTypeServer.SUBSCRIBE_ERROR) {
					sendableBuffer.clear();
					receivedBuffer.clear();
					String answer = (String)receivedChatMessage.getData();
					System.out.println(answer);
					name = scanFromKeyboard();
					message = new ServerMessage(ProtocolType.CHAT, new ChatMessageClient(ChatMsgTypeUser.SUBSCRIBE, name));
					sendableBuffer = intoByteBuffer(message);
					channel.write(sendableBuffer);
					channel.read(receivedBuffer);
					receivedChatMessage = intoServerMessage(receivedBuffer);
				}

				System.out.println("****");
				String answer = (String)receivedChatMessage.getData();
				System.out.println(answer);
				sendableBuffer.clear();
				receivedBuffer.clear();

			} catch (IOException | ClassNotFoundException e) {
				e.printStackTrace();
			}
		}
		
		private void exit() {
			ByteBuffer receivedBuffer = ByteBuffer.allocate(CAPACITY);
			ServerMessage message = new ServerMessage(ProtocolType.CHAT, new ChatMessageClient(ChatMsgTypeUser.EXIT, "exit-1"));
			ByteBuffer sendableBuffer = intoByteBuffer(message);
			ChatMessage receivedChatMessage = null;
			
			try {
				channel.write(sendableBuffer);
				channel.read(receivedBuffer);
				receivedChatMessage = intoServerMessage(receivedBuffer);
				String answer = (String)receivedChatMessage.getData();
				System.out.println(answer);
				isRunning = false;
			} catch (IOException | ClassNotFoundException e) {
				e.printStackTrace();
			}
			
			sendableBuffer.clear();
		}
		
		private void sendMsg() {
			String sendableStr = null;
			ServerMessage message = null;
			ByteBuffer sendableBuffer = ByteBuffer.allocate(CAPACITY);
			
			System.out.println("You can now chat freely. press 'exit-1' to exit");
			sendableStr = scanFromKeyboard();
			
			while(!sendableStr.equals("exit-1")) {
				message = new ServerMessage(ProtocolType.CHAT, new ChatMessageClient(ChatMsgTypeUser.PUBLIC_MESSAGE, sendableStr));
				sendableBuffer = intoByteBuffer(message);
				try {
					channel.write(sendableBuffer);
				} catch (IOException e) {
					e.printStackTrace();
				}
				sendableStr = scanFromKeyboard();
				sendableBuffer.clear();
			}
			
			exit();
		}
		
		@Override
		public void run() {
			ByteBuffer receivedBuffer = null;
			ChatMessage receivedChatMessage = null;
			
			while(isRunning) {
				try {
					receivedBuffer = ByteBuffer.allocate(CAPACITY);
					channel.read(receivedBuffer);
					receivedChatMessage = intoServerMessage(receivedBuffer);
					String answer = (String)receivedChatMessage.getData();
					System.out.println(answer);
					receivedBuffer.flip();
				} catch (IOException | ClassNotFoundException e) {
					e.printStackTrace();
				}				
			}		
		}
	}
	
	private static ChatMessage intoServerMessage(ByteBuffer byteBuffer) throws IOException, ClassNotFoundException {
		//byte buffer to object       
		ByteArrayInputStream in = new ByteArrayInputStream(byteBuffer.array());
		ObjectInputStream is = new ObjectInputStream(in);

		return (ChatMessage)is.readObject();
	}
}
