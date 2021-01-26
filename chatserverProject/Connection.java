package il.co.ilrd.chat_server;

public interface Connection {
	public void initConnection();
	public void stopConnection();
	public int getId();
}
