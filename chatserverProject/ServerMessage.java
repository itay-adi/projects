package il.co.ilrd.chat_server;

public class ServerMessage implements Message<ProtocolType, Message<?, ?>> {
    private final ProtocolType protocolKey;
    private final Message<?, ?> data;

    public ServerMessage(ProtocolType protocolKey, Message<?, ?> data) {
        this.protocolKey = protocolKey;
        this.data = data;
    }

    @Override
    public ProtocolType getKey() {
        return protocolKey;
    }

    @Override
    public Message<?, ?> getData() {
        return data;
    }
}
