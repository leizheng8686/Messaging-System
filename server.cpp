#include "server.h"


messageserver Server;


UINT  RecThreadEntry(LPVOID pParam)
{	
	SOCKET sRecSocket = (SOCKET)pParam;
	while(1)
	{
		if(Server.Recv(sRecSocket))
			break;
	}
	return 0;
}



UINT  ListenThreadEntry(LPVOID pParam)
{	

	while(1)
		Server.Listen();
	return 0;
}



messageserver::messageserver()
{
    cout << "Start the server\n";
	m_sConnection = false;

    WSADATA wsaData;

    sockaddr_in local;

    int wsaret=WSAStartup(0x101,&wsaData);// version request

    if(wsaret!=0)
    {
        return;
    }

    local.sin_family=AF_INET; 
    local.sin_addr.s_addr=INADDR_ANY; 
    local.sin_port=htons((u_short)6274); //set port number

    m_SListenClient=socket(AF_INET,SOCK_STREAM,0);


    if(m_SListenClient==INVALID_SOCKET)
    {
        return;
    }


    if(bind(m_SListenClient,(sockaddr*)&local,sizeof(local))!=0)
    {
        return;
    }


    if(listen(m_SListenClient,10)!=0) //connect up to 10 clients
    {
        return;
    }

	m_sConnection = true;
    return;
}

messageserver::~messageserver()
{
    closesocket(m_SListenClient);

    WSACleanup();
}

void messageserver::Listen() //wait for client to connect
{

    sockaddr_in from;
    int fromlen=sizeof(from);

    m_SClient=accept(m_SListenClient,
         (struct sockaddr*)&from,&fromlen);

	if(m_SClient != INVALID_SOCKET)
		m_vClientList.push_back(m_SClient);

	AfxBeginThread(RecThreadEntry,(void *)m_SClient);

}



int messageserver::Send(string sMessage) // send message
{
		int iStat = 0;
		list<SOCKET>::iterator itl;

		if(m_vClientList.size() == 0)
			return 0;

		for(itl = m_vClientList.begin();itl != m_vClientList.end();itl++)
		{
			iStat = send(*itl,sMessage.c_str(),sMessage.size()+1,0);			
			if(iStat == -1)
				m_vClientList.remove(*itl);

		}

		if(iStat == -1)
			return 1;

		return 0;

}

int messageserver::Recv(SOCKET sRecSocket) // message receive
{
    char temp[1024];
	int iStat;
	iStat = recv(sRecSocket,temp,1024,0);
	if(iStat == -1)
		{
			m_vClientList.remove(sRecSocket);
			return 1;
		}
	else
		{
			cout <<":"<<temp<<"\n";
			Send(temp);//broadcast
			return 0;
		}
	return 0;

}




int main(int argc, char* argv[])
{
	char buf[1024];
	
	cout << "Connect to the server pc port .\n";
    cout << "Press only ENTER to quit.\n";
	cout << "=================================================\n";

	if(!Server.sConnection())
	{
		cout<<"\nFailed to initialize server socket";
		_getch();
		return 1;
	}
	AfxBeginThread(ListenThreadEntry,0);


	while(gets_s(buf))
	{
		if(strlen(buf) == 0)
			break;
		if(Server.Send(buf))
		{
			cout<<"Problem in connecting to server. Check whether server is running\n";
			break;
		}
	}

	cout<<"bye";
	_getch();
	
    return 0;
}

