Chat Server:

A generic server which enables communication via TCP, UDP and Broadcast protocols, and can
interpret customized protocols like chat between multiple users

--------------------------------------------------------------------------------
Files:

----------------------------------

Mains:
1. ChatClient.java: Conceptualize the client which connects to the server via TCP
2. GenericServer.java: Conceptualize the Server which the users can connect to

----------------------------------

Classes:
1. ChatMessageClient.java: Defining the ChatMessageClient class
2. ChatProtocol.java: The chat protocol itself, which enables the user to:
	-subscribe
	-send public message
	-disconnect

3. ChatMessage.java: Defining the ChatMessage class
4. ServerMessage.java: Defining the functionality of a Server Message

----------------------------------

Interfaces:

1. Connection.java: An interface for connection methods (functions)
2. Message.java: An interface for the Messages
3. Protocol.java: An interface for the protocol itself, which contains message handler
4. ProtocolType.java: An interface which consists the customized protocols of the server
5. SendableConnection.java: An interface which consists the send/receive

----------------------------------

Enums:

1. ChatMsgTypeServer.java: An ENUM for the Chat Message Type from the Server
2. ChatMsgTypeUser.java: An ENUM for the Chat Message Type from the Client
3. ConnectionType.java: An ENUM which consists the connection types: TCP, UDP, BC

--------------------------------------------------------------------------------
