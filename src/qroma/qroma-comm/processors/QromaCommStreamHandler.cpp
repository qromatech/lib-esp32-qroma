#include "QromaCommStreamHandler.h"
#include <qroma/util/logger.h>
#include <qroma/util/fs.h>


void QromaCommStreamHandler::handleQromaStreamCommand(QromaStreamCommand * streamCommand, 
  std::function<void(uint8_t*, uint32_t)> txFn, IQromaCommStreamRxHandler * streamRxHandler) 
{
  switch (streamCommand->which_command) {
    case QromaStreamCommand_initWriteFileStreamCommand_tag:
      handleInitWriteFileStreamCommand(&(streamCommand->command.initWriteFileStreamCommand),
        txFn, streamRxHandler);
      break;
    case QromaStreamCommand_initReadFileStreamCommand_tag:
      handleInitReadFileStreamCommand(&(streamCommand->command.initReadFileStreamCommand),
        txFn, streamRxHandler);
      break;
    default:
      logError("UNRECOGNIZED STREAM COMMAND");
      logError(streamCommand->which_command);
  }
}


void QromaCommStreamHandler::populateInitWriteFileStreamAckResponse(QromaCommResponse * response,
  bool success, const char * message, uint32_t fileStreamId)
{
  response->which_response = QromaCommResponse_streamResponse_tag;
  response->response.streamResponse.which_response = QromaStreamResponse_initWriteFileStreamAckResponse_tag;
  
  response->response.streamResponse.response.initWriteFileStreamAckResponse.success = success;
  strncpy(response->response.streamResponse.response.initWriteFileStreamAckResponse.message,
    message,
    sizeof(response->response.streamResponse.response.initWriteFileStreamAckResponse.message));
  response->response.streamResponse.response.initWriteFileStreamAckResponse.fileStreamId = fileStreamId;
}


void QromaCommStreamHandler::populateWriteFileStreamCompleteWithErrResponse(QromaCommResponse * response,
  const char * message, uint32_t fileStreamId)
{
  response->which_response = QromaCommResponse_streamResponse_tag;
  response->response.streamResponse.which_response = QromaStreamResponse_writeFileStreamCompleteResponse_tag;
  
  response->response.streamResponse.response.writeFileStreamCompleteResponse.success = false;
  strncpy(response->response.streamResponse.response.writeFileStreamCompleteResponse.message,
    message,
    sizeof(response->response.streamResponse.response.writeFileStreamCompleteResponse.message));
  response->response.streamResponse.response.writeFileStreamCompleteResponse.fileStreamId = fileStreamId;

  response->response.streamResponse.response.writeFileStreamCompleteResponse.has_fileData = false;
}


void QromaCommStreamHandler::populateWriteFileStreamCompleteSuccessResponse(QromaCommResponse * response,
  const char * message, uint32_t fileStreamId, uint32_t crc)
{
  response->which_response = QromaCommResponse_streamResponse_tag;
  response->response.streamResponse.which_response = QromaStreamResponse_writeFileStreamCompleteResponse_tag;
  
  response->response.streamResponse.response.writeFileStreamCompleteResponse.success = true;
  strncpy(response->response.streamResponse.response.writeFileStreamCompleteResponse.message,
    message,
    sizeof(response->response.streamResponse.response.writeFileStreamCompleteResponse.message));
  response->response.streamResponse.response.writeFileStreamCompleteResponse.fileStreamId = fileStreamId;

  response->response.streamResponse.response.writeFileStreamCompleteResponse.has_fileData = true;
  response->response.streamResponse.response.writeFileStreamCompleteResponse.fileData.checksum = crc;
  response->response.streamResponse.response.writeFileStreamCompleteResponse.fileData.filesize = _expectedFileSize;

  strncpy(response->response.streamResponse.response.writeFileStreamCompleteResponse.fileData.filename,
    _readToFileName,
    sizeof(response->response.streamResponse.response.writeFileStreamCompleteResponse.fileData.filename));
}


void QromaCommStreamHandler::handleInitWriteFileStreamCommand(InitWriteFileStreamCommand * command,
  std::function<void(uint8_t*, uint32_t)> txFn, IQromaCommStreamRxHandler * streamRxHandler)
{
  _streamToFile = LittleFS.open(command->fileData.filename, FILE_WRITE);
  if (!_streamToFile) {
    logInfo("COULD NOT OPEN FILE TO STREAM");
    logInfo(command->fileData.filename);
    
    QromaCommResponse response;
    populateInitWriteFileStreamAckResponse(&response, false, "Err opening file to stream", command->fileStreamId);

    streamRxHandler->sendQromaCommResponse(&response, txFn);
    return;
  }

  _txFn = txFn;
  _streamRxHandler = streamRxHandler;

  _streamRxHandler->startStreamReadingMode();

  strncpy(_readToFileName, command->fileData.filename, sizeof(_readToFileName));
  _expectedChecksum = command->fileData.checksum;
  _expectedFileSize = command->fileData.filesize;
  _fileStreamId = command->fileStreamId;
  _numberOfBytesWrittenSoFar = 0;
  _lastCommReadTimeInMs = millis();

  QromaCommResponse response;
  populateInitWriteFileStreamAckResponse(&response, true, "ACK", command->fileStreamId);

  _streamRxHandler->sendQromaCommResponse(&response, _txFn);
}


uint32_t QromaCommStreamHandler::processBytes(const uint8_t * bytes, uint32_t byteCount) {

  // logInfoIntWithDescription("PROCESSING STREAM BYTES: ", byteCount);

  uint32_t numBytesRemainingToWrite = _expectedFileSize - _numberOfBytesWrittenSoFar;

  // logInfoIntWithDescription("REMAINING STREAM BYTES: ", numBytesRemainingToWrite);

  if (numBytesRemainingToWrite > byteCount) {
    // we won't be done writing, but we're going to write what we got
    // logInfo("WRITING NEXT BYTES");
    // logInfo(byteCount);
    // logInfo(numBytesRemainingToWrite);

    bool writeSuccess = _streamToFile.write(bytes, byteCount);

    if (!writeSuccess) {
      QromaCommResponse response;
      populateWriteFileStreamCompleteWithErrResponse(&response, "Err writing to file", _fileStreamId);
      _streamRxHandler->sendQromaCommResponse(&response, _txFn);
      _streamRxHandler->endStreamReadingMode();
      
      logError("WRITING BYTES FAILED");
      logError(numBytesRemainingToWrite);
      logError(byteCount);
    }

    _numberOfBytesWrittenSoFar += byteCount;

    // logInfoIntWithDescription("WROTE BYTES TO FILE: ", byteCount);
    // logInfoIntWithDescription("BYTES WRITTEN SO FAR: ", _numberOfBytesWrittenSoFar);

    return byteCount;
  }

  logInfoIntWithDescription("WRITING FINAL STREAM BYTES: ", numBytesRemainingToWrite);
  _streamRxHandler->endStreamReadingMode();

  // no more bytes to read after this
  bool writeSuccess = _streamToFile.write(bytes, numBytesRemainingToWrite);
  _streamToFile.close();

  QromaCommResponse response;
  
  if (!writeSuccess) {
    populateWriteFileStreamCompleteWithErrResponse(&response, "Err doing final write to file", _fileStreamId);
    _streamRxHandler->sendQromaCommResponse(&response, _txFn);
    
    return numBytesRemainingToWrite;
  } 
  
  uint32_t crc = getFileChecksum(_readToFileName);

  if (crc != _expectedChecksum) {
    populateWriteFileStreamCompleteWithErrResponse(&response, "File written. Checksum error", _fileStreamId);
    _streamRxHandler->sendQromaCommResponse(&response, _txFn);
    
    return numBytesRemainingToWrite;
  }

  populateWriteFileStreamCompleteSuccessResponse(&response, "File written successfully", _fileStreamId, crc);
  _streamRxHandler->sendQromaCommResponse(&response, _txFn);

  return numBytesRemainingToWrite;
}


void QromaCommStreamHandler::handleInitReadFileStreamCommand(InitReadFileStreamCommand * command,
  std::function<void(uint8_t*, uint32_t)> txFn, IQromaCommStreamRxHandler * streamRxHandler)
{
  logInfo("START handleInitReadFileStreamCommand()");
  logInfo(command->filePath);

  QromaCommResponse ackResponse;
  ackResponse.which_response = QromaCommResponse_streamResponse_tag;
  ackResponse.response.streamResponse.which_response = QromaStreamResponse_initReadFileStreamAckResponse_tag;
  ackResponse.response.streamResponse.response.initReadFileStreamAckResponse.fileStreamId = command->fileStreamId;
  
  File file = LittleFS.open(command->filePath);

  bool ableToSend = true;

  if (file == NULL) {
    logError("handleInitReadFileStreamCommand - failed to open file");
    logError(command->filePath);
    logError("FILE IS NULL");
    ackResponse.response.streamResponse.response.initReadFileStreamAckResponse.fileStatus = GetFileStatusCode_GFSC_ERR_OPEN_FILE;
    strncpy(ackResponse.response.streamResponse.response.initReadFileStreamAckResponse.message,
      "Failed to open file",
      sizeof(ackResponse.response.streamResponse.response.initReadFileStreamAckResponse.message));
    ableToSend = false;
  }

  if (file.isDirectory()) {
    logError("handleInitReadFileStreamCommand - not a file; it's a directory");
    logError(command->filePath);
    logError("GOT DIRECTORY");
    ackResponse.response.streamResponse.response.initReadFileStreamAckResponse.fileStatus = GetFileStatusCode_GFSC_ERR_INVALID_FILE_PATH;
    strncpy(ackResponse.response.streamResponse.response.initReadFileStreamAckResponse.message,
      "Not a file; it's a directory",
      sizeof(ackResponse.response.streamResponse.response.initReadFileStreamAckResponse.message));
    ableToSend = false;
  }

  if (!ableToSend) {
    ackResponse.response.streamResponse.response.initReadFileStreamAckResponse.has_fileData = false;
    file.close();
    streamRxHandler->sendQromaCommResponse(&ackResponse, txFn);
    return;
  }

  int fileSize = file.size();
  uint32_t checkSum = getFileChecksum(command->filePath);

  ackResponse.response.streamResponse.response.initReadFileStreamAckResponse.fileStatus = GetFileStatusCode_GFSC_FILE_EXISTS;
  ackResponse.response.streamResponse.response.initReadFileStreamAckResponse.has_fileData = true;
  strncpy(ackResponse.response.streamResponse.response.initReadFileStreamAckResponse.message,
    "OK to download",
    sizeof(ackResponse.response.streamResponse.response.initReadFileStreamAckResponse.message));
  strncpy(ackResponse.response.streamResponse.response.initReadFileStreamAckResponse.fileData.filename,
    command->filePath,
    sizeof(ackResponse.response.streamResponse.response.initReadFileStreamAckResponse.fileData.filename));
  ackResponse.response.streamResponse.response.initReadFileStreamAckResponse.fileData.filesize = fileSize;
  ackResponse.response.streamResponse.response.initReadFileStreamAckResponse.fileData.checksum = checkSum;

  // logInfo("PRE SEND ACK");
  streamRxHandler->sendQromaCommResponse(&ackResponse, txFn);
  // logInfo("POST SEND ACK");

  QromaCommResponse completeQcResponse;
  completeQcResponse.which_response = QromaCommResponse_streamResponse_tag;
  completeQcResponse.response.streamResponse.which_response = QromaStreamResponse_readFileStreamCompleteResponse_tag;
  completeQcResponse.response.streamResponse.response.readFileStreamCompleteResponse.fileStreamId = command->fileStreamId;
  strncpy(completeQcResponse.response.streamResponse.response.initReadFileStreamAckResponse.message,
    "Stream complete",
    sizeof(completeQcResponse.response.streamResponse.response.initReadFileStreamAckResponse.message));
  strncpy(completeQcResponse.response.streamResponse.response.readFileStreamCompleteResponse.fileData.filename,
    command->filePath,
    sizeof(completeQcResponse.response.streamResponse.response.readFileStreamCompleteResponse.fileData.filename));
  completeQcResponse.response.streamResponse.response.initReadFileStreamAckResponse.fileData.filesize = fileSize;
  completeQcResponse.response.streamResponse.response.initReadFileStreamAckResponse.fileData.checksum = checkSum;

  uint32_t chunkSize = 5000;
  uint32_t sendDelayInMs = 40;

  // logInfo("PRE SEND STREAM");
  bool success = doStreamSendFile(file, txFn, chunkSize, sendDelayInMs);
  // logInfo("POST SEND STREAM");

  completeQcResponse.response.streamResponse.response.readFileStreamCompleteResponse.success = success;

  streamRxHandler->sendQromaCommResponse(&completeQcResponse, txFn);

  if (!success) {
    logError("UNSUCCESSFUL STREAMING FILE CONTENTS");
  }
}


bool QromaCommStreamHandler::doStreamSendFile(File file, std::function<void(uint8_t*, uint32_t)> txFn, uint32_t chunkSize, uint32_t sendDelayInMs)
{
  const TickType_t sendDelay = sendDelayInMs / portTICK_PERIOD_MS;
  char chunk[chunkSize];
  bool isFirstSend = true;
  int bytesRead;

  while ((bytesRead = file.readBytes(chunk, chunkSize)) > 0) {
    if (isFirstSend) {
      isFirstSend = false;
    } else {
      vTaskDelay(sendDelay);
    }
    txFn((uint8_t*)chunk, bytesRead);
  }

  return true;
}
