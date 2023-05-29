#ifndef IAPP_COMMAND_PROCESSOR_H
#define IAPP_COMMAND_PROCESSOR_H

#include <pb.h>

class IAppCommandProcessor {
  public:
    virtual uint32_t processBytes(const uint8_t * bytes, uint32_t byteCount, std::function<void(uint8_t*, uint32_t)> txFn, QromaCommResponse * qcResponse);
    virtual bool hasAppResponse();
    // virtual void serialTxBytes(const uint8_t * bytes, uint32_t byteCount) = 0;
    // virtual void print(const char * message) = 0;
    // virtual void println(const char * message) = 0;
};


#endif
