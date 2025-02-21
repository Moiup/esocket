#ifndef _ESTREAM_LINUX_H_
#define _ESTREAM_LINUX_H_

#include "ESocket_linux.h"

class EStream
{
private:
    ESocket* _esocket{nullptr};

public:
    EStream();
    EStream(ESocket& es);
    EStream(EStream&& stream);
    ~EStream();

    EStream& operator=(EStream&& stream);

    int32_t Recv(uint32_t buf_size, char* buf);
    int32_t Send(char* buf, uint32_t size);
    int32_t Close();

    ESocket& GetESocket();
    void SetESocket(ESocket& es);

};

#endif