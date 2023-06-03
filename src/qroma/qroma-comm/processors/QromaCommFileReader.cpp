#include "LittleFS.h"
#include "QromaCommFileReader.h"
#include "../../util/logger.h"


void QromaCommFileReader::startFileReadingMode(uint32_t silenceDelayTimeoutInMs, FileData * fileData) {
  // _processingMode = QromaCommProcessingMode_FileReader;

  logInfo("READING SERIAL TO FILE");
  logInfo(fileData->filename);

  // // setCommReadingMode(CommReadingMode_FILE_FROM_COMM);

  uint32_t now = millis();
  _lastCommReadTimeInMs = now;
  _silenceDelayTimeoutInMs = silenceDelayTimeoutInMs;
  _readToBufferTimeoutInMs = now + silenceDelayTimeoutInMs;
  _readToBufferCount = 0;
  _readToBufferSize = fileData->filesize;
  _expectedChecksum = fileData->checksum;
  strncpy(_readToFileName, fileData->filename, sizeof _readToFileName);
}


uint32_t QromaCommFileReader::processBytes(const uint8_t * bytes, uint32_t byteCount) {
  return 0;
}


// bool QromaCommFileReader::processReadToBuffer() {
//   uint32_t now = millis();

//   logInfo("READ TO BUFFER");

//   int commBufferWriteIndex = cbGetCommBufferWriteIndex();
//   if (commBufferWriteIndex == _readToBufferCount &&
//       now > _readToBufferTimeoutInMs)
//   {
//     logInfo("READ TO BUFFER TIMEOUT");
//     setCommReadingMode(CommReadingMode_PB_COMMANDS);
//     return false;
//   }

//   _readToBufferCount = commBufferWriteIndex;
//   _readToBufferTimeoutInMs = now + _silenceDelayTimeoutInMs;
  
//   // const uint8_t * commBuffer = cbGetCommBuffer();

//   logInfo("COMM BUFFER INDEX");
//   logInfo(commBufferWriteIndex);
//   logInfo(_readToBufferSize);

//   if (commBufferWriteIndex < _readToBufferSize) {
//     return true;
//   }

//   switch (_commReadingMode) {
//     case CommReadingMode_FILE_FROM_COMM:
//       return finalizeReadToFileContents();
//       break;
//     case CommReadingMode_QROMA_DEVICE_CMD_FROM_COMM:
//       return finalizeReadToQromaDeviceCommand();
//       break;
//     case CommReadingMode_QROMA_POINT_CMD_FROM_COMM:
//       return finalizeReadToQromaPointCommand();
//       break;
//   }

//   return false;
// }


// bool QromaCommFileReader::finalizeReadToFileContents() {
//   const uint8_t * commBuffer = cbGetCommBuffer();

//   logInfo("ADD TO FILE");
//   File file = LittleFS.open(_readToFileName, FILE_WRITE);
//   if (!file) {
//     logInfo("NO FILE OPENED");
//     logInfo(_readToFileName);
//     sendReadSerialToFileResponse(false, 0);
//     return true;
//   }

//   bool writeSuccess = file.write(commBuffer, _readToBufferSize);
//   file.close();

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
  
//   cbRemoveFirstNFromBuffer(_readToBufferSize);
//   setCommReadingMode(CommReadingMode_PB_COMMANDS);  

//   return true;
// }
