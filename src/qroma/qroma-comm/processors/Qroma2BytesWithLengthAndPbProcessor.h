#ifndef QROMA_2BYTES_WITH_LENGTH_AND_PB_PROCESSOR_H
#define QROMA_2BYTES_WITH_LENGTH_AND_PB_PROCESSOR_H

#include <pb.h>
#include "IQromaNewDataPbProcessor.h"

class Qroma2BytesWithLengthAndPbProcessor: public IQromaNewDataPbProcessor {
  public:
    void reset();
    uint32_t processBytes(const uint8_t * bytes, uint32_t byteCount, PbCommandsRegistry * pbCommandsRegistry, std::function<void(uint8_t*, uint32_t)> txFn);
    
  // private:
  //   unsigned char _base64DecodeBuffer[1000];
  //   unsigned char _base64EncodeBuffer[1000];
};

#endif
