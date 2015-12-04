# Messaging-System
810E project

Environment: Visual Studio 2015

How to compile: 

Authors: Shengkai Yu,Yunlin Zeng,Lei Zheng



What we finish yet :
1.We can implement communication between one client and one server, which means : client can send message to server and server will receive the message from client ;  server can send message to client and client will receive the message from server.

2.We can implement the broadcast, which means that once we run several client program in several computers, if one client send message then all clients will receive this message.

What we need to do more:

1.We need to implement multi-thread, Which means several clients can establish several connections with one server at the same time. Some of the threads will suspend, and the others will work. 

With multi-thread, we can implement that different clients can send different messages to the server at the same time, and the server will show these messages separately.

And also we can communicate between two different clients through the server using multi-thread.

2.We need to create a thread list to store all threads, and also create flags for different threads, which means marks for different clients.

A client send a request to server, says I want to talk someone, then the server shows all online clients. Then the client will choose one to communicat. Means that with thread list, a client can decide which client communicate to.

3.Attach file to server from client.

4.Create options for clients to send different requests to server to ask for different functions.
