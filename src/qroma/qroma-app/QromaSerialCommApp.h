#ifndef QROMA_SERIAL_COMM_APP_H
#define QROMA_SERIAL_COMM_APP_H

#include "QromaApp.h"
#include "IQromaSerialCommApp.h"
#include <qroma/qroma-comm/io/QromaCommSerialIo.h>
#include <qroma/qroma-comm/io/IQromaCommSerialTx.h>
#include <qroma/qroma-comm/processors/IAppCommandProcessor.h>
#include <qroma/util/fs.h>


#define MEM_BUFFER_SiZE        1000
#define SERIAL_RX_BUFFER_SIZE  1000
#define SERIAL_TX_BUFFER_SIZE  1000

#define QROMA_CORE_CONFIG_FILENAME "/qroma-core-config.qroma"


class QromaSerialCommApp: public QromaApp
{
  public:

    void startupQroma();

    void setAppCommandProcessor(IAppCommandProcessor * processor) {
      _qromaCommSerialIo.setAppCommandProcessor(processor);
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
      initApp();
      _qromaCommSerialIo.init(&(_qromaCoreConfig.serialIoConfig));
    }

    bool tick();

    bool saveDefaultQromaCoreConfig();
    bool saveQromaCoreConfig();

  
  private:
    void _doTickStuff();
    void _sendHeartbeatResponse();

    QromaCommSerialIo<MEM_BUFFER_SiZE, &Serial> _qromaCommSerialIo;
    uint32_t _nextHeartbeatSendTimeInMs = 0;
    uint32_t _numHeartbeatTicks = 0;
};


void setQromaSerialCommApp(QromaSerialCommApp * app);
QromaSerialCommApp * getQromaSerialCommApp();


#endif
