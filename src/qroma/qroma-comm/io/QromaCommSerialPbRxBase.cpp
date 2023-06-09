#include <RTOS.h>
#include <Arduino.h>

#include "QromaCommSerialPbRxBase.h"
#include "../../util/logger.h"
#include "../../util/constants.h"


void _doSerialCommandProcessingTask(void *pvParameters) {
  logInfo("STARTING TASK: doSerialCommandProcessingTask");

  QromaCommSerialPbRxBase * qcSerialRx = (QromaCommSerialPbRxBase*)pvParameters;

  while (true) {
    qcSerialRx->serialRx();
    bool wasProcessed = qcSerialRx->processCommBuffer();
    if (!wasProcessed) {
      vTaskDelay(MS_10);
    } else {
      logInfo("PROCESSING");
    }
  }

  logInfo("OOPS - COMPLETED TASK: doSerialCommandProcessingTask");
  vTaskDelete(NULL);
}


void QromaCommSerialPbRxBase::initPbRxBase(
  QromaCommMemBuffer * qromaCommMemBuffer, 
  IQromaNewDataPbProcessor * qromaNewDataProcessor, 
  PbCommandsRegistry * pbCommandsRegistry,
  std::function<void(uint8_t*, uint32_t)> responseFn
) {
  _commSilenceDelayToClearBuffer = 3000;
  
  _qromaCommMemBuffer = qromaCommMemBuffer;
  _activeQromaNewDataProcessor = qromaNewDataProcessor;

  _pbCommandsRegistry = pbCommandsRegistry;

  _responseFn = responseFn;

  BaseType_t xTaskStatus = xTaskCreate(_doSerialCommandProcessingTask, "doSerialCommandProcessingTask", 40000, (QromaCommSerialPbRxBase*)this, 1, NULL);

  if (xTaskStatus != pdPASS) {
    logError("ERROR CREATING TASK: doSerialCommandProcessingTask");
    logError(xTaskStatus);
  }
}


void QromaCommSerialPbRxBase::serialRx() {
  int now = millis();

  while (Serial.available()) {
    char incomingByte = Serial.read();
    _qromaCommMemBuffer->addByte(incomingByte, now);
  }
}


bool QromaCommSerialPbRxBase::processCommBuffer() {
  int commBufferWriteIndex = _qromaCommMemBuffer->getBufferWriteIndex();
  if (commBufferWriteIndex == 0) {
    return false;
  }

  int now = millis();
  int bufferExpirationTime = _qromaCommMemBuffer->getLastTimeAddedToInMs() + _commSilenceDelayToClearBuffer;
  if (now > bufferExpirationTime) {
    logInfo("processCommBuffer EXPIRED");
    _qromaCommMemBuffer->reset();
    return false;
  }

  const uint8_t * bytes = _qromaCommMemBuffer->getBufferContent();
  uint32_t byteCount = _qromaCommMemBuffer->getBufferWriteIndex();

  uint32_t numBytesProcessed = 0;

  logInfo("pre-processBytes");
  numBytesProcessed = _activeQromaNewDataProcessor->processBytes(bytes, byteCount, _pbCommandsRegistry, _responseFn);
  logInfo("post-processBytes");

  if (numBytesProcessed > 0) {
    _qromaCommMemBuffer->removeFirstNFromBuffer(numBytesProcessed);
    return true;
  }

  return false;
}
