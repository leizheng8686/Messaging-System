
#include <Afxwin.h>
#include <stdio.h>
#include <winsock2.h>
#include <conio.h> 
#include<list>
#include <iostream>

using namespace std;

class messageserver
{
public:
	messageserver();
	~messageserver();
	bool sConnection(){return m_sConnection;} // returns connection status
	void Listen(); // Listen to client
	int Send(string sMessage); // Send message to all clients.
	int Recv(SOCKET sRecSocket); // receive message for a particulat socket
private:
	bool m_sConnection; // connected(true) not connected(false)
	int m_iServerPort;
	list<SOCKET> m_vClientList; // All socket connected to client
	SOCKET m_SClient;
	SOCKET m_SListenClient; // socket listening for client calls
};
