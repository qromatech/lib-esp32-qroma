#include <RTOS.h>
#include <Arduino.h>

#include "QromaCommSerialPbRxBase.h"
#include <qroma/util/logger.h>
#include <qroma/util/constants.h>
#include "SerialCommandProcessingTask.h"


// void _doSerialCommandProcessingTask(void *pvParameters) {
//   logInfo("STARTING TASK: doSerialCommandProcessingTask");

//   QromaCommSerialPbRxBase * qcSerialRx = (QromaCommSerialPbRxBase*)pvParameters;
//   uint32_t lastDelay = millis();

//   while (true) {
//     bool hasMoreProcessingToDo = qcSerialRx->processCommBuffer();
//     while (hasMoreProcessingToDo) {
//       logInfo("hasMoreProcessingToDo");
//       hasMoreProcessingToDo = qcSerialRx->processCommBuffer();
//     }

//     bool rxNeedsDelay = qcSerialRx->serialRx();
//     if (rxNeedsDelay) {
//       logInfo("rxNeedsDelay");
//       lastDelay = millis();
//       vTaskDelay(MS_1000);
//     } else {
//       // uint32_t msSinceLastDelay = millis() - lastDelay;
//       // if (msSinceLastDelay >= 1000) {
//       //   // vTaskDelay(MS_10);
//       // }
//       // // logInfo("CONTINUE PROCESSING");
//     }
//   }

//   logInfo("OOPS - COMPLETED TASK: doSerialCommandProcessingTask");
//   vTaskDelete(NULL);
// }


void QromaCommSerialPbRxBase::initPbRxBase(
  QromaCommMemBuffer * qromaCommMemBuffer, 
  IAppCommandProcessor * appCommandProcessor, 
  std::function<void(const uint8_t*, uint32_t)> responseFn
) {
  _commSilenceDelayToClearBuffer = 3000;
  _nextBufferExpirationTime = 0;
  
  _qromaCommMemBuffer = qromaCommMemBuffer;
  _qromaCommProcessor.init(appCommandProcessor);

  _responseFn = responseFn;

  BaseType_t xTaskStatus = xTaskCreate(_doSerialCommandProcessingTask, "doSerialCommandProcessingTask", 40000, (QromaCommSerialPbRxBase*)this, 1, NULL);

  if (xTaskStatus != pdPASS) {
    logError("ERROR CREATING TASK: doSerialCommandProcessingTask");
    logError(xTaskStatus);
  }
}


// return whether or not consumer should delay
bool QromaCommSerialPbRxBase::serialRx() {
  int now = millis();

  uint32_t remainingBufferByteCount = _qromaCommMemBuffer->getRemainingBufferByteCount();
  bool bufferIsFull = remainingBufferByteCount < 1;

  if (bufferIsFull) {
    logInfoIntWithDescription("QromaCommSerialPbRxBase::serialRx() START - BUFFER FULL: ", remainingBufferByteCount);
    return true;
  }

  bool bufferWasAddedTo = false;
  while (Serial.available() &&
         remainingBufferByteCount > 0) 
  {
    char incomingByte = Serial.read();
    remainingBufferByteCount = _qromaCommMemBuffer->addByte(incomingByte, now);
    bufferWasAddedTo = true;
    bufferIsFull = remainingBufferByteCount < 1;
  }

  if (bufferIsFull) {
    logInfoIntWithDescription("QromaCommSerialPbRxBase::serialRx() END - BUFFER FULL, DON'T DELAY: ", remainingBufferByteCount);
    return false;
  }

  return !bufferWasAddedTo;
}


// - return whether or not more processing should happen
bool QromaCommSerialPbRxBase::processCommBuffer() {
  int now = millis();
  if (now > _nextBufferExpirationTime) {
    _nextBufferExpirationTime = now + _commSilenceDelayToClearBuffer;
    logInfoUintWithDescription("processCommBuffer EXPIRED - ", now);
    logInfo(_nextBufferExpirationTime);
    _qromaCommMemBuffer->reset();
    _qromaCommProcessor.reset();
    return false;
  }

  int commBufferWriteIndex = _qromaCommMemBuffer->getBufferWriteIndex();
  if (commBufferWriteIndex == 0) {
    return false;
  }

  const uint8_t * bytes = _qromaCommMemBuffer->getBufferContent();
  uint32_t byteCount = _qromaCommMemBuffer->getBufferWriteIndex();

  uint32_t numBytesConsumed = 0;

  numBytesConsumed = _qromaCommProcessor.processBytes(bytes, byteCount, _responseFn);

  if (numBytesConsumed > 0) {
    _qromaCommMemBuffer->removeFirstNFromBuffer(numBytesConsumed);
    logInfoIntWithDescription("QromaCommSerialPbRxBase::processCommBuffer() PROCESSED BYTES: ", numBytesConsumed);
    commBufferWriteIndex = _qromaCommMemBuffer->getBufferWriteIndex();
    return commBufferWriteIndex != 1;
  }

  return false;
}


bool QromaCommSerialPbRxBase::sendQromaCommResponse(QromaCommResponse * qromaCommResponse) {
  return _qromaCommProcessor.sendQromaCommResponse(qromaCommResponse, _responseFn);
}