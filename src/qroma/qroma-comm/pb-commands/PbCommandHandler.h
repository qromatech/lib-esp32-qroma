#ifndef PB_COMMAND_HANDLER_H
#define PB_COMMAND_HANDLER_H

#include <pb.h>
#include <pb_decode.h>
#include <functional>
#include "IPbCommandHandler.h"

template<typename PbMessage, const pb_msgdesc_t *PbMessageFields>
class PbCommandHandler: public IPbCommandHandler {

  public:
    PbCommandHandler(std::function<void(PbMessage*)> handlerFunction) {
      _handlerFunction = handlerFunction;
    }
    
    // uint32_t handleBytes(const uint8_t * bytes, uint32_t byteCount, std::function<void(uint8_t*, uint32_t)> responseFn) {
    //   PbMessage pbMessage;

    //   for (int i=1; i <= byteCount; i++) {
    //     pb_istream_t stream = pb_istream_from_buffer(bytes, i);
    //     bool decoded = pb_decode(&stream, PbMessageFields, &pbMessage);

    //     if (decoded) {
    //       _handlerFunction(&pbMessage);
    //       return i;
    //     }
    //   }

    //   return 0;
    // }

    uint32_t handleBytes(const uint8_t * bytes, uint32_t byteCount, std::function<void(uint8_t*, uint32_t)> responseFn) {
      PbMessage pbMessage;

      pb_istream_t istream = pb_istream_from_buffer(bytes, byteCount);
      bool decoded = pb_decode(&istream, PbMessageFields, &pbMessage);

      if (decoded) {
        _handlerFunction(&pbMessage);
        return byteCount;
      }

      return 0;
    }

  private:
    std::function<void(PbMessage*)> _handlerFunction;
};

#endif
