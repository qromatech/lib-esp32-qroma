#ifndef QROMA_COMM_SERIAL_IO_CONFIG_H
#define QROMA_COMM_SERIAL_IO_CONFIG_H

#include "../commBuffer/QromaCommMemBuffer.h"
#include "../processors/QromaBytesProcessor.h"


class QromaCommSerialIoConfig {
  public:
    QromaCommMemBuffer * qromaCommMemBuffer;

    QromaBytesProcessor** qromaBytesProcessors;
    uint8_t qromaBytesProcessorsCount;

    unsigned long baudRate;
};


#endif
