#ifndef QROMA_NEW_DATA_PROCESSOR_H
#define QROMA_NEW_DATA_PROCESSOR_H

#include <pb.h>

class QromaNewDataProcessor {
  public:
    virtual void init();
    virtual void uninit();
    
    virtual uint32_t processNewData(const uint8_t * bytes, uint32_t byteCount);
    // virtual void executeHandler();
};

#endif
