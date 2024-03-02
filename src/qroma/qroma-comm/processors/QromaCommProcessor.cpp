#include "QromaCommProcessor.h"
#include <qroma/util/logger.h>



void QromaCommProcessor::init(IAppCommandProcessor * appCommandProcessor) {
  _processingMode = QromaCommProcessingMode_QromaCommands;
  _appCommandProcessor = appCommandProcessor;
}


void QromaCommProcessor::reset() {
  _processingMode = QromaCommProcessingMode_QromaCommands;
}


uint32_t QromaCommProcessor::processBytes(const uint8_t * bytes, uint32_t byteCount, std::function<void(const uint8_t*, uint32_t)> txFn) {

  if (_processingMode == QromaCommProcessingMode_StreamReader) {
    // logInfoIntWithDescription("STREAM PROCESS BYTES: ", byteCount);
    uint32_t numStreamBytesProcessed = _qromaCommStreamHandler.processBytes(bytes, byteCount);
    // logInfoIntWithDescription("QROMA COMM PROCESSOR STREAM MODE - NUM BYTES: ", numStreamBytesProcessed);
    return numStreamBytesProcessed;
  }

  bool newLineFound = false;
  uint32_t newLineIndex = 0;
  int scanIndex = 0;
  uint32_t numBytesConsumed = 0;

  while (scanIndex < byteCount && !newLineFound) {
    if (bytes[scanIndex] == '\n') {
      newLineFound = true;
      newLineIndex = scanIndex;
      numBytesConsumed = newLineIndex + 1;
    }
    scanIndex++;
  }

  if (!newLineFound) {
    return 0;
  }

  auto decodedBufferLength = q_decode_base64(bytes, newLineIndex, _base64DecodeBuffer);

  handleQromaCommCommand(_base64DecodeBuffer, decodedBufferLength, txFn);

  return numBytesConsumed;
}


uint32_t QromaCommProcessor::handleQromaCommCommand(uint8_t * bytes, uint32_t bytesLength, std::function<void(uint8_t*, uint32_t)> txFn) {
  QromaCommCommand qromaCommCommand = QromaCommCommand_init_zero;

  pb_istream_t istream = pb_istream_from_buffer(bytes, bytesLength);
  bool decoded = pb_decode(&istream, QromaCommCommand_fields, &qromaCommCommand);

  if (decoded) {
    QromaCommResponse qromaCommResponse = QromaCommResponse_init_zero;

    bool shouldSendQromaCommResponse = false;

    switch (qromaCommCommand.which_command) {
      case QromaCommCommand_appCommandBytes_tag: {
          _appCommandProcessor->processBytes(qromaCommCommand.command.appCommandBytes.bytes, qromaCommCommand.command.appCommandBytes.size, txFn, &qromaCommResponse);
          if (_appCommandProcessor->hasAppResponse()) {
            shouldSendQromaCommResponse = true;
            qromaCommResponse.which_response = QromaCommResponse_appResponseBytes_tag;
          }
        }
        break;
      case QromaCommCommand_fsCommand_tag:
        txFn((uint8_t *)"FS COMMAND", 10);

        shouldSendQromaCommResponse = _qromaFsCommandProcessor.handleFileSystemCommand(
            &(qromaCommCommand.command.fsCommand), 
            &qromaCommResponse, 
            txFn);

        txFn((uint8_t *)"DONE FS COMMAND\n", 16);

        break;
      case QromaCommCommand_streamCommand_tag:
        txFn((uint8_t *)"STREAM COMMAND", 14);

        _qromaCommStreamHandler.handleQromaStreamCommand(&(qromaCommCommand.command.streamCommand), txFn, this);

        txFn((uint8_t *)"DONE STREAM COMMAND\n", 20);
        break;
      case QromaCommCommand_commConfigCommand_tag:
        _qromaCommConfigProcessor.handleQromaCommConfigCommand(
          &(qromaCommCommand.command.commConfigCommand), 
          &qromaCommResponse, 
          txFn);
        shouldSendQromaCommResponse = true;
        qromaCommResponse.which_response = QromaCommResponse_commConfigResponse_tag;
        break;
    }

    if (shouldSendQromaCommResponse) {
        bool success = sendQromaCommResponse(&qromaCommResponse, txFn);
        if (!success) {
          return bytesLength;
        }
      }

      return bytesLength;
  } else {
    // unsuccessful decode after reading a newline
  }

  return 0;
}


void QromaCommProcessor::startStreamReadingMode() {
  _processingMode = QromaCommProcessingMode_StreamReader;
}
    
void QromaCommProcessor::endStreamReadingMode() {
  _processingMode = QromaCommProcessingMode_QromaCommands;
}


bool QromaCommProcessor::sendQromaCommResponse(QromaCommResponse * qromaCommResponse, std::function<void(uint8_t*, uint32_t)> txFn) {
  // logInfo("SENDING QROMACOMM RESPONSE");
  uint8_t encodeBuffer[1000];
  memset(encodeBuffer, 0, sizeof(encodeBuffer));

  pb_ostream_t ostream = pb_ostream_from_buffer(encodeBuffer, sizeof(encodeBuffer));
  bool encoded = pb_encode(&ostream, QromaCommResponse_fields, qromaCommResponse);
  if (!encoded) {
    logError("ERROR handleQromaCommCommand - handleBytes/encode");
    return false;
  }

  // logInfoIntWithDescription("QROMACOMM RESPONSE ENCODED: ", ostream.bytes_written);
  unsigned int b64EncodedBufferLength = q_encode_base64(encodeBuffer, ostream.bytes_written, _base64EncodeBuffer);
  _base64EncodeBuffer[b64EncodedBufferLength] = '\n';
  // logInfo("PRE-TX B64");
  txFn(_base64EncodeBuffer, b64EncodedBufferLength + 1);
  // logInfo("POST-TX B64");

  return true;
}
