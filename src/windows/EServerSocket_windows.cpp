#include "../../inc/windows/EServerSocket_windows.h"

EServerSocket::EServerSocket() :
	_socket{},
	_address{ "127.0.0.1" },
	_port{ "8080" }
{; }

EServerSocket::EServerSocket(const std::string& address, const std::string& port) :
	_socket{},
	_address{ address },
	_port{ port }
{
	;
}

EServerSocket::~EServerSocket() {
	WSACleanup();
}

INT32 EServerSocket::Bind() {
	INT32 i_result{};
	WSADATA wsa_data{};
	struct addrinfo hints {};
	struct addrinfo* result;

	i_result = WSAStartup(MAKEWORD(2, 2), &wsa_data);
	if (i_result != 0) {
		std::cout << "WSAStartup failed: " << i_result << std::endl;
		return i_result;
	}

	ZeroMemory(&hints, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;
	hints.ai_flags = AI_PASSIVE;

	i_result = getaddrinfo(_address.c_str(), _port.c_str(), &hints, &result);
	if (i_result != 0) {
		std::cout << "getaddrinfo failed: " << i_result << std::endl;
		WSACleanup();
		return i_result;
	}

	_socket.SetSocket(
		socket(
			result->ai_family,
			result->ai_socktype,
			result->ai_protocol
		)
	);
	if (_socket.GetSocket() == INVALID_SOCKET) {
		std::cout << "Error creating server socket :" << WSAGetLastError() << std::endl;
		freeaddrinfo(_result);
		WSACleanup();
		return WSAGetLastError();
	}

	i_result = bind(_socket.GetSocket(), result->ai_addr, (int)result->ai_addrlen);
	freeaddrinfo(_result);


	if (i_result == SOCKET_ERROR) {
		std::cout << "Bind failed : " << WSAGetLastError() << std::endl;
		_socket.Close();
		WSACleanup();
		return WSAGetLastError();
	}

	return i_result;
}

EStream EServerSocket::Connect() {
	EStream client_stream{};
	INT32 i_result{};

	i_result = connect(_socket.GetSocket(), result->ai_addr, (int)(result->ai_addrlen));
	client_stream.SetESocket(_socket);

	freeaddrinfo(result);
	result = nullptr;

	if (i_result == SOCKET_ERROR) {
		std::cout << "Connection failed : " << WSAGetLastError() << std::endl;
		_socket.Close();
		WSACleanup();
		return {};
	}

	return client_stream;
}

INT32 EServerSocket::Listen() {
	INT32 i_result{};

	i_result = listen(_socket.GetSocket(), SOMAXCONN);
	if (i_result == SOCKET_ERROR) {
		std::cout << "listen failed." << std::endl;
		_socket.Close();
		WSACleanup();
		return WSAGetLastError();
	}

	return i_result;
}

EStream EServerSocket::Accept() {
	EStream client_stream{};
	ESocket sock;
	
	sock.SetSocket(accept(_socket.GetSocket(), NULL, NULL));

	if (sock.GetSocket() == INVALID_SOCKET) {
		std::cout << "Accept failed : " << WSAGetLastError() << std::endl;
		_socket.Close();
		WSACleanup();
	}

	client_stream.SetESocket(sock);

	return client_stream;
}

SOCKET EServerSocket::Accept_test() {
	EStream client_stream;

	SOCKET s = accept(_socket.GetSocket(), NULL, NULL);

	if (s == INVALID_SOCKET) {
		std::cout << "Accept failed: " << WSAGetLastError() << std::endl;
		_socket.Close();
		WSACleanup();
	}

	std::cout << s << std::endl;

	return s;
}

std::string& EServerSocket::Address() {
	return _address;
}

std::string& EServerSocket::Port() {
	return _port;
}

const std::string& EServerSocket::Address() const {
	return _address;
}

const std::string& EServerSocket::Port() const {
	return _port;
}