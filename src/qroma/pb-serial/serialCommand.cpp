// // #include <freertos/FreeRTOS.h>
// // #include <freertos/task.h>
// #include <RTOS.h>
// // #include "../serial/debug_comm.h"
// #include "serialCommand.h"
// #include "pbSerialComm.h"
// // #include "pbUartBleComm.h"
// #include "pbBufferCommProcessor.h"
// #include "../util/constants.h"
// #include "../util/logger.h"


// PbSerialComm _pbSerialComm = PbSerialComm();
// // PbUartBleComm _pbUartBleComm = PbUartBleComm();
// PbBufferCommProcessor _pbBufferCommProcessor = PbBufferCommProcessor();

// // PbUartBleComm * getPbUartBleComm() { return &_pbUartBleComm; }
// PbSerialComm * getPbSerialComm() { return &_pbSerialComm; }



// void _doSerialCommandProcessingTask(void *pvParameters) {
//   logInfo("STARTING TASK: doSerialCommandProcessingTask");

//   _pbBufferCommProcessor.doPbCommSetup();

//   while (true) {
//     _pbSerialComm.readData();
//     bool wasRead = _pbBufferCommProcessor.processCommBuffer();
//     if (!wasRead) {
//       vTaskDelay(MS_5);
//     }
//   }

//   logInfo("COMPLETED TASK: doSerialCommandProcessingTask");
//   vTaskDelete(NULL);
// }

// void initSerialCommandMode() {
//   BaseType_t xTaskStatus = xTaskCreate(_doSerialCommandProcessingTask, "doSerialCommandProcessingTask", 40000, NULL, 1, NULL);

//   if (xTaskStatus != pdPASS) {
//     logError("ERROR CREATING TASK: doSerialCommandProcessingTask");
//     logError(xTaskStatus);
//     return;
//   }
// }
