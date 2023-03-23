#ifndef QROMA_COMM_SERIAL_IO_H
#define QROMA_COMM_SERIAL_IO_H

#include "QromaCommSerialIoConfig.h"
#include "../commBuffer/QromaCommMemBuffer.h"
#include "../processors/QromaBytesProcessingPipeline.h"
#include "../serial/QromaSerialRx.h"
#include "../serial/QromaSerialTx.h"


class QromaCommSerialIo {
  public:
    QromaCommSerialIo();

    void init(QromaCommSerialIoConfig * config);

    void onSerialReceive();

    void serialTxBytes(const uint8_t * bytes, uint32_t byteCount);
    void serialPrint(const char * message);
    void serialPrintln(const char * message);

  private:
    QromaCommMemBuffer * _qromaCommMemBuffer;
    QromaBytesProcessingPipeline _bytesProcessingPipeline;

    QromaSerialRx _qromaSerialRx;
    QromaSerialTx _qromaSerialTx;
};


#endif
