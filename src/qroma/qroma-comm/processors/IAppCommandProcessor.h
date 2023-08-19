#ifndef IAPP_COMMAND_PROCESSOR_H
#define IAPP_COMMAND_PROCESSOR_H

#include <pb.h>

class IAppCommandProcessor {
  public:
    virtual uint32_t processBytes(const uint8_t * bytes, uint32_t byteCount, std::function<void(uint8_t*, uint32_t)> txFn, QromaCommResponse * qcResponse);
    virtual bool hasAppResponse();

    // virtual uint32_t txResponse(PbResponse * response, std::function<void(uint8_t*, uint32_t)> txFn);
};


#endif
