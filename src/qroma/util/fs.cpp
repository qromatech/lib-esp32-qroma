#include "fs.h"
#include "LittleFS.h"
#include "logger.h"
#include <CRC32.h>


void initFileSystem() {
  logInfo("INIT FILE SYS");

  if (!LittleFS.begin(true)) {
    logError("An Error has occurred while mounting SPIFFS");
    return;
  }

  logInfo("INIT FILE SYS COMPLETE");
}


uint32_t getFileChecksum(const char * fname) {
  // logInfo("getFileChecksum()");
  // logInfo(fname);

  CRC32 crc;
  
  File file = LittleFS.open(fname);
  for (int i = 0; i < file.size(); i++) {
    char c = file.read();
    crc.update(c);
  }

  uint32_t checksum = crc.finalize();
  // logInfoIntWithDescription("CHECKSUM VALUE: ", checksum);

  return checksum;
}


bool resetFilesystem() {
  logInfo("INITIATING FILE SYSTEM RESET");
  logInfo("OPENING");

  bool errorOccurred = false;

  File root = LittleFS.open("/");
  logInfo("ROOT OPEN");
  if (root == NULL) {
    logError("ROOT NULL");
    errorOccurred = true;
  }
  logInfo(root.name());
 
  logInfo("NEXT FILE");
  File file = root.openNextFile();
  if (file == NULL) {
    logError("FILE NULL");
    errorOccurred = true;
  } else {
    logInfo("FILE >>");
    logInfo(file.name());
  }
 
  while(file) {  
    logInfo("FILE: ");
    logInfo(file.name());
    LittleFS.remove(file.name());

    file = root.openNextFile();
  }
  logInfo("FILE SYSTEM RESET COMPLETE");

  return !errorOccurred;
}


bool doesFileExist(const char * fname) {
  return LittleFS.exists(fname);
}