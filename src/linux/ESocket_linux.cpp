#include "../../inc/linux/ESocket_linux.h"

ESocket::ESocket():
    _socket{ -1 }
{
    ;
}

ESocket::~ESocket() {
    Close();
}

void ESocket::SetSocket(int32_t socket){
    _socket = socket;
}

int32_t ESocket::GetSocket(){
    return _socket;
}


void ESocket::Close() {
    std::cout << "ESocket close" << std::endl;
    if(_socket != -1){
        close(_socket);
        _socket = -1;
    }
}