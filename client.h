
#include <Afxwin.h>
#include <cstdio>
#include <winsock2.h>
#include <conio.h> 
#include <string.h>
#include <iostream>

using namespace std;


class Message
{
public:
	Message();
	~Message();
	void Init(string sIpAddress, int iPort);
	int SendMessagePort(string sMessage);
	int RecMessagePort();
	bool sConnection(){return m_sConnection;}
private:
	bool m_sConnection; // true - connected false - not connected
	string m_ServerIPAddress;
	int m_ServerPort;
	SOCKET conn; // socket connected to server
};
