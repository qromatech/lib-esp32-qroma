#ifndef QROMA_COMM_SERIAL_IO_H
#define QROMA_COMM_SERIAL_IO_H

#include <Arduino.h>
#include "QromaCommSerialIoConfig.h"
#include "QromaCommSerialPbRxBase.h"
#include "../commBuffer/QromaCommMemBuffer.h"
#include "../commBuffer/TQromaCommMemBuffer.h"
#include "../pipeline/QromaMessageProcessingPipeline.h"
// #include "../serial/QromaSerialRx.h"
// #include "../serial/QromaSerialTx.h"
// #include "../pipeline/QromaCommSerialRxProcessor.h"


// template<
//   typename NewDataProcessor
// >
template<
  uint32_t bufferSize, 
  typename DefaultNewDataProcessor, 
  HardwareSerial * _serial
>
class QromaCommSerialIo: public QromaCommSerialPbRxBase {
  public:
    // QromaCommSerialIo() {

    // }

    void init(QromaCommSerialIoConfig * config, PbCommandsRegistry * pbCommandsRegistry) {
      // _newDataProcessor.initPbCommandsRegistry(pbCommandsRegistry);
      initPbRxBase(&_tQromaCommMemBuffer, &_newDataProcessor, pbCommandsRegistry, [this](const uint8_t * bytes, uint32_t byteCount) {
        this->serialTxBytes(bytes, byteCount);
      });

      _serial->setRxBufferSize(config->rxBufferSize);
      _serial->setTxBufferSize(config->txBufferSize);
      
      _serial->begin(config->baudRate);
    }

    // void onSerialReceive();
    // void serialRx();
    // bool processCommBuffer();

    void serialTxBytes(const uint8_t * bytes, uint32_t byteCount) { 
      logInfo("QromaCommSerialIo - serialTxBytes");
      logInfo(byteCount);
      _serial->write(bytes, byteCount); 
    }
    // // void serialPrint(const char * message);
    // // void serialPrintln(const char * message);

    // virtual QromaCommMemBuffer * getQromaCommMemBuffer();
    HardwareSerial * getSerial() { return _serial; };
    // virtual QromaNewDataProcessor * getQromaNewDataProcessor();

  private:
    // QromaCommMemBuffer * _qromaCommMemBuffer;
    TQromaCommMemBuffer<bufferSize> _tQromaCommMemBuffer;
    // HardwareSerial * _serial;
    // QromaNewDataProcessor * _newDataProcessor;
    // QromaCommSerialRxProcessor<DefaultNewDataProcessor> _serialRxProcessor;

    // PbCommandsRegistry * _pbCommandsRegistry;

    DefaultNewDataProcessor _newDataProcessor;


  //   DefaultNewDataProcessor _newDataProcessor;

    // QromaSerialRx _qromaSerialRx;
    // QromaSerialTx _qromaSerialTx;
};


#endif
