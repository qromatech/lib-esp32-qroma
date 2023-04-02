#ifndef QROMA_BASE64_NEWLINE_DELIMITED_PROCESSOR_H
#define QROMA_BASE64_NEWLINE_DELIMITED_PROCESSOR_H

#include <pb.h>
#include "QromaNewDataPbProcessor.h"

class QromaBase64NewLineDelimitedPbProcessor: public QromaNewDataPbProcessor {
  public:
    // virtual void init();
    // virtual void uninit();

    void reset();
    uint32_t processBytes(const uint8_t * bytes, uint32_t byteCount, PbCommandsRegistry * pbCommandsRegistry, std::function<void(uint8_t*, uint32_t)> txFn);
    
    // void base64EncodeAndTx();
    // virtual void executeHandler();

  private:
    unsigned char _base64DecodeBuffer[1000];
    unsigned char _base64EncodeBuffer[1000];
};

#endif
