#ifndef QROMA_SERIAL_COMM_APP_H
#define QROMA_SERIAL_COMM_APP_H

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

    void startupQroma() {
      setQromaApp(this);
      init();
      _whenHeartbeatLastSentInMs = 0;
      _numHeartbeatTicks = 0;
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

    bool processHeartbeat() {
      uint32_t rightNow = millis();
      uint32_t msSinceLastSent = rightNow - _whenHeartbeatLastSentInMs;
      uint32_t heartbeatIntervalInMs = getHeartbeatIntervalInMs();

      if (heartbeatIntervalInMs != 0 &&
          msSinceLastSent >= heartbeatIntervalInMs) 
      {
        _whenHeartbeatLastSentInMs = rightNow;
        _numHeartbeatTicks++;
        
        QromaCommResponse heartbeatResponse;
        heartbeatResponse.which_response = QromaCommResponse_heartbeatResponse_tag;
        heartbeatResponse.response.heartbeatResponse.heartbeatTicks = _numHeartbeatTicks;
        heartbeatResponse.response.heartbeatResponse.uptimeInMs = rightNow;

        return _qromaCommSerialIo.sendQromaCommResponse(&heartbeatResponse);
      }

      return false;
    };

    void init() {
      initFileSystem();
      _qromaCommSerialIo.init(&_serialIoConfig);
      initApp();
    }

  
  private:

    QromaCommSerialIo<1000, &Serial> _qromaCommSerialIo;
    uint32_t _whenHeartbeatLastSentInMs = 0;
    uint32_t _numHeartbeatTicks = 0;

    QromaCommSerialIoConfig _serialIoConfig = {
      .baudRate = 115200,
      .rxBufferSize = 1000
    };

};


#endif
