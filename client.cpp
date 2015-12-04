#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include "client.h"

//Global Message object
Message client;



Message::Message()
{
	m_sConnection = false;
}

void Message::Init(string IpAddress, int Port) //initilize server address and connect
{

	m_ServerIPAddress = IpAddress;
	m_ServerPort = Port;
	struct hostent *host;
	unsigned int addr;
	struct sockaddr_in server;
	

	WSADATA wsaData;

	int wsaret=WSAStartup(0x101,&wsaData);


	if(wsaret!=0)
	{
		return;
	}

	conn=socket(AF_INET,SOCK_STREAM,0);
	if(conn==INVALID_SOCKET)
		return;

	addr=inet_addr(m_ServerIPAddress.c_str());
	host=gethostbyaddr((char*)&addr,sizeof(addr),AF_INET);
	
	if(host==NULL)
	{
		closesocket(conn);
		return;
	}

	server.sin_addr.s_addr= inet_addr("127.0.0.1");
	server.sin_family=AF_INET;
	server.sin_port=htons(m_ServerPort);
	if(connect(conn,(struct sockaddr*)&server,sizeof(server)))
	{
		closesocket(conn);
		return;	
	}
	m_sConnection = true;
	return;
}

Message::~Message()
{
	if(m_sConnection)
		closesocket(conn);
}

int Message::SendMessagePort(string sMessage)
{
		int iStat = 0;
		iStat = send(conn,sMessage.c_str(),sMessage.size()+1,0);
		if(iStat == -1)
			return 2;
		return 0;

}
int Message::RecMessagePort()
{

		char acRetData[1024];
		int iStat = 0;

		iStat = recv(conn,acRetData,1024,0);
		if (iStat == -1)
			
			return 3;
		cout<<"-->"<<acRetData<<"\n";

		return 0;

}



UINT  RecThreadEntry(LPVOID pParam)
{	
	while(1)
	{
		if(client.RecMessagePort())
			break;
	}
	return 0;
}



int main(int argc, char* argv[])
{
	char buf[1024];
	cout<<"\nPress ONLY ENTER to quit";
	cout<<"\n===============================================\n";

	SOCKET sHost;
	sHost = socket(AF_INET, SOCK_STREAM, 0);

	string sServerAddress;

	sServerAddress = "127.0.0.1";

	string content;
	

	client.Init(sServerAddress.c_str(), 6274);

	AfxBeginThread(RecThreadEntry,0);
	while(true)
	{
		ZeroMemory(buf, 1024);
		cin >> buf;
		content = buf;
		client.SendMessagePort(content);
	}
	 
	cout<<"\n BYE:";
	_getch();
	return 0;
}
