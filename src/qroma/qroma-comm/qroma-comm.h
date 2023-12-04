#ifndef QROMA_MODULE__COMM_H
#define QROMA_MODULE__COMM_H

#include <pb.h>
#include <pb_encode.h>
#include <functional>
#include <qroma/util/qbase64.h>
#include <qroma/util/logger.h>
#include <qroma/qroma-app/IQromaSerialCommApp.h>


template <typename PbMessage, const pb_msgdesc_t *PbMessageFields>
bool sendSerialPbMessage(PbMessage* message, std::function<void(uint8_t*, uint32_t)> responseFn)
{
  uint8_t buffer[2000];
  memset(buffer, 0, sizeof(buffer));
  
  pb_ostream_t stream = pb_ostream_from_buffer(buffer, sizeof(buffer));
  bool encoded = pb_encode(&stream, PbMessageFields, message);
  if (!encoded) {
    logError("ERROR ENCODING STATUS DATA - sendSerialPbMessage");
    return false;
  }

  responseFn(buffer, stream.bytes_written);

  return true;
}


template <typename PbMessage, const pb_msgdesc_t *PbMessageFields>
bool sendSerialPb64NewLineMessage(PbMessage* message, std::function<void(uint8_t*, uint32_t)> responseFn)
{
  uint8_t buffer[2000];
  memset(buffer, 0, sizeof(buffer));
  
  pb_ostream_t stream = pb_ostream_from_buffer(buffer, sizeof(buffer));
  bool encoded = pb_encode(&stream, PbMessageFields, message);
  if (!encoded) {
    logError("ERROR ENCODING STATUS DATA - sendSerialPb64NewLineMessage");
    return false;
  }

  uint8_t base64EncodeBuffer[3000];
  memset(base64EncodeBuffer, 0, sizeof(base64EncodeBuffer));

  unsigned int encodedBufferLength = q_encode_base64(buffer, stream.bytes_written, base64EncodeBuffer);

  responseFn(base64EncodeBuffer, encodedBufferLength);
  responseFn((uint8_t*)"\n", 1);

  return true;
}



template <typename PbMessage, const pb_msgdesc_t *PbMessageFields>
bool sendSerialPbMessage(PbMessage* message, IQromaSerialCommApp * app)
{
  return sendSerialPbMessage<PbMessage, PbMessageFields>(message, 
    [app](const uint8_t * bytes, uint32_t byteCount) {
      app->getSerialTx()->serialTxBytes(bytes, byteCount);
    });
}


template <typename PbMessage, const pb_msgdesc_t *PbMessageFields>
bool sendSerialPb64NewLineMessage(PbMessage* message, IQromaSerialCommApp * app)
{
  return sendSerialPb64NewLineMessage<PbMessage, PbMessageFields>(message, 
    [app](const uint8_t * bytes, uint32_t byteCount) {
      app->getSerialTx()->serialTxBytes(bytes, byteCount);
    });
}

void qromaAppSerialPrint(const char * msg, IQromaSerialCommApp * app);

void qromaAppSerialPrintln(const char * msg, IQromaSerialCommApp * app);


bool saveQromaCommConfig();


#endif
