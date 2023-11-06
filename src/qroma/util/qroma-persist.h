#ifndef CONFIG_PERSIST_H
#define CONFIG_PERSIST_H

#include <pb_decode.h>
#include <pb_encode.h>
#include <qroma/qroma.h>


#define QROMASTRIP_CONFIG_BUFFER_LOAD_SIZE   3000


size_t loadDataFromPersistence(const char * filename, pb_byte_t * buffer, uint32_t bufferSize);
bool saveDataToPersistence(const char * filename, pb_byte_t * data, uint32_t dataLength);


template <typename T>
bool loadPbFromPersistence(T * config, const char * filename, const pb_msgdesc_t * fields) {
  
  pb_byte_t buffer[QROMASTRIP_CONFIG_BUFFER_LOAD_SIZE];
  int size = loadDataFromPersistence(filename, buffer, QROMASTRIP_CONFIG_BUFFER_LOAD_SIZE);

  pb_istream_t stream = pb_istream_from_buffer(buffer, size);
  bool status = pb_decode(&stream, fields, config);

  if (!status) {
    logError("LOAD CONFIG ERR");
    return false;
  }

  logInfo("CONFIG FILE LOADED");
  logInfo(filename);

  return true;
}


template <typename T>
bool savePbToPersistence(T * config, const char * filename, const pb_msgdesc_t * fields) {
  pb_byte_t buffer[QROMASTRIP_CONFIG_BUFFER_LOAD_SIZE];
  memset(buffer, 0, sizeof buffer);

  logInfo("SAVING CONFIG TO PERSISTENCE");
  logInfo(filename);

  pb_ostream_t stream = pb_ostream_from_buffer(buffer, sizeof(buffer));
  bool status = pb_encode(&stream, fields, config);

  if (!status) {
    logError("Error encoding data in savePbToPersistence()");
    logError(filename);
    return false;
  }

  bool writeSuccess = saveDataToPersistence(filename, buffer, stream.bytes_written);
  if (writeSuccess) {
    logInfo("SUCCESSFULLY SAVED CONFIG");
  } else {
    logError("ERROR SAVING CONFIG");
  }

  return writeSuccess;
}


#endif
