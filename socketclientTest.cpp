// socketclientTest.cpp : 定义控制台应用程序的入口点。  
//  
  
#include "stdafx.h"  
#include <iostream>  
  
#include <winsock.h>  
  
#pragma comment(lib,"ws2_32.lib")  
  
#define  MAXBUFLEN 256  
#define PORT 44965  
#define DEST_IP_ADDR "127.0.0.1" //想要链接的目标Server address  
  
using namespace std;  
int _tmain(int argc, _TCHAR* argv[])  
{  
    WSADATA Data;  
    SOCKADDR_IN destSockAddr;  
    SOCKET destSocket;  
    unsigned long destAddr;  
    int status;  
      
  
    /* initialize the Windows Socket DLL */  
    status=WSAStartup(MAKEWORD(1, 1), &Data);  
    if (status != 0)  
        cout<< "ERROR: WSAStartup unsuccessful"<<endl;  
  
    /* convert IP address into in_addr form */  
    destAddr=inet_addr(DEST_IP_ADDR);  
    /* copy destAddr into sockaddr_in structure */  
    memcpy(&destSockAddr.sin_addr, &destAddr, sizeof(destAddr));  
    /* specify the port portion of the address */  
    destSockAddr.sin_port=htons(PORT);  
    /* specify the address family as Internet */  
    destSockAddr.sin_family=AF_INET;  
  
    /* create a socket */  
    destSocket=socket(AF_INET, SOCK_STREAM, 0);  
    if (destSocket == INVALID_SOCKET)  
    {  
        cout<< "ERROR: socket unsuccessful" << endl;  
  
        status=WSACleanup();  
        if (status == SOCKET_ERROR)  
            cout<< "ERROR: WSACleanup unsuccessful" << endl;  
        return(1);  
    }  
      
    cout<< "Trying to connect to IP Address: " << DEST_IP_ADDR <<endl;  
  
    /* connect to the server */  
    status=connect(destSocket, (LPSOCKADDR)&destSockAddr, sizeof(destSockAddr));  
    if (status == SOCKET_ERROR)  
    {  
        cout<< "ERROR: connect unsuccessful" << endl;  
  
        status=closesocket(destSocket);  
        if (status == SOCKET_ERROR)  
            cout<< "ERROR: closesocket unsuccessful"  
            << endl;  
        status=WSACleanup();  
        if (status == SOCKET_ERROR)  
            cout<< "ERROR: WSACleanup unsuccessful"  
            << endl;  
        return(1);  
    }  
  
    cout << "Connected..." << endl;  
  
    while(1)  
    {  
        int numsnt;  
        char *toSendtxt=new char[256];  
        cout << "输入想要发送给服务器的消息内容并按回车发送:" << endl;  
        cin>>toSendtxt;  
        numsnt=send(destSocket, toSendtxt, strlen(toSendtxt) + 1, 0);  
        if (numsnt != (int)strlen(toSendtxt) + 1)  
        {  
            cout << "Connection terminated" << endl;  
  
            status=closesocket(destSocket);  
            if (status == SOCKET_ERROR)  
                cout<< "ERROR: closesocket unsuccessful" << endl;  
            status=WSACleanup();  
            if (status == SOCKET_ERROR)  
                cout<< "ERROR: WSACleanup unsuccessful" << endl;  
            return(1);  
        }  
  
        /* Wait before sending the message again */  
        cout<<"向服务器发送的消息已经成功发送现在等待接受服务器发来的消息......"<<endl;  
        int numrcv;  
        char buffer[MAXBUFLEN];  
        numrcv = recv(destSocket/*已经建立的套接字*/,buffer/*接受输入数据缓冲器的指针*/,MAXBUFLEN/*接受缓冲区大小*/,0/*传输控制方式*/);  
  
        if ((0==numrcv)||(numrcv==SOCKET_ERROR))  
        {  
            cout<<"链接受到限制"<<endl;  
  
            status = closesocket(destSocket);  
            if (SOCKET_ERROR==status)  
                cout<<"断开链接失败"<<endl;  
  
            status = WSACleanup();  
            if (SOCKET_ERROR==status)  
                cout<<"清理链接失败"<<endl;  
            return(1);  
        }  
        cout<<"服务器发来的消息内容是："<<buffer<<endl;  
          
    } /* while */  
    return 0;  
}  
  
/*总结通信客户端，  建立一个socket通信，          socket() 
                    链接目标服务器端，            connect() 
                    向服务器发送消息，            send() 
                    接受服务器端发来的消息内容，  recv() 
                     
*/
