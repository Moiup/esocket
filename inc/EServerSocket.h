#pragma once
#include "ESocket.h"
#include "EStream.h"

#include <string>

class EServerSocket
{
public:

private:
	ESocket _socket;

	struct addrinfo* _result;
	std::string _address;
	std::string _port;

public:
	EServerSocket();
	EServerSocket(const std::string& address, const std::string& port);
	~EServerSocket();

	INT32 Initialise();

	EStream Connect();

	INT32 Bind();
	INT32 Listen();
	EStream Accept();
	SOCKET Accept_test();
	INT32 Close();


	std::string& Address();
	std::string& Port();

	const std::string& Address() const;
	const std::string& Port() const;

};

