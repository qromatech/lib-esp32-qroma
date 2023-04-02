#ifndef QROMA_MESSAGE_PROCESSING_PIPELINE_H
#define QROMA_MESSAGE_PROCESSING_PIPELINE_H

#include <Arduino.h>
#include "../commBuffer/IQromaCommBuffer.h"
#include "processors/QromaMessageProcessor.h"
#include "processors/QromaNewDataProcessor.h"
#include "processors/QromaBytesProcessorMode.h"
#include "../pb-commands/PbCommandsRegistry.h"

class QromaMessageProcessingPipeline {
  public:
    QromaMessageProcessingPipeline();

    // void init(QromaRawBytesProcessor** qromaBytesProcessors, uint8_t qromaBytesProcessorsCount);
    void init(QromaMessageProcessor** qromaBytesProcessors, PbCommandsRegistry * pbCommandsRegistry);

    void setProcessingMode(QromaBytesProcessingMode mode);

    bool processCommBuffer(IQromaCommBuffer * commBuffer);
    uint32_t processPbCommands(const uint8_t * bytes, uint32_t byteCount);
    uint32_t processBase64PbCommands(const uint8_t * bytes, uint32_t byteCount);

  private:
    uint32_t _commSilenceDelayToClearBuffer;
    QromaBytesProcessingMode _processingMode;
    QromaBytesProcessingMode _defaultProcessingMode;

    QromaRawBytesProcessor** _qromaBytesProcessors;
    PbCommandsRegistry * _pbCommandsRegistry;
    uint8_t _qromaBytesProcessorsCount;
};


#endif
