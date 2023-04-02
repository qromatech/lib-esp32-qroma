#ifndef QROMA_COMM_SERIAL_IO_CONFIG_H
#define QROMA_COMM_SERIAL_IO_CONFIG_H

#include <pb.h>

class QromaCommSerialIoConfig {
  public:
    unsigned long baudRate;
    size_t rxBufferSize;
    size_t txBufferSize;
};


#endif
