#ifndef QROMA_SERIAL_COMM_APP_H
#define QROMA_SERIAL_COMM_APP_H

// #include "QromaSerialCommAppBase.h"
#include "QromaApp.h"
#include "IQromaSerialCommApp.h"
#include <qroma/qroma-comm/io/QromaCommSerialIo.h>
#include <qroma/qroma-comm/io/IQromaCommSerialTx.h>
#include <qroma/qroma-comm/processors/IAppCommandProcessor.h>
#include <qroma/util/fs.h>


typedef std::function<void(QromaCommSerialIoConfig * config)> QromaCommSerialIoConfigFn;

typedef std::function<void(QromaAppConfig * config)> QromaAppConfigFn;


class QromaSerialCommApp: QromaApp
{
  public:
    QromaSerialCommApp() {
      // command processor
      // membuffer
    }


    void startupQroma() {
      setQromaApp(this);
      init();
    }

    void setAppCommandProcessor(IAppCommandProcessor * processor) {
      _qromaCommSerialIo.setAppCommandProcessor(processor);
    }
    
    void configureSerialCommIo(QromaCommSerialIoConfigFn serialIoConfigFn) {
      serialIoConfigFn(&_serialIoConfig);
    }

    void configureQromaApp(QromaAppConfigFn configFn) {
      configFn(this->getAppConfigRef());
    }

    IQromaCommSerialTx * getQromaCommSerialTxRef() {
      return &_qromaCommSerialIo;
    }

    template<typename PbMessage, const pb_msgdesc_t *PbMessageFields>
    bool sendQromaAppResponse(PbMessage * response) {
      return _qromaCommSerialIo.sendQromaAppResponse<PbMessage, PbMessageFields>(response);
    }

    void init() {
      initFileSystem();
      _qromaCommSerialIo.init(&_serialIoConfig);
      initApp();
    }

  
  private:
    // QromaCommSerialIo 
    // QromaCommSerialIo Config
    // Comm/new data Processor

    QromaCommSerialIo<1000, &Serial> _qromaCommSerialIo;

    QromaCommSerialIoConfig _serialIoConfig = {
      .baudRate = 115200,
      .rxBufferSize = 1000
    };

};


#endif
