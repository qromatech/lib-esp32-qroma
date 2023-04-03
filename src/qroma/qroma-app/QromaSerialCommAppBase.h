#ifndef QROMA_SERIAL_COMM_APP_BASE_H
#define QROMA_SERIAL_COMM_APP_BASE_H

#include "QromaApp.h"
#include "IQromaSerialCommApp.h"
#include "../qroma-comm/io/QromaCommSerialIo.h"
#include "../qroma-comm/io/IQromaCommSerialTx.h"


template<
  uint32_t bufferSize, 
  typename DefaultNewDataProcessor, 
  HardwareSerial * _serial
>
class QromaSerialCommAppBase: public QromaApp,
                              public IQromaSerialCommApp,
                              public PbCommandsRegistry 
{
  public:
    void init() {
      _qromaCommSerialIo.init(&_serialIoConfig, this);
      initApp();
    }
    
    QromaCommSerialIoConfig * getSerialIoConfigRef() { return &_serialIoConfig; }
    
    IQromaCommSerialTx * getSerialTx() { return &_qromaCommSerialIo; }

  private:
    // QromaCommSerialIo<1000, QromaBase64BracketBoundedPbProcessor, &Serial> _qromaCommSerialIo;
    QromaCommSerialIo<bufferSize, DefaultNewDataProcessor, _serial> _qromaCommSerialIo;

    QromaCommSerialIoConfig _serialIoConfig = {
      .baudRate = 115200,
      .rxBufferSize = 1000
    };
};

#endif
