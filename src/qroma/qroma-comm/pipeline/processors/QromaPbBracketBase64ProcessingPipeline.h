// #ifndef QROMA_BYTES_PROCESSING_PIPELINE_H
// #define QROMA_BYTES_PROCESSING_PIPELINE_H

// #include <Arduino.h>
// #include "../commBuffer/IQromaCommBuffer.h"
// #include "QromaBytesProcessor.h"
// #include "QromaBytesProcessorMode.h"

// class QromaPbBracketBase64ProcessingPipeline {
//   public:
//     QromaPbBracketBase64ProcessingPipeline();

//     void init(QromaBytesProcessor** qromaBytesProcessors, uint8_t qromaBytesProcessorsCount);

//     void setProcessingMode(QromaBytesProcessingMode mode);

//     bool processCommBuffer(IQromaCommBuffer * commBuffer);
//     uint32_t processPbCommands(const uint8_t * bytes, uint32_t byteCount);

//   private:
//     // uint32_t COMM_SILENCE_DELAY_TO_CLEAR_BUFFER = 3000;
//     uint32_t _commSilenceDelayToClearBuffer;
//     QromaBytesProcessingMode _processingMode;

//     QromaBytesProcessor** _qromaBytesProcessors;
//     uint8_t _qromaBytesProcessorsCount;
// };


// #endif
