#ifndef _ESERVER_SOCKET_LINUX_H_
#define _ESERVER_SOCKET_LINUX_H_

#include "ESocket_linux.h"
#include "EStream_linux.h"

#include <string>

class EServerSocket
{

private:
    ESocket _socket;

    std::string _address;
    std::string _port;

public:
    EServerSocket();
    EServerSocket(const std::string& address, const std::string& port);
    ~EServerSocket();

    EStream Connect();

    int32_t Bind();
    int32_t Listen();
    EStream Accept();

    std::string& Address();
    std::string& Port();

    const std::string& Address() const;
    const std::string& Port() const;
};

#endif