#include "LittleFS.h"
#include "QromaCommFileReader.h"
#include <qroma/util/logger.h>


void QromaCommFileReader::startFileReadingMode(uint32_t silenceDelayTimeoutInMs, FileData * fileData) {

  logInfo("READING SERIAL TO FILE");
  logInfo(fileData->filename);

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
