#include "QromaCommSerialIo.h"


QromaCommSerialIo::QromaCommSerialIo() {

}


void QromaCommSerialIo::init(QromaCommSerialIoConfig * config) {
  _qromaCommMemBuffer = config->qromaCommMemBuffer;
  _bytesProcessingPipeline.init(config->qromaBytesProcessors, config->qromaBytesProcessorsCount);

  Serial.onReceive([this]() {
    this->onSerialReceive();
  });
  Serial.setRxBufferSize(config->rxBufferSize);

  Serial.begin(config->baudRate);
}


void QromaCommSerialIo::onSerialReceive() {
  int now = millis();

  while (Serial.available()) {
    char incomingByte = Serial.read();
    _qromaCommMemBuffer->addByte(incomingByte, now);
  }

  _bytesProcessingPipeline.processCommBuffer(_qromaCommMemBuffer);
}


void QromaCommSerialIo::serialTxBytes(const uint8_t * bytes, uint32_t byteCount) {
  Serial.write(bytes, byteCount);
}


void QromaCommSerialIo::serialPrint(const char * message) {
  Serial.print(message);
}


void QromaCommSerialIo::serialPrintln(const char * message) {
  Serial.println(message);
}
