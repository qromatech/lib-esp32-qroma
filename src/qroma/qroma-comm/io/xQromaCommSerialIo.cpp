// #include "QromaCommSerialIo.h"
// #include "../../util/logger.h"
// #include "../../util/constants.h"



// void _doSerialCommandProcessingTask(void *pvParameters) {
//   logInfo("STARTING TASK: doSerialCommandProcessingTask");

//   QromaCommSerialIo * qcSerialIo = (QromaCommSerialIo*)pvParameters;
  
//   // _pbBufferCommProcessor.doPbCommSetup();

//   while (true) {
//     qcSerialIo->serialRx();
//     bool wasProcessed = qcSerialIo->processCommBuffer();
//     if (!wasProcessed) {
//       vTaskDelay(MS_10);
//     }
//   }

//   logInfo("OOPS - COMPLETED TASK: doSerialCommandProcessingTask");
//   vTaskDelete(NULL);
// }


// // QromaCommSerialIo::QromaCommSerialIo() {

// // }


// void QromaCommSerialIo::init(QromaCommSerialIoConfig * config, PbCommandsRegistry * pbCommandsRegistry) {
//   // _qromaCommMemBuffer = config->qromaCommMemBuffer;
//   _qromaCommMemBuffer = getQromaCommMemBuffer();
//   _serial = getSerial();
//   _newDataProcessor = getQromaNewDataProcessor();
//   // _bytesProcessingPipeline.init(config->qromaBytesProcessors, config->qromaBytesProcessorsCount);

//   _pbCommandsRegistry = pbCommandsRegistry;

//   _serial->setRxBufferSize(config->rxBufferSize);
//   _serial->begin(config->baudRate);

//   BaseType_t xTaskStatus = xTaskCreate(_doSerialCommandProcessingTask, "doSerialCommandProcessingTask", 40000, NULL, 1, NULL);

//   if (xTaskStatus != pdPASS) {
//     logError("ERROR CREATING TASK: doSerialCommandProcessingTask");
//     logError(xTaskStatus);
//   }
// }


// // void QromaCommSerialIo::onSerialReceive() {
// //   int now = millis();

// //   while (Serial.available()) {
// //     char incomingByte = Serial.read();
// //     _qromaCommMemBuffer->addByte(incomingByte, now);
// //   }

// //   _bytesProcessingPipeline.processCommBuffer(_qromaCommMemBuffer);
// // }


// void QromaCommSerialIo::serialRx() {
//   int now = millis();
//   // bool dataRead = false;

//   while (Serial.available()) {
//     char incomingByte = Serial.read();
//     _qromaCommMemBuffer->addByte(incomingByte, now);
//     // dataRead = true;
//   }

//   // return dataRead;
// }


// bool QromaCommSerialIo::processCommBuffer() {
//   // return _messageProcessingPipeline.processCommBuffer(_qromaCommMemBuffer);
// }


// void QromaCommSerialIo::serialTxBytes(const uint8_t * bytes, uint32_t byteCount) {
//   _serial->write(bytes, byteCount);
// }


// void QromaCommSerialIo::serialPrint(const char * message) {
//   _serial->print(message);
// }


// void QromaCommSerialIo::serialPrintln(const char * message) {
//   _serial->println(message);
// }
