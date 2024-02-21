#include <RTOS.h>
#include <Arduino.h>

#include "QromaCommSerialPbRxBase.h"
#include <qroma/util/logger.h>
#include <qroma/util/constants.h>


void _doSerialCommandProcessingTask(void *pvParameters) {
  logInfo("STARTING TASK: doSerialCommandProcessingTask");

  QromaCommSerialPbRxBase * qcSerialRx = (QromaCommSerialPbRxBase*)pvParameters;

  while (true) {
    qcSerialRx->processCommBuffer();

    bool rxNeedsDelay = qcSerialRx->serialRx();
    if (rxNeedsDelay) {
      vTaskDelay(MS_10);
    } else {
      // logInfo("PROCESSING");
    }
  }

  logInfo("OOPS - COMPLETED TASK: doSerialCommandProcessingTask");
  vTaskDelete(NULL);
}


void QromaCommSerialPbRxBase::initPbRxBase(
  QromaCommMemBuffer * qromaCommMemBuffer, 
  IAppCommandProcessor * appCommandProcessor, 
  std::function<void(const uint8_t*, uint32_t)> responseFn
) {
  _commSilenceDelayToClearBuffer = 3000;
  
  _qromaCommMemBuffer = qromaCommMemBuffer;
  _qromaCommProcessor.init(appCommandProcessor);

  _responseFn = responseFn;

  BaseType_t xTaskStatus = xTaskCreate(_doSerialCommandProcessingTask, "doSerialCommandProcessingTask", 40000, (QromaCommSerialPbRxBase*)this, 1, NULL);

  if (xTaskStatus != pdPASS) {
    logError("ERROR CREATING TASK: doSerialCommandProcessingTask");
    logError(xTaskStatus);
  }
}


// return whether or not we need a delay
bool QromaCommSerialPbRxBase::serialRx() {
  int now = millis();

  uint32_t remainingBufferByteCount = _qromaCommMemBuffer->getRemainingBufferByteCount();

  if (remainingBufferByteCount < 1) {
    logInfo("QromaCommSerialPbRxBase::serialRx() START - BUFFER FULL");
    return true;
  }

  while (Serial.available() &&
         remainingBufferByteCount > 0) 
  {
    char incomingByte = Serial.read();
    remainingBufferByteCount = _qromaCommMemBuffer->addByte(incomingByte, now);
  }

  if (remainingBufferByteCount < 1) {
    logInfo("QromaCommSerialPbRxBase::serialRx() END - BUFFER FULL");
    return true;
  }

  return false;
}


// TODO: return number of bytes processed?
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
    _qromaCommProcessor.reset();
    return false;
  }

  const uint8_t * bytes = _qromaCommMemBuffer->getBufferContent();
  uint32_t byteCount = _qromaCommMemBuffer->getBufferWriteIndex();

  uint32_t numBytesProcessed = 0;

  numBytesProcessed = _qromaCommProcessor.processBytes(bytes, byteCount, _responseFn);

  if (numBytesProcessed > 0) {
    _qromaCommMemBuffer->removeFirstNFromBuffer(numBytesProcessed);
    // logInfoIntWithDescription("QromaCommSerialPbRxBase::processCommBuffer() PROCESSED BYTES: ", numBytesProcessed);
    return true;
  }

  return false;
}


bool QromaCommSerialPbRxBase::sendQromaCommResponse(QromaCommResponse * qromaCommResponse) {
  return _qromaCommProcessor.sendQromaCommResponse(qromaCommResponse, _responseFn);
}