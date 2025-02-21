#include "../../inc/linux/EServerSocket_linux.h"

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
    ;
}

EStream EServerSocket::Connect() {
    EStream client_stream{};
    
    struct addrinfo hints;
    struct addrinfo *result;

    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;
    hints.ai_protocol = IPPROTO_TCP;

    int32_t i_result = getaddrinfo(
        _address.c_str(),
        _port.c_str(),
        &hints,
        &result
    );

    if(i_result == -1){
        std::cout << "getaddrinfo failed: " << strerror(errno) << std::endl;
        return client_stream;
    }

    int32_t sock = socket(
        result->ai_family,
        result->ai_socktype,
        result->ai_protocol
    );
    _socket.SetSocket(sock);

    if (_socket.GetSocket() == -1) {
        std::cout << "Error creating client socket: " << strerror(errno) << std::endl;
        return client_stream;
    }

    i_result = connect(_socket.GetSocket(), result->ai_addr, result->ai_addrlen);
    freeaddrinfo(result);

    if(i_result == -1){
        std::cout << "Error connecting client socket: " << strerror(errno) << std::endl;
        return client_stream;
    }

    client_stream.SetESocket(_socket);

    return client_stream;
}

int32_t EServerSocket::Bind() {
    struct addrinfo hints;
    struct addrinfo *result;

    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;
    hints.ai_protocol = IPPROTO_TCP;

    int32_t i_result = getaddrinfo(
        _address.c_str(),
        _port.c_str(),
        &hints,
        &result
    );

    if(i_result == -1){
        std::cout << "getaddrinfo failed: " << strerror(errno) << std::endl;
        return errno;
    }

    int32_t sock = socket(
        result->ai_family,
        result->ai_socktype,
        result->ai_protocol
    );
    _socket.SetSocket(sock);

    if (_socket.GetSocket() == -1) {
        std::cout << "Error creating server socket: " << strerror(errno) << std::endl;
        return errno;
    }

    i_result = bind(_socket.GetSocket(), result->ai_addr, result->ai_addrlen);
    if(i_result == -1){
        std::cout << "Error binding server socket :" << strerror(errno) << std::endl;
        return errno;
    }

    freeaddrinfo(result);

    return i_result;
}

int32_t EServerSocket::Listen(){
    int32_t i_result = listen(_socket.GetSocket(), SOMAXCONN);
    if(i_result == -1){
        std::cout << "Error listening: " << strerror(errno) << std::endl;
        _socket.Close();
        return errno;
    }
    return 0;
}

EStream EServerSocket::Accept() {
    EStream client_stream;
    ESocket sock;
    
    sock.SetSocket(accept(_socket.GetSocket(), nullptr, nullptr));
    if(sock.GetSocket() == -1){
        std::cout << "Accept failed: " << strerror(errno) << std::endl;
        _socket.Close();
    }

    return client_stream;
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