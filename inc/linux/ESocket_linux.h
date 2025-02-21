#ifndef _ESOCKET_LINUX_H_
#define _ESOCKET_LINUX_H_

#include <iostream>
#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

class ESocket
{

private:
    int32_t _socket;

public:
    ESocket();
    ~ESocket();
    
    void SetSocket(int32_t socket);
    int32_t GetSocket();

    void Close();
};

#endif