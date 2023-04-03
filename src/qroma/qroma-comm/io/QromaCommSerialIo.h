#ifndef QROMA_COMM_SERIAL_IO_H
#define QROMA_COMM_SERIAL_IO_H

#include <Arduino.h>
#include "QromaCommSerialIoConfig.h"
#include "QromaCommSerialPbRxBase.h"
#include "../commBuffer/TQromaCommMemBuffer.h"
#include "IQromaCommSerialTx.h"



template<
  uint32_t bufferSize, 
  typename DefaultNewDataProcessor, 
  HardwareSerial * _serial
>
class QromaCommSerialIo: public QromaCommSerialPbRxBase,
                         public IQromaCommSerialTx
{
  public:

    void init(QromaCommSerialIoConfig * config, PbCommandsRegistry * pbCommandsRegistry) {

      initPbRxBase(&_tQromaCommMemBuffer, &_newDataProcessor, pbCommandsRegistry, [this](const uint8_t * bytes, uint32_t byteCount) {
        this->serialTxBytes(bytes, byteCount);
      });

      _serial->setRxBufferSize(config->rxBufferSize);
      _serial->setTxBufferSize(config->txBufferSize);
      
      _serial->begin(config->baudRate);
    }

    void serialTxBytes(const uint8_t * bytes, uint32_t byteCount) { 
      logInfo("QromaCommSerialIo - serialTxBytes");
      logInfo(byteCount);
      _serial->write(bytes, byteCount); 
    }

    HardwareSerial * getSerial() { return _serial; };

  private:
    TQromaCommMemBuffer<bufferSize> _tQromaCommMemBuffer;
    DefaultNewDataProcessor _newDataProcessor;
};

#endif
