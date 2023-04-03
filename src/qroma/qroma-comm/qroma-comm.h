#ifndef QROMA_MODULE__COMM_H
#define QROMA_MODULE__COMM_H

#include <pb.h>
#include <pb_encode.h>
#include <functional>


template <typename PbMessage, const pb_msgdesc_t *PbMessageFields>
bool sendSerialPbMessage(PbMessage* message, std::function<void(uint8_t*, uint32_t)> responseFn)
{
  uint8_t buffer[2000];
  memset(buffer, 0, sizeof(buffer));
  
  pb_ostream_t stream = pb_ostream_from_buffer(buffer, sizeof(buffer));
  bool encoded = pb_encode(&stream, PbMessageFields, message);
  if (!encoded) {
    logError("ERROR ENCODING STATUS DATA");
    return false;
  }

  responseFn(buffer, stream.bytes_written);

  return true;
}


template <typename PbMessage, const pb_msgdesc_t *PbMessageFields>
bool sendSerialPbMessage(PbMessage* message, QromaSerialCommApp * app)
{
  return sendSerialPbMessage<PbMessage, PbMessageFields>(message, 
    [app](const uint8_t * bytes, uint32_t byteCount) {
      app->getSerialTx()->serialTxBytes(bytes, byteCount);
    });
}

#endif
