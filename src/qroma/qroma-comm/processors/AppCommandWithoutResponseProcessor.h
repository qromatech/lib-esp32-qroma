#ifndef APP_COMMAND_PROCESSOR_H
#define APP_COMMAND_PROCESSOR_H

#include <pb.h>
#include "IQromaNewBytesProcessor.h"
#include <qroma-lib-proto/qroma-comm.pb.h>
#include <qroma/util/logger.h>
#include <qroma/util/qbase64.h>
#include <pb_decode.h>
#include <pb_encode.h>
#include "IAppCommandProcessor.h"
// #include "fs_comm_handlers.h"


template<
  typename PbMessage, 
  const pb_msgdesc_t *PbMessageFields
>
class AppCommandWithoutResponseProcessor: public IAppCommandProcessor {
  public:
    AppCommandProcessor(std::function<void(PbMessage*, PbResponse*)> handlerFunction) {
      _handlerFunction = handlerFunction;
    }

  uint32_t processBytes(const uint8_t * bytes, uint32_t byteCount, QromaCommResponse * qcResponse) {

    pb_istream_t appCommand_istream = pb_istream_from_buffer(bytes, byteCount);
    bool appCommandDecoded = pb_decode(&appCommand_istream, PbMessageFields, &appCommand);
    if (!appCommandDecoded) {
      txFn((uint8_t *)"ERR APP COMMAND", 15);
      return 0;
    }

    // txFn((uint8_t *)"DO APP COMMAND", 14);

    PbMessage pbMessage;
    PbResponse appCommandResponse;
    _handlerFunction(&pbMessage, &appCommandResponse);
    
    memset(&(qromaCommResponse->response.appResponseBytes), 0, sizeof(qromaCommResponse->response.appResponseBytes));

    pb_ostream_t ostream = pb_ostream_from_buffer(
      qromaCommResponse->response.appResponseBytes.bytes,
      sizeof(qromaCommResponse->response.appResponseBytes.bytes)
    );
    bool encoded = pb_encode(&ostream, PbResponseFields, &appCommandResponse);
    if (!encoded) {
      logError("ERROR handleAppCommand - handleBytes/encode");
      return false;
    }

    qromaCommResponse->response.appResponseBytes.size = ostream.bytes_written;
    qromaCommResponse->which_response = QromaCommResponse_appResponseBytes_tag;

    return 0;
  }

  bool hasAppResponse() { return false; }

  const uint32_t setAppResponse(const pb_byte_t * bytes) {
    return sizeof(PbResponse);
  }

  // const bytes * getAppResponseBytes() {
  //   return 
  // }

  private:
    std::function<void(PbMessage*, PbResponse*)> _handlerFunction;

    PbResponse _appCommandResponse;

    unsigned char _base64DecodeBuffer[1000];
    unsigned char _base64EncodeBuffer[1000];
};

#endif
