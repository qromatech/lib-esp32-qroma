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


template<
  typename PbMessage, 
  const pb_msgdesc_t *PbMessageFields,
  typename PbResponse, 
  const pb_msgdesc_t *PbResponseFields
>
class AppCommandProcessor: public IAppCommandProcessor {
  public:
    AppCommandProcessor(std::function<void(PbMessage*, PbResponse*)> handlerFunction) {
      _handlerFunction = handlerFunction;
    }

  uint32_t processBytes(const uint8_t * bytes, uint32_t byteCount, std::function<void(uint8_t*, uint32_t)> txFn, QromaCommResponse * qcResponse) {

    txFn((uint8_t *)"DO APP COMMAND", 14);

    PbMessage appCommand;
    memset(&appCommand, 0, sizeof(appCommand));

    pb_istream_t appCommand_istream = pb_istream_from_buffer(bytes, byteCount);
    bool appCommandDecoded = pb_decode(&appCommand_istream, PbMessageFields, &appCommand);
    if (!appCommandDecoded) {
      txFn((uint8_t *)"ERR APP COMMAND", 15);
      return 0;
    }

    PbResponse appCommandResponse;
    _handlerFunction(&appCommand, &appCommandResponse);
    
    memset(&(qcResponse->response.appResponseBytes), 0, sizeof(qcResponse->response.appResponseBytes));

    pb_ostream_t ostream = pb_ostream_from_buffer(
      qcResponse->response.appResponseBytes.bytes,
      sizeof(qcResponse->response.appResponseBytes.bytes)
    );
    bool encoded = pb_encode(&ostream, PbResponseFields, &appCommandResponse);
    if (!encoded) {
      logError("ERROR handleAppCommand - handleBytes/encode");
      return false;
    }

    qcResponse->response.appResponseBytes.size = ostream.bytes_written;
    qcResponse->which_response = QromaCommResponse_appResponseBytes_tag;

    return 0;
  }

  bool hasAppResponse() { return true; }

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
