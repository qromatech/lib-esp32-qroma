#ifndef QROMA_BASE64_BRACKET_BOUNDED_PB_PROCESSOR_H
#define QROMA_BASE64_BRACKET_BOUNDED_PB_PROCESSOR_H

#include <pb.h>
#include "QromaNewDataPbProcessor.h"

class QromaBase64BracketBoundedPbProcessor: public QromaNewDataPbProcessor {
  public:
    // void init();
    // void uninit();
    
    void reset();
    uint32_t processBytes(const uint8_t * bytes, uint32_t byteCount, PbCommandsRegistry * pbCommandsRegistry, std::function<void(uint8_t*, uint32_t)> txFn);
    // virtual void executeHandler();
};

#endif
