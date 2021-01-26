package il.co.ilrd.chat_server;

public class ChatMessageClient implements Message<ChatMsgTypeUser, String> {
    private final ChatMsgTypeUser kind;
    private final String data;
    ChatMessageClient(ChatMsgTypeUser kind, String content){
        this.kind = kind;
        this.data = content;
    }
    @Override
    public ChatMsgTypeUser getKey() {
        return kind;
    }

    @Override
    public String getData() {
        return data;
    }
}