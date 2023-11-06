#include "qroma-persist.h"
#include "LittleFS.h"


size_t loadDataFromPersistence(const char * filename, pb_byte_t * buffer, uint32_t bufferSize) {
  logInfo("OPENING FILE TO LOAD");
  logInfo(filename);

  File file = LittleFS.open(filename);
  
  if (!file){
    logError("Failed to open config file for reading");
    return -1;
  }

  logInfo("FILE OPENED");
  logInfo("READING CONFIG FILE");
  size_t fileSize = file.size();
  logInfo(fileSize);

  if (file.size() > bufferSize) {
    logError("BUFFER NOT BIG ENOUGH TO READ FILE");
    logError(filename);
    logError(fileSize);
    logError(bufferSize);
    return -1;
  }

  file.read(buffer, fileSize);
  
  file.close();

  logInfo("CONFIG FILE LOADED");
  logInfo(fileSize);

  return fileSize;
}


bool saveDataToPersistence(const char * filename, pb_byte_t * data, uint32_t dataLength) {
  File file = LittleFS.open(filename, FILE_WRITE);
  if (!file) {
    logError("Error in saveDataToPersistence()");
    logError(filename);
    logError(dataLength);
    return false;
  }

  logInfo("SAVING FILE");
  logInfo(filename);
  logInfo(dataLength);

  bool writeSuccess = file.write(data, dataLength);
  file.close();

  if (writeSuccess) {
    logInfo("CONFIG STORE SUCCESS");
    logInfo(filename);
  } else {
    logInfo("CONFIG STORE ERROR");
    logInfo(filename);
  }
  
  return writeSuccess;
}
