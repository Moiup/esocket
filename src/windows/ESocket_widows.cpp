#include "../inc/ESocket_windows.h"

ESocket::ESocket() : _socket{ INVALID_SOCKET } { ; }

ESocket::~ESocket() {
	Close();
}

void ESocket::SetSocket(SOCKET s) {
	_socket = s;
}

SOCKET ESocket::GetSocket() {
	return _socket;
}

void ESocket::Close() {
	if (_socket != INVALID_SOCKET) {
		closesocket(_socket);
        _socket = INVALID_SOCKET;
	}
}