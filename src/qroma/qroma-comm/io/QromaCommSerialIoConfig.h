#ifndef QROMA_COMM_SERIAL_IO_CONFIG_H
#define QROMA_COMM_SERIAL_IO_CONFIG_H

#include "../commBuffer/QromaCommMemBuffer.h"
#include "../pipeline/processors/QromaNewDataProcessor.h"


class QromaCommSerialIoConfig {
  public:
    unsigned long baudRate;
    size_t rxBufferSize;
    size_t txBufferSize;
};


#endif
