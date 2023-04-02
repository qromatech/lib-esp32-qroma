#ifndef QROMA_BASE64_PROCESSOR_H
#define QROMA_BASE64_PROCESSOR_H

#include <pb.h>

class QromaBase64Processor: QromaNewDataProcessor {
  public:
    virtual void init();
    virtual void uninit();
    
    virtual uint32_t processBytes(const uint8_t * bytes, uint32_t byteCount);
    // virtual void executeHandler();
};

#endif
