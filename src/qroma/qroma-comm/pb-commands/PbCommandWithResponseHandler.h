#ifndef PB_COMMAND_WITH_RESPONSE_PROCESSOR_H
#define PB_COMMAND_WITH_RESPONSE_PROCESSOR_H

#include <RTOS.h>
#include <pb.h>
#include <pb_decode.h>
#include <functional>
#include "../qroma-comm.h"
#include "../pipeline/processors/QromaNewDataProcessor.h"
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
        logInfo("HANDLED BY HANDLER");
        sendSerialPbMessage<PbResponse, PbResponseFields>(&pbResponse, responseFn);
        logInfo("RESPONSE  BY HANDLER");

        // memcpy(&_pbMessage, &pbMessage, sizeof(PbMessage));

        // BaseType_t xTaskStatus = xTaskCreate(taskHandlePbCommandProcessorCommand,
        //   "taskHandlePbCommandProcessorCommand", 40000, (void*)(QromaBytesProcessor*)this, 1, NULL);

        // if (xTaskStatus != pdPASS) {
        //   logError("ERROR CREATING TASK: taskHandlePbCommandProcessorCommand");
        //   logError(xTaskStatus);
        // }

        return byteCount;
      }

      return 0;
    }
    
    // uint32_t handleBytes(const uint8_t * bytes, uint32_t byteCount, std::function<void(uint8_t*, uint32_t)> responseFn) {
    //   PbMessage pbMessage;

    //   for (int i=1; i <= byteCount; i++) {
    //     pb_istream_t stream = pb_istream_from_buffer(bytes, i);
    //     bool decoded = pb_decode(&stream, PbMessageFields, &pbMessage);

    //     if (decoded) {
    //       PbResponse pbResponse;
    //       _handlerFunction(&pbMessage, &pbResponse);
    //       sendSerialPbMessage<PbResponse, PbResponseFields>(&pbResponse, responseFn);

    //       // memcpy(&_pbMessage, &pbMessage, sizeof(PbMessage));

    //       // BaseType_t xTaskStatus = xTaskCreate(taskHandlePbCommandProcessorCommand,
    //       //   "taskHandlePbCommandProcessorCommand", 40000, (void*)(QromaBytesProcessor*)this, 1, NULL);

    //       // if (xTaskStatus != pdPASS) {
    //       //   logError("ERROR CREATING TASK: taskHandlePbCommandProcessorCommand");
    //       //   logError(xTaskStatus);
    //       // }

    //       return i;
    //     }
    //   }

    //   return 0;
    // }

    // void executeHandler() {
    //   PbResponse pbResponse;
    //   _handlerFunction(&_pbMessage, &pbResponse);
    //   // sendSerialPbMessage<PbResponse, PbResponseFields>(&pbResponse);
    // }
    
  private:
    // PbMessage _pbMessage;

    std::function<void(PbMessage*, PbResponse*)> _handlerFunction;
};

#endif
