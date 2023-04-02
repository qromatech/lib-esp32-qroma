#include <RTOS.h>
#include <Arduino.h>

#include "QromaCommSerialPbRxBase.h"
#include "../../util/logger.h"
#include "../../util/constants.h"


void _doSerialCommandProcessingTask(void *pvParameters) {
  logInfo("STARTING TASK: doSerialCommandProcessingTask");

  // QromaCommSerialIo * qcSerialIo = (QromaCommSerialIo*)pvParameters;
  QromaCommSerialPbRxBase * qcSerialRx = (QromaCommSerialPbRxBase*)pvParameters;
  
  // _pbBufferCommProcessor.doPbCommSetup();

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
  QromaNewDataPbProcessor * defaultQromaNewDataProcessor, 
  PbCommandsRegistry * pbCommandsRegistry,
  std::function<void(uint8_t*, uint32_t)> responseFn
) {
  _commSilenceDelayToClearBuffer = 3000;
  
  _qromaCommMemBuffer = qromaCommMemBuffer;
  _defaultQromaNewDataProcessor = defaultQromaNewDataProcessor;
  _activeQromaNewDataProcessor = defaultQromaNewDataProcessor;

  _pbCommandsRegistry = pbCommandsRegistry;

  _responseFn = responseFn;

  // _qromaCommMemBuffer = config->qromaCommMemBuffer;
  // _qromaCommMemBuffer = getQromaCommMemBuffer();
  // _serial = getSerial();
  // _newDataProcessor = getQromaNewDataProcessor();
  // // _bytesProcessingPipeline.init(config->qromaBytesProcessors, config->qromaBytesProcessorsCount);

  // _pbCommandsRegistry = pbCommandsRegistry;

  // _serial->setRxBufferSize(config->rxBufferSize);
  // _serial->begin(config->baudRate);

  BaseType_t xTaskStatus = xTaskCreate(_doSerialCommandProcessingTask, "doSerialCommandProcessingTask", 40000, (QromaCommSerialPbRxBase*)this, 1, NULL);

  if (xTaskStatus != pdPASS) {
    logError("ERROR CREATING TASK: doSerialCommandProcessingTask");
    logError(xTaskStatus);
  }
}


// void QromaCommSerialIo::onSerialReceive() {
//   int now = millis();

//   while (Serial.available()) {
//     char incomingByte = Serial.read();
//     _qromaCommMemBuffer->addByte(incomingByte, now);
//   }

//   _bytesProcessingPipeline.processCommBuffer(_qromaCommMemBuffer);
// }


void QromaCommSerialPbRxBase::serialRx() {
  int now = millis();
  // bool dataRead = false;

  while (Serial.available()) {
    char incomingByte = Serial.read();
    _qromaCommMemBuffer->addByte(incomingByte, now);
    // dataRead = true;
  }

  // return dataRead;
}


bool QromaCommSerialPbRxBase::processCommBuffer() {
  // logInfo("processCommBuffer...");
  // if (_qromaCommMemBuffer == NULL) {
  //   logInfo("NULL MEM BUFFER");
  // } else {
  //   logInfo("NOT NULL MEM BUFFER");
  // }
  // logInfo((int)(void*)_qromaCommMemBuffer);
  // logInfo("_qromaCommMemBuffer");

  int commBufferWriteIndex = _qromaCommMemBuffer->getBufferWriteIndex();
  if (commBufferWriteIndex == 0) {
    return false;
  }

  // logInfo("processCommBuffer - 2");
  int now = millis();
  int bufferExpirationTime = _qromaCommMemBuffer->getLastTimeAddedToInMs() + _commSilenceDelayToClearBuffer;
  if (now > bufferExpirationTime) {
    logInfo("processCommBuffer EXPIRED");
    _activeQromaNewDataProcessor = _defaultQromaNewDataProcessor;
    _qromaCommMemBuffer->reset();
    
    // setProcessingMode(_defaultProcessingMode);
    // commBuffer->reset();
    return false;
  }

  // logInfo("processCommBuffer - 3");

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