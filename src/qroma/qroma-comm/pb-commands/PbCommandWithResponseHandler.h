#ifndef PB_COMMAND_WITH_RESPONSE_PROCESSOR_H
#define PB_COMMAND_WITH_RESPONSE_PROCESSOR_H

#include <pb.h>
#include <pb_decode.h>
#include <pb_encode.h>
#include <functional>
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

      pb_istream_t istream = pb_istream_from_buffer(bytes, byteCount);
      bool decoded = pb_decode(&istream, PbMessageFields, &pbMessage);

      if (decoded) {
        PbResponse pbResponse;
        memset(&pbResponse, 0, sizeof(pbResponse));

        _handlerFunction(&pbMessage, &pbResponse);

        uint8_t encodeBuffer[2000];
        memset(encodeBuffer, 0, sizeof(encodeBuffer));
    
        pb_ostream_t ostream = pb_ostream_from_buffer(encodeBuffer, sizeof(encodeBuffer));
        bool encoded = pb_encode(&ostream, PbResponseFields, &pbResponse);
        if (!encoded) {
          logError("ERROR PbCommandWithResponseHandler - handleBytes/encode");
          return 0;
        }

        responseFn(encodeBuffer, ostream.bytes_written);
        return byteCount;
      }

      return 0;
    }
    
  private:
    std::function<void(PbMessage*, PbResponse*)> _handlerFunction;
};

#endif
