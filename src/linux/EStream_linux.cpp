#include "../../inc/linux/EStream_linux.h"

EStream::EStream() : 
    _esocket{}
{
    ;    
}

EStream::EStream(ESocket& es){
    SetESocket(es);
}

EStream::EStream(EStream&& stream){
    *this = std::move(stream);
}

EStream& EStream::operator=(EStream&& stream){
     _esocket = std::move(stream)._esocket;
    stream._esocket = nullptr;
    return *this;
}

EStream::~EStream() {
    Close();
}

int32_t EStream::Recv(uint32_t buf_size, char* buf) {
    return recv(_esocket->GetSocket(), buf, buf_size, 0);
}

int32_t EStream::Send(char* buf, uint32_t size){
    return send(_esocket->GetSocket(), buf, size, 0);
}

int32_t EStream::Close(){
    int32_t res{0};
    if(_esocket){
        res = shutdown(_esocket->GetSocket(), SHUT_RDWR);
        _esocket = nullptr;
    }
    return res;
}

ESocket& EStream::GetESocket() {
    return *_esocket;
}

void EStream::SetESocket(ESocket& es){
    _esocket = &es;
}