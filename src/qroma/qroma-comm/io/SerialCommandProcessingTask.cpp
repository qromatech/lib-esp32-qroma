#include <RTOS.h>
#include <Arduino.h>

#include "SerialCommandProcessingTask.h"
#include "QromaCommSerialPbRxBase.h"
#include <qroma/util/constants.h>



void _doSerialCommandProcessingTask(void *pvParameters) {
  logInfo("STARTING TASK: doSerialCommandProcessingTask");

  QromaCommSerialPbRxBase * qcSerialRx = (QromaCommSerialPbRxBase*)pvParameters;
  uint32_t lastDelay = millis();

  while (true) {
    bool hasMoreProcessingToDo = qcSerialRx->processCommBuffer();
    while (hasMoreProcessingToDo) {
      logInfo("hasMoreProcessingToDo");
      hasMoreProcessingToDo = qcSerialRx->processCommBuffer();
    }

    bool rxNeedsDelay = qcSerialRx->serialRx();
    if (rxNeedsDelay) {
      logInfo("rxNeedsDelay");
      lastDelay = millis();
      vTaskDelay(MS_1000);
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

