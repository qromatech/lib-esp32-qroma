#ifndef IPB_COMMAND_PROCESSOR_H
#define IPB_COMMAND_PROCESSOR_H

#include <pb.h>
#include <functional>


class IPbCommandHandler {
  public:
    virtual uint32_t handleBytes(const uint8_t * bytes, uint32_t byteCount, std::function<void(uint8_t*, uint32_t)> responseFn) = 0;
};

#endif
