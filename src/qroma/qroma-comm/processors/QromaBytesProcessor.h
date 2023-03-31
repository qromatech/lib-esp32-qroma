#ifndef QROMA_BYTES_PROCESSOR_H
#define QROMA_BYTES_PROCESSOR_H

#include <pb.h>

class QromaBytesProcessor {
  public:
    virtual uint32_t processBytes(const uint8_t * bytes, uint32_t byteCount);
    virtual void executeHandler();
};

#endif
