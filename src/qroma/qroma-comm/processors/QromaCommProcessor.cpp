#include "QromaCommProcessor.h"



void QromaCommProcessor::init(IAppCommandProcessor * appCommandProcessor) {
  _processingMode = QromaCommProcessingMode_QromaCommands;
  _appCommandProcessor = appCommandProcessor;
}


uint32_t QromaCommProcessor::processBytes(const uint8_t * bytes, uint32_t byteCount, std::function<void(const uint8_t*, uint32_t)> txFn) {

  if (_processingMode == QromaCommProcessingMode_FileReader) {
    return _qromaFsCommandProcessor.processBytes(bytes, byteCount);
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

  // PbMessage appMessage;
  // memset(&appMessage, 0, sizeof(appMessage));

  pb_istream_t istream = pb_istream_from_buffer(bytes, bytesLength);
  bool decoded = pb_decode(&istream, QromaCommCommand_fields, &qromaCommCommand);

  if (decoded) {
    QromaCommResponse qromaCommResponse = QromaCommResponse_init_zero;

    switch (qromaCommCommand.which_command) {
      case QromaCommCommand_appCommandBytes_tag: {
          // txFn((uint8_t *)"APP COMMAND", 12);
          _appCommandProcessor->processBytes(qromaCommCommand.command.appCommandBytes.bytes, qromaCommCommand.command.appCommandBytes.size, txFn, &qromaCommResponse);
          if (_appCommandProcessor->hasAppResponse()) {
            qromaCommResponse.which_response = QromaCommResponse_appResponseBytes_tag;
            // uint32_t responseBytesCount = _appCommandProcessor->setAppResponse(&(qromaCommResponse.response.appResponseBytes.bytes));
            // qromaCommResponse.response.appResponseBytes.size = responseBytesCount;
            // qromaCommResponse.response.appResponseBytes.size = _appCommandProcessor->getAppResponseByteCount();
          }
        }
        break;
      case QromaCommCommand_fsCommand_tag:
        txFn((uint8_t *)"FS COMMAND", 10);

        _qromaFsCommandProcessor.handleFileSystemCommand(
            &(qromaCommCommand.command.fsCommand), 
            &qromaCommResponse, 
            txFn,
            this);

        // handleFileSystemCommand(&(qromaCommCommand.command.fsCommand));
        // _qromaFsCommandProcessor.
        // handleQromaCommFileSystemCommand(&(qromaCommCommand.command.fsCommand), &qromaCommResponse);
        break;
      case QromaCommCommand_commConfigCommand_tag:
        // txFn((uint8_t *)"COMM COMMAND", 12);

        // handleQromaCommConfigCommand(&(qromaCommCommand.command.commConfigCommand), &qromaCommResponse);
        _qromaCommConfigProcessor.handleQromaCommConfigCommand(&(qromaCommCommand.command.commConfigCommand), &qromaCommResponse, txFn);
        break;
    }

    uint8_t encodeBuffer[2000];
    memset(encodeBuffer, 0, sizeof(encodeBuffer));

    pb_ostream_t ostream = pb_ostream_from_buffer(encodeBuffer, sizeof(encodeBuffer));
    bool encoded = pb_encode(&ostream, QromaCommResponse_fields, &qromaCommResponse);
    if (!encoded) {
      logError("ERROR handleQromaCommCommand - handleBytes/encode");
      return 0;
    }

    txFn(encodeBuffer, ostream.bytes_written);
    return bytesLength;
  } else {
    // unsuccessful decode after reading a newline
  }

  return 0;
}


void QromaCommProcessor::startFileReadingMode(uint32_t silenceDelayTimeoutInMs, FileData * fileData) {
  _processingMode = QromaCommProcessingMode_FileReader;

  logInfo("READING SERIAL TO FILE");
  logInfo(fileData->filename);

  // // setCommReadingMode(CommReadingMode_FILE_FROM_COMM);

  // uint32_t now = millis();
  // _lastCommReadTimeInMs = now;
  // _silenceDelayTimeoutInMs = silenceDelayTimeoutInMs;
  // _readToBufferTimeoutInMs = now + silenceDelayTimeoutInMs;
  // _readToBufferCount = 0;
  // _readToBufferSize = fileData->filesize;
  // _expectedChecksum = fileData->checksum;
  // strncpy(_readToFileName, fileData->filename, sizeof _readToFileName);
}
    
void QromaCommProcessor::endFileReadingMode() {
  _processingMode = QromaCommProcessingMode_QromaCommands;
}


// uint32_t QromaCommProcessor::handleAppCommand(PbMessage * pbMessage, QromaCommResponse * qromaCommResponse) {

//   PbResponse appCommandResponse;
//   _handlerFunction(pbMessage, &appCommandResponse);
  
//   memset(&(qromaCommResponse->response.appResponseBytes), 0, sizeof(qromaCommResponse->response.appResponseBytes));

//   pb_ostream_t ostream = pb_ostream_from_buffer(
//     qromaCommResponse->response.appResponseBytes.bytes,
//     sizeof(qromaCommResponse->response.appResponseBytes.bytes)
//   );
//   bool encoded = pb_encode(&ostream, PbResponseFields, &appCommandResponse);
//   if (!encoded) {
//     logError("ERROR handleAppCommand - handleBytes/encode");
//     return false;
//   }

//   qromaCommResponse->response.appResponseBytes.size = ostream.bytes_written;
//   qromaCommResponse->which_response = QromaCommResponse_appResponseBytes_tag;

//   return 0;
// }


// uint32_t handleQromaCommFileSystemCommand(FileSystemCommand * command, QromaCommResponse * response) {

//   return 0;
// }
// uint32_t handleQromaCommFileSystemCommand(FileSystemCommand * command, QromaCommResponse * response);

// uint32_t handleQromaCommConfigCommand(QromaCommConfigCommand * command, QromaCommResponse * response) {
//   switch (command->which_command) {
//     case QromaCommConfigCommand_setLogLevel_tag:
//       setLogLevel(command->command.setLogLevel.logLevel);
//       break;
//   }
//   return 0;
// }
