#ifndef REGISTER_PB_COMMAND_HANDLERS_H
#define REGISTER_PB_COMMAND_HANDLERS_H

#include <pb.h>
#include <functional>

#include "../../qroma-comm/pb-commands/PbCommandHandler.h"
#include "../../qroma-comm/pb-commands/PbCommandWithResponseHandler.h"


template<
  typename PbMessage, 
  const pb_msgdesc_t *PbMessageFields
  >
void registerPbCommandFunction(std::function<void(PbMessage*)> handlerFunction, PbCommandsRegistry * pbCommandsRegistry) {
  PbCommandHandler<PbMessage, PbMessageFields> * pbCommandHandler = 
    new PbCommandHandler<PbMessage, PbMessageFields>(handlerFunction);

  pbCommandsRegistry->setAppCommandProcessor(pbCommandHandler);
}


template<
  typename PbMessage, 
  const pb_msgdesc_t *PbMessageFields,
  typename PbResponse, 
  const pb_msgdesc_t *PbResponseFields
  >
void registerPbCommandFunction(std::function<void(PbMessage*, PbResponse*)> handlerFunction, PbCommandsRegistry * pbCommandsRegistry)
{
  PbCommandWithResponseHandler<PbMessage, PbMessageFields, PbResponse, PbResponseFields> * pbCommandHandler = 
    new PbCommandWithResponseHandler<PbMessage, PbMessageFields, PbResponse, PbResponseFields>(handlerFunction);

// bool decode_callback(pb_istream_t *stream, const pb_field_t *field, void ** arg) {

// }

// bool (*decode)(pb_istream_t *stream, const pb_field_t *field, void **arg);

  // bool (*decode_callback)(pb_istream_t *istream, const pb_field_t *field, void **arg) = [](pb_istream_t *istream, const pb_field_t *field, void **arg) {
  auto decode_callback = [](pb_istream_t *istream, const pb_field_t *field, void **arg) -> bool {
    PbMessage pbMessage;

    // pb_istream_t istream = pb_istream_from_buffer(bytes, byteCount);
    bool decoded = pb_decode(istream, PbMessageFields, &pbMessage);
    // logInfo("base64EncodeAndTx()");
    // unsigned int encodedBufferLength = q_encode_base64(bytes, bytesLength, _base64EncodeBuffer);
    // txFn(_base64EncodeBuffer, encodedBufferLength);
    // txFn((uint8_t*)"\n", 1);

    if (decoded) {
      PbResponse pbResponse;
      memset(&pbResponse, 0, sizeof(pbResponse));

      // handlerFunction(&pbMessage, &pbResponse);

      uint8_t encodeBuffer[2000];
      memset(encodeBuffer, 0, sizeof(encodeBuffer));
  
      pb_ostream_t ostream = pb_ostream_from_buffer(encodeBuffer, sizeof(encodeBuffer));
      bool encoded = pb_encode(&ostream, PbResponseFields, &pbResponse);
      if (!encoded) {
        logError("ERROR PbCommandWithResponseHandler - handleBytes/encode");
        return false;
      }

      // responseFn(encodeBuffer, ostream.bytes_written);
      // return byteCount;
      return true;
    }

    return decoded;
  };

  // bool (*decode_callback)(pb_istream_t *stream, const pb_field_t *field, void **arg);

  pbCommandsRegistry->decodeFunc = decode_callback;

  pbCommandsRegistry->setAppCommandProcessor(pbCommandHandler);
}

#endif
