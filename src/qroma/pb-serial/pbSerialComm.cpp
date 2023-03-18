#include <freertos/FreeRTOS.h>
#include <pb_encode.h>
#include <pb_decode.h>
#include "SPIFFS.h"

#include "pbSerialComm.h"
#include "comm_buffer.h"
#include "../util/logger.h"


bool PbSerialComm::readData() {
  bool dataRead = false;
  while (Serial.available()) {
    char incomingByte = Serial.read();
    cbAddToCommBuffer(incomingByte, millis());
    // dataRead = true;
  }

  return dataRead;
}


void PbSerialComm::pbSendBytes(uint8_t * values, uint32_t count) {
  Serial.flush();
  for (int i = 0; i < count; i++) {
    Serial.write(values[i]);
  }
  Serial.flush();
}
