#ifndef QROMA_COMM_SERIAL_PB_RX_BASE_H
#define QROMA_COMM_SERIAL_PB_RX_BASE_H

#include <qroma/qroma-comm/commBuffer/QromaCommMemBuffer.h>
#include <qroma/qroma-comm/processors/IQromaNewBytesProcessor.h>
#include <qroma/qroma-comm/processors/QromaCommProcessor.h>
#include <qroma/qroma-comm/processors/IAppCommandProcessor.h>


class QromaCommSerialPbRxBase {

  public:
    void initPbRxBase(
      QromaCommMemBuffer * qromaCommMemBuffer, 
      IAppCommandProcessor * qromaNewBytesProcessor, 
      std::function<void(const uint8_t*, uint32_t)> responseFn
    );

    void serialRx();

    bool processCommBuffer();

    template<typename PbMessage, const pb_msgdesc_t *PbMessageFields>
    bool sendQromaAppResponse(PbMessage * qromaAppResponse) {
      return _qromaCommProcessor.sendQromaAppResponse<PbMessage, PbMessageFields>(qromaAppResponse, _responseFn);
    }

    bool sendQromaCommResponse(QromaCommResponse * qromaCommResponse);



  private:
    uint32_t _commSilenceDelayToClearBuffer;
    
    QromaCommMemBuffer * _qromaCommMemBuffer;
    QromaCommProcessor _qromaCommProcessor;

    std::function<void(const uint8_t*, uint32_t)> _responseFn;
};

#endif
