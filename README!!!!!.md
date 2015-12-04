# Messaging-System
810E project

Environment: Visual Studio 2015

How to compile: 
1.In option of debug,  start source server support at debug option and click microsoft Symbol Server. Then debug with local Windows Compiler. Then debuger will load all pdb files needed.

2.Replace the afxwin.h and afx.h in your VC include library, because we have modified them for some reasons.If you do not replace them , you may have errs.    But something interesting is that MAYBE there are msome errs although you replace these two head file due to different computers. The solution is to delete the unknown identifier as it says.

Authors: 
Shengkai Yu,Yunlin Zeng,Lei Zheng



What we finish yet :

1.We can implement communication between one client and one server, which means : client can send message to server and server will receive the message from client ;  server can send message to client and client will receive the message from server.

2.We can implement the broadcast, which means that once we run several client program in several computers, if one client send  a message then all clients will receive this message.

3.We have implemented multi-thread with AfxBeginThread.  Any client at any computer can join in the communication at any time.


What we need to do more:

1.We need to extend multi-thread, Which means several clients can establish several connections with one server at the same time. Some of the threads will suspend, and the others will work. 

With multi-thread model, we can implement that different clients can send different messages to the server at the same time, and the server will show these messages separately.

And also we can communicate between two different clients through the server using multi-thread.

2.We have created a thread list to store all threads, and we also need to create flags for different threads, which means marks for different clients.

A client send a request to server, says I want to talk with someone, then the server shows all online clients. Then the client will choose one to communicate. With this  thread list, the client can communicate to other certain client.

3.Attach file to server from client. And other clients could modify this file.

4.Create options for clients to send different requests to server to ask for different functions.
