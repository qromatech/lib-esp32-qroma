// // #include <freertos/FreeRTOS.h>
// #include <RTOS.h>
// #include <pb_encode.h>
// #include <pb_decode.h>

// #include "pbBufferCommProcessor.h"
// #include "../util/fs.h"
// #include "../util/logger.h"
// #include "SPIFFS.h"
// #include "comm_buffer.h"
// // #include "pbUartBleComm.h"
// #include "fs_comm_handlers.h"
// #include "serialCommand.h"
// // #include "../constants.h"
// // #include "../config/persist.h"


// QromaCommCommand _commPbQromaCommCommand = QromaCommCommand_init_zero;
// const uint32_t COMM_SILENCE_DELAY_TO_CLEAR_BUFFER = 3000;


// void PbBufferCommProcessor::doPbCommSetup() {
//   logInfo("PB COMM STARTUP");
//   cbResetCommBuffer();
//   _commReadingMode = CommReadingMode_PB_COMMANDS;
// }


// void PbBufferCommProcessor::pbSendBytes(uint8_t * values, uint32_t count) {
//   getPbSerialComm()->pbSendBytes(values, count);
//   // getPbUartBleComm()->pbSendBytes(values, count);
// }


// void PbBufferCommProcessor::pbSendMessage(const char * msg) {
//   pbSendLine(msg, "");
// }


// void PbBufferCommProcessor::pbSendLine(const char * msg, const char * value) {
//   char msgBuffer[200];
//   memset(msgBuffer, 0, sizeof msgBuffer);

//   strlcpy(msgBuffer, msg, sizeof msgBuffer);
//   strlcat(msgBuffer, value, sizeof msgBuffer);
//   size_t len = strlcat(msgBuffer, "\n", sizeof msgBuffer);
  
//   pbSendBytes((uint8_t *)msgBuffer, len);
// }


// void PbBufferCommProcessor::pbSendIntMessageLine(const char * msg, int value) {
//   char vBuf[20];
//   sprintf(vBuf, "%d", value);
  
//   pbSendLine(msg, vBuf);
// }


// void PbBufferCommProcessor::pbSendQromacommResponse(uint8_t * values, uint32_t count) {
//   QromaCommHeader qch;
//   qch.messageSize = count;
//   uint8_t buffer[50];
//   memset(buffer, 0, sizeof buffer);
//   pb_ostream_t stream = pb_ostream_from_buffer(buffer, sizeof(buffer));
//   bool status = pb_encode(&stream, QromaCommHeader_fields, &qch);

//   if (!status) {
//     logError("Error encoding response in pbSendQromacommResponse()");
//   }

//   pbSendBytes(buffer, (uint32_t)stream.bytes_written);
//   pbSendBytes(values, count);
// }


// int PbBufferCommProcessor::checkForNewQromaCommCommand(QromaCommCommand * cmd) {
//   int commBufferWriteIndex = cbGetCommBufferWriteIndex();
//   const uint8_t * commBuffer = cbGetCommBuffer();

//   for (int i=1; i <= commBufferWriteIndex; i++) {
//     pb_istream_t stream = pb_istream_from_buffer(commBuffer, i);
//     bool decoded = pb_decode(&stream, QromaCommCommand_fields, cmd);

//     if (decoded) {
//       cbRemoveFirstNFromBuffer(i);
//       logInfo("REMOVE N FROM BUFFER");
//       logInfo(i);
//       logInfo(commBufferWriteIndex - i);
//       return i;
//     }
//   }

//   return -1;
// }


// void PbBufferCommProcessor::handleClearToSendQuery(ClearToSendQuery * ctsQuery) {
//   logInfo("CTSQUERY");
//   logInfo(ctsQuery->ctsRandomValue);

//   QromaCommResponse response;
//   response.which_response = QromaCommResponse_clearToSendResponse_tag;
//   response.response.clearToSendResponse.ctsRandomValue = ctsQuery->ctsRandomValue;

//   uint8_t buffer[200];
//   memset(buffer, 0, sizeof buffer);
//   pb_ostream_t stream = pb_ostream_from_buffer(buffer, sizeof(buffer));
//   bool status = pb_encode(&stream, QromaCommResponse_fields, &response);

//   if (!status) {
//     logError("UNABLE TO ENCODE ClearToSendResponse");
//   }

//   pbSendBytes(buffer, stream.bytes_written);
// }


// bool PbBufferCommProcessor::processPbCommands() {

//   int validBufferSize = checkForNewQromaCommCommand(&_commPbQromaCommCommand);
//   if (validBufferSize <= 0) {
//     return false;
//   }

//   QromaCommCommand * cmd = &_commPbQromaCommCommand;

//   switch (cmd->which_command)
//   {
//     case QromaCommCommand_clearToSendQuery_tag:
//       logInfo("CTS QUERY - LC");
//       handleClearToSendQuery(&(cmd->command.clearToSendQuery));
//       break;

//     case QromaCommCommand_fsCommand_tag:
//       logInfo("FILESYS - LC");
//       handleFileSystemCommand(&(cmd->command.fsCommand), this);
//       break;

//     default:
//       break;
//   }

//   return true;
// }


// bool PbBufferCommProcessor::processReadToFile() {
//   uint32_t now = millis();

//   logInfo("READ TO FILE");

//   int commBufferWriteIndex = cbGetCommBufferWriteIndex();
//   if (commBufferWriteIndex == _readToFileCount &&
//       now > _readToFileTimeoutInMs)
//   {
//     logInfo("READ TO FILE TIMEOUT");
//     setCommReadingMode(CommReadingMode_PB_COMMANDS);
//     return false;
//   }

//   _readToFileCount = commBufferWriteIndex;
//   _readToFileTimeoutInMs = now + _silenceDelayTimeoutInMs;
  
//   const uint8_t * commBuffer = cbGetCommBuffer();

//   logInfo("COMM BUFFER INDEX");
//   logInfo(commBufferWriteIndex);
//   logInfo(_readToFileSize);

//   if (commBufferWriteIndex < _readToFileSize) {
//     return true;
//   }

//   logInfo("ADD TO FILE");
//   File file = SPIFFS.open(_readToFileName, FILE_WRITE);
//   if (!file) {
//     logInfo("NO FILE OPENED");
//     logInfo(_readToFileName);
//     cbRemoveFirstNFromBuffer(_readToFileSize);
//     sendReadSerialToFileResponse(false, 0);
//     return true;
//   }

//   bool writeSuccess = file.write(commBuffer, _readToFileSize);
//   file.close();

//   cbRemoveFirstNFromBuffer(_readToFileSize);

//   logInfoIntWithDescription("FILE WRITE COMPLETE: ", writeSuccess);

//   if (writeSuccess) {
//     logInfo("WROTE FILE - COMM BUFFER");
//     logInfo(_readToFileName);
//   } else {
//     logInfo("ERR WRITE FILE");
//     logInfo(_readToFileName);

//     sendReadSerialToFileResponse(false, 0);
//     return true;
//   }

//   uint32_t crc = getFileChecksum(_readToFileName);

//   sendReadSerialToFileResponse(writeSuccess, crc);

//   return true;
// }


// void PbBufferCommProcessor::sendReadSerialToFileResponse(bool success, uint32_t crc) {
//   setCommReadingMode(CommReadingMode_PB_COMMANDS);

//   QromaCommResponse response;
//   response.which_response = QromaCommResponse_fsResponse_tag;
//   response.response.fsResponse.which_response = FileSystemResponse_storeUpcomingFileDataResponse_tag;

//   response.response.fsResponse.response.storeUpcomingFileDataResponse.success = success;
//   response.response.fsResponse.response.storeUpcomingFileDataResponse.bytesWritten = _readToFileCount;
//   strncpy(response.response.fsResponse.response.storeUpcomingFileDataResponse.command.filename, _readToFileName, 
//     sizeof(response.response.fsResponse.response.storeUpcomingFileDataResponse.command.filename));
//   response.response.fsResponse.response.storeUpcomingFileDataResponse.command.filesize = _readToFileSize;
//   response.response.fsResponse.response.storeUpcomingFileDataResponse.command.checksum = crc;

//   uint8_t buffer[2000];
//   memset(buffer, 0, sizeof buffer);
//   pb_ostream_t stream = pb_ostream_from_buffer(buffer, sizeof(buffer));
//   bool status = pb_encode(&stream, QromaCommResponse_fields, &response);

//   if (!status) {
//     logInfo("UNABLE TO ENCODE StoreUpcomingFileDataCommand RESPONSE");
//   } else {
//     logInfoIntWithDescription("STORE FILE RESP: ", stream.bytes_written);
//     logInfo("STORE FILE RESP: ");
//     logInfo(stream.bytes_written);
//   }

//   pbSendQromacommResponse(buffer, (uint32_t)stream.bytes_written);
// }


// bool PbBufferCommProcessor::processCommBuffer() {
//   int commBufferWriteIndex = cbGetCommBufferWriteIndex();
//   if (commBufferWriteIndex == 0) {
//     return false;
//   }

//   int now = millis();
//   int bufferExpirationTime = cbGetLastTimeAddedToInMs() + COMM_SILENCE_DELAY_TO_CLEAR_BUFFER;
//   if (now > bufferExpirationTime) {
//     logInfo("processCommBuffer EXPIRED");
//     setCommReadingMode(CommReadingMode_PB_COMMANDS);
//     cbResetCommBuffer();
//     return false;
//   }

//   switch (_commReadingMode) {
//     case CommReadingMode_PB_COMMANDS:
//       logInfo("Mode_PB_COMMANDS");
//       return processPbCommands();
//       break;
//     case CommReadingMode_FILE_FROM_COMM:
//       logInfo("Mode_FILE_FROM_COMM");
//       return processReadToFile();
//       break;
//     case CommReadingMode_NOT_SET:
//       logError("Mode_NOT_SET");
//       break;
//     default:
//       logError("Unrecognized Mode");
//   }
//   return false;
// }


// void PbBufferCommProcessor::setCommReadingMode(CommReadingMode mode) {
//   _commReadingMode = mode;
// }


// void PbBufferCommProcessor::readSerialToFile(uint32_t silenceDelayTimeoutInMs, FileData * fileData) {
//   logInfo("READING SERIAL TO FILE");
//   logInfo(fileData->filename);

//   setCommReadingMode(CommReadingMode_FILE_FROM_COMM);

//   uint32_t now = millis();
//   _lastCommReadTimeInMs = now;
//   _silenceDelayTimeoutInMs = silenceDelayTimeoutInMs;
//   _readToFileTimeoutInMs = now + silenceDelayTimeoutInMs;
//   _readToFileCount = 0;
//   _readToFileSize = fileData->filesize;
//   _expectedChecksum = fileData->checksum;
//   strncpy(_readToFileName, fileData->filename, sizeof _readToFileName);
// }


// void PbBufferCommProcessor::setPbBuildingMessage(bool buildingMessage) {
//   getPbSerialComm()->setPbBuildingMessage(buildingMessage);
//   // getPbUartBleComm()->setPbBuildingMessage(buildingMessage);
// }
