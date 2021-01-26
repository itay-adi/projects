package il.co.ilrd.chat_server;

public class ChatMessage implements Message<ChatMsgTypeServer, String> {
    private final ChatMsgTypeServer key;
    private final String data;

    public ChatMessage(ChatMsgTypeServer key, String data){
        this.key = key;
        this.data = data;
    }

    @Override
    public ChatMsgTypeServer getKey() {
        return key;
    }

    @Override
    public String getData() {
        return data;
    }
}
