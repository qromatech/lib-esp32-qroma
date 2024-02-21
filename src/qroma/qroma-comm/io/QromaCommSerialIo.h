#ifndef QROMA_COMM_SERIAL_IO_H
#define QROMA_COMM_SERIAL_IO_H

#include <Arduino.h>
#include "QromaCommSerialPbRxBase.h"
#include "IQromaCommSerialTx.h"
#include <qroma/qroma-comm/commBuffer/TQromaCommMemBuffer.h>
#include <qroma/qroma-comm/processors/IAppCommandProcessor.h>


// use the Arduino HardwareSerial by default; to set for ESP32 C3 (e.g. QT Py C3) in PlatformIO, add line
//  build_flags= -DQROMA_SERIAL="HWCDC" in platformio.ini

#ifdef QROMA_SERIAL
  typedef QROMA_SERIAL QromaCommSerialType;
#else
  typedef HardwareSerial QromaCommSerialType;
#endif



template<
  uint32_t MEM_BUFFER_SiZE,
  QromaCommSerialType * _serial
>
class QromaCommSerialIo: public QromaCommSerialPbRxBase,
                         public IQromaCommSerialTx
{
  public:

    void init(QromaCommSerialIoConfig * config) {

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

    QromaCommSerialType * getSerial() { return _serial; };

    void setAppCommandProcessor(IAppCommandProcessor * appCommandProcessor) {
      _appCommandProcessor = appCommandProcessor;
    }

  private:
    TQromaCommMemBuffer<MEM_BUFFER_SiZE> _tQromaCommMemBuffer;
    IAppCommandProcessor * _appCommandProcessor;
};

#endif
