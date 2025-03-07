#pragma once
#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <iostream>

#pragma comment (lib, "Ws2_32.lib")
#pragma comment (lib, "Mswsock.lib")
#pragma comment (lib, "AdvApi32.lib")

class ESocket
{

private:
	SOCKET _socket;

public:
	ESocket();
	~ESocket();

	void SetSocket(SOCKET s);
	SOCKET GetSocket();

	void Close();
};

