#ifndef QROMA_COMM_SERIAL_IO_H
#define QROMA_COMM_SERIAL_IO_H

#include <Arduino.h>
#include "QromaCommSerialIoConfig.h"
#include "QromaCommSerialPbRxBase.h"
#include "../commBuffer/TQromaCommMemBuffer.h"
#include "IQromaCommSerialTx.h"
#include "../processors/IAppCommandProcessor.h"



template<
  uint32_t bufferSize,
  // typename DefaultNewDataProcessor, 
  HWCDC * _serial
>
class QromaCommSerialIo: public QromaCommSerialPbRxBase,
                         public IQromaCommSerialTx
{
  public:

    void init(QromaCommSerialIoConfig * config) {

      // _serial = serial;

      initPbRxBase(&_tQromaCommMemBuffer, _appCommandProcessor, [this](const uint8_t * bytes, uint32_t byteCount) {
        this->serialTxBytes(bytes, byteCount);
      });

      _serial->setRxBufferSize(config->rxBufferSize);
      _serial->setTxBufferSize(config->txBufferSize);
      
      _serial->begin(config->baudRate);
    }

    void serialTxBytes(const uint8_t * bytes, uint32_t byteCount) { 
      _serial->write(bytes, byteCount); 
    }

    void print(const char * message) { 
      _serial->print(message); 
    }

    void println(const char * message) { 
      _serial->println(message); 
    }

    HWCDC * getSerial() { return _serial; };

    void setAppCommandProcessor(IAppCommandProcessor * appCommandProcessor) {
      _appCommandProcessor = appCommandProcessor;
    }

  private:
    TQromaCommMemBuffer<bufferSize> _tQromaCommMemBuffer;
    // DefaultNewDataProcessor _newDataProcessor;
    IAppCommandProcessor * _appCommandProcessor;

    // HWCDC * _serial;
};

#endif
