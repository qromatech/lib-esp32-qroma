#ifndef PB_COMMAND_WITH_RESPONSE_PROCESSOR_H
#define PB_COMMAND_WITH_RESPONSE_PROCESSOR_H

#include <pb.h>
#include <pb_decode.h>
#include <functional>
#include "../qroma-comm.h"
#include "IPbCommandHandler.h"


template<
  typename PbMessage, 
  const pb_msgdesc_t *PbMessageFields,
  typename PbResponse, 
  const pb_msgdesc_t *PbResponseFields
  >
class PbCommandWithResponseHandler: public IPbCommandHandler {

  public:
    PbCommandWithResponseHandler(std::function<void(PbMessage*, PbResponse*)> handlerFunction) {
      _handlerFunction = handlerFunction;
    }

    
    uint32_t handleBytes(const uint8_t * bytes, uint32_t byteCount, std::function<void(uint8_t*, uint32_t)> responseFn) {
      PbMessage pbMessage;

      pb_istream_t stream = pb_istream_from_buffer(bytes, byteCount);
      bool decoded = pb_decode(&stream, PbMessageFields, &pbMessage);

      if (decoded) {
        PbResponse pbResponse;
        _handlerFunction(&pbMessage, &pbResponse);
        sendSerialPbMessage<PbResponse, PbResponseFields>(&pbResponse, responseFn);
        return byteCount;
      }

      return 0;
    }
    
  private:
    std::function<void(PbMessage*, PbResponse*)> _handlerFunction;
};

#endif
