#include <RTOS.h>
#include <Arduino.h>

#include "SerialCommandProcessingTask.h"
#include "QromaCommSerialPbRxBase.h"
#include <qroma/util/constants.h>
#include <qroma/util/logger.h>


uint32_t _msDelayInProcessingLoop = 100;
uint32_t _processingLoopDelayInterval = _msDelayInProcessingLoop * MS_1;


bool setMsDelayInProcessingLoop(uint32_t msDelay) {
  if (msDelay > 0 &&
      msDelay <= 5000)
  {
    _msDelayInProcessingLoop = msDelay;
    _processingLoopDelayInterval = msDelay * MS_1;
    return true;
  } else {
    logError("MS DELAY IN PROCESSING LOOP MUST BE 5000 OR LESS");
    return false;
  }
}

uint32_t getMsDelayInProcessingLoop() {
  return _msDelayInProcessingLoop;
}


void _doSerialCommandProcessingTask(void *pvParameters) {
  logInfo("STARTING TASK: doSerialCommandProcessingTask");

  QromaCommSerialPbRxBase * qcSerialRx = (QromaCommSerialPbRxBase*)pvParameters;
  // uint32_t lastDelay = millis();

  while (true) {
    // bool hasMoreProcessingToDo = qcSerialRx->processCommBuffer();
    // while (hasMoreProcessingToDo) {
    //   logInfo("hasMoreProcessingToDo");
    //   hasMoreProcessingToDo = qcSerialRx->processCommBuffer();
    // }

    qcSerialRx->processCommBuffer();

    bool rxNeedsDelay = qcSerialRx->serialRx();
    if (rxNeedsDelay) {
      // logInfo("rxNeedsDelay");
      // lastDelay = millis();
      vTaskDelay(_processingLoopDelayInterval);
    } else {
      // uint32_t msSinceLastDelay = millis() - lastDelay;
      // if (msSinceLastDelay >= 1000) {
      //   // vTaskDelay(MS_10);
      // }
      // // logInfo("CONTINUE PROCESSING");
    }
  }

  logInfo("OOPS - COMPLETED TASK: doSerialCommandProcessingTask");
  vTaskDelete(NULL);
}

