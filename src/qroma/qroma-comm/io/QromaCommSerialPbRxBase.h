#ifndef QROMA_COMM_SERIAL_PB_RX_BASE_H
#define QROMA_COMM_SERIAL_PB_RX_BASE_H

#include "../commBuffer/QromaCommMemBuffer.h"
#include "../processors/IQromaNewBytesProcessor.h"
#include "../processors/QromaCommProcessor.h"
#include "../processors/IAppCommandProcessor.h"


class QromaCommSerialPbRxBase {

  public:
    void initPbRxBase(
      QromaCommMemBuffer * qromaCommMemBuffer, 
      IAppCommandProcessor * qromaNewBytesProcessor, 
      // PbCommandsRegistry * pbCommandsRegistry,
      std::function<void(const uint8_t*, uint32_t)> responseFn
    );

    void serialRx();

    bool processCommBuffer();

  private:
    uint32_t _commSilenceDelayToClearBuffer;
    
    QromaCommMemBuffer * _qromaCommMemBuffer;
    // IQromaNewDataPbProcessor * _activeQromaNewDataProcessor;
    QromaCommProcessor _qromaCommProcessor;

    // PbCommandsRegistry * _pbCommandsRegistry;

    std::function<void(const uint8_t*, uint32_t)> _responseFn;
};

#endif
