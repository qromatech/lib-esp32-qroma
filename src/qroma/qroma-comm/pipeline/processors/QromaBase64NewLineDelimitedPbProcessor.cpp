#include "QromaBase64NewLineDelimitedPbProcessor.h"
#include "../../pb-commands/IPbCommandHandler.h"
#include "../../../util/logger.h"
#include "../../../util/qbase64.h"


void QromaBase64NewLineDelimitedPbProcessor::reset() { }


uint32_t QromaBase64NewLineDelimitedPbProcessor::processBytes(const uint8_t * bytes, uint32_t byteCount, PbCommandsRegistry * pbCommandsRegistry, std::function<void(uint8_t*, uint32_t)> txFn) {
  
  
  // logInfo("QromaBase64NewLineDelimitedPbProcessor - PROCESSING PB COMMANDS - NO BASE 64");

  bool scanComplete = false;
  bool newLineFound = false;
  uint32_t newLineIndex = 0;
  uint32_t trimCount = 0;
  int scanIndex = 0;
  uint32_t numBytesConsumed = 0;

  while (scanIndex < byteCount && !scanComplete) {
    if (bytes[scanIndex] == '\n') {
      newLineFound = true;
      trimCount = scanIndex;
      newLineIndex = scanIndex;
      scanComplete = true;
      numBytesConsumed = newLineIndex + 1;
    }
    scanIndex++;
  }

  if (!scanComplete) {
    return 0;
  }

  auto decodedBufferLength = q_decode_base64(bytes, newLineIndex, _base64DecodeBuffer);

  logInfo("FOUND NEWLINE DELIMITED MESSAGE");

  auto base64EncodeAndTx = [this, txFn](uint8_t * bytes, uint32_t bytesLength) {
    logInfo("base64EncodeAndTx()");
    unsigned int encodedBufferLength = q_encode_base64(bytes, bytesLength, _base64EncodeBuffer);
    txFn(_base64EncodeBuffer, encodedBufferLength);
    txFn((uint8_t*)"\n", 1);
  };
  
  for (int i=0; i < pbCommandsRegistry->getCommandHandlersCount(); i++) {
    IPbCommandHandler * thisHandler = pbCommandsRegistry->getCommandHandler(i);
    uint32_t numBytesProcessed = thisHandler->handleBytes(_base64DecodeBuffer, decodedBufferLength, base64EncodeAndTx);
    if (numBytesProcessed > 0) {
      logInfo("PROCESSED BYTES");
      logInfo(numBytesConsumed);
      return numBytesConsumed;
    }
  }

  return 0;
}


// void QromaBase64NewLineDelimitedPbProcessor::base64EncodeAndTx() {

// }
