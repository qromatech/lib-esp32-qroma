#ifndef PB_COMMAND_WITH_RESPONSE_PROCESSOR_H
#define PB_COMMAND_WITH_RESPONSE_PROCESSOR_H

#include <pb.h>
#include <pb_decode.h>
#include <functional>
#include "../qroma-comm.h"
#include "QromaBytesProcessor.h"


template<
  typename PbMessage, 
  const pb_msgdesc_t *PbMessageFields,
  typename PbResponse, 
  const pb_msgdesc_t *PbResponseFields
  >
class PbCommandWithResponseProcessor: public QromaBytesProcessor {

  public:
    PbCommandWithResponseProcessor(std::function<void(PbMessage*, PbResponse*)> handlerFunction) {
      _handlerFunction = handlerFunction;
    }
    
    uint32_t processBytes(const uint8_t * bytes, uint32_t byteCount) {
      PbMessage pbMessage;

      for (int i=1; i <= byteCount; i++) {
        pb_istream_t stream = pb_istream_from_buffer(bytes, i);
        bool decoded = pb_decode(&stream, PbMessageFields, &pbMessage);
        if (decoded) {
          PbResponse pbResponse;
          _handlerFunction(&pbMessage, &pbResponse);
          sendSerialPbMessage<PbResponse, PbResponseFields>(&pbResponse);
          return i;
        }
      }

      return 0;
    }
    
  private:
    std::function<void(PbMessage*, PbResponse*)> _handlerFunction;
};

#endif
