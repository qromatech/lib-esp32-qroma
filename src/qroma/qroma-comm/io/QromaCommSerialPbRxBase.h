#ifndef QROMA_COMM_SERIAL_PB_RX_BASE_H
#define QROMA_COMM_SERIAL_PB_RX_BASE_H

#include "../commBuffer/QromaCommMemBuffer.h"
#include "../pipeline/processors/QromaNewDataPbProcessor.h"


class QromaCommSerialPbRxBase {

  public:
    void initPbRxBase(
      QromaCommMemBuffer * qromaCommMemBuffer, 
      QromaNewDataPbProcessor * defaultQromaNewDataProcessor, 
      PbCommandsRegistry * pbCommandsRegistry,
      std::function<void(uint8_t*, uint32_t)> responseFn
    );

    void serialRx();

    bool processCommBuffer();

    // std::function<void(uint8_t*, uint32_t)> _responseFn;

  private:
    uint32_t _commSilenceDelayToClearBuffer;
    
    QromaCommMemBuffer * _qromaCommMemBuffer;
    QromaNewDataPbProcessor * _defaultQromaNewDataProcessor;
    QromaNewDataPbProcessor * _activeQromaNewDataProcessor;

    PbCommandsRegistry * _pbCommandsRegistry;

    std::function<void(uint8_t*, uint32_t)> _responseFn;
};

#endif