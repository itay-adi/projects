package il.co.ilrd.chat_server;

import java.nio.ByteBuffer;

public interface SendableConnection extends Connection {
	public void sendMsg(ByteBuffer buffer);
	public void receiveMsg();
}
