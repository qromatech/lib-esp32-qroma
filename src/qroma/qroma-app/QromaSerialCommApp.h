#ifndef QROMA_SERIAL_COMM_APP_H
#define QROMA_SERIAL_COMM_APP_H

#include "QromaSerialCommAppBase.h"
#include "../qroma-comm/processors/QromaPb64NewLineDelimitedProcessor.h"
#include "QromaApp.h"
#include "IQromaSerialCommApp.h"
#include "../qroma-comm/io/QromaCommSerialIo.h"
#include "../qroma-comm/io/IQromaCommSerialTx.h"
// #include "../qroma-comm/processors/Qroma2BytesWithLengthAndPbProcessor.h"

typedef std::function<void(QromaCommSerialIoConfig * config)> QromaCommSerialIoConfigFn;

typedef std::function<void(QromaAppConfig * config)> QromaAppConfigFn;



// template<
//   typename PbMessage, 
//   const pb_msgdesc_t *PbMessageFields,
//   typename PbResponse, 
//   const pb_msgdesc_t *PbResponseFields
// >
// class QromaSerialCommApp: public QromaSerialCommAppBase<1000, &Serial, QromaPb64NewLineDelimitedProcessor<PbMessage, PbMessageFields, PbResponse, PbResponseFields>>
// class QromaSerialCommApp: public QromaSerialCommAppBase<1000, &Serial>
class QromaSerialCommApp: QromaApp
// class QromaSerialCommApp: public QromaSerialCommAppBase<1000, Qroma2BytesWithLengthAndPbProcessor, &Serial>
{
  public:
    QromaSerialCommApp() {
      // command processor
      // membuffer
      // 
    }

    // // void registerPbCommandFunction(std::function<void(PbMessage*)> handlerFunction, PbCommandsRegistry * pbCommandsRegistry) {
    // void registerPbCommandFunction(std::function<void(PbMessage*, PbResponse*)> handlerFunction) {
    //   // PbCommandHandler<PbMessage, PbMessageFields> * pbCommandHandler = 
    //   //   new PbCommandHandler<PbMessage, PbMessageFields>(handlerFunction);

    //   // pbCommandsRegistry->setAppCommandProcessor(pbCommandHandler);
    // }


    void setAppCommandProcessor(IQromaNewDataPbProcessor * processor) {
      _qromaCommSerialIo.setNewDataProcessor(processor);
    }
    

    void startupQroma() {
      // _startupQroma(app);
      setQromaApp(this);
      // qromaApp->init();
      init();
    }

    void configureSerialCommIo(QromaCommSerialIoConfigFn serialIoConfigFn) {
      // QromaCommSerialIoConfig * r = getSerialIoConfigRef();
      serialIoConfigFn(&_serialIoConfig);
    }

    void configureQromaApp(QromaAppConfigFn configFn) {
      // configFn(app->getAppConfigRef());
      configFn(this->getAppConfigRef());
    }

    IQromaCommSerialTx * getQromaCommSerialTxRef() {
      return &_qromaCommSerialIo;
    }

    void init() {
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


// template<
//   typename PbMessage, 
//   const pb_msgdesc_t *PbMessageFields,
//   typename PbResponse, 
//   const pb_msgdesc_t *PbResponseFields
//   >
// void registerPbCommandFunction(std::function<void(PbMessage*, PbResponse*)> handlerFunction, PbCommandsRegistry * pbCommandsRegistry)
// {
//   PbCommandWithResponseHandler<PbMessage, P
// };


#endif
