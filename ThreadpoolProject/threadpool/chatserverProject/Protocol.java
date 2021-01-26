package il.co.ilrd.chat_server;


public interface Protocol {
	public void handleMsg(Message<?, ?> clientMsg, Connection connection);
}
