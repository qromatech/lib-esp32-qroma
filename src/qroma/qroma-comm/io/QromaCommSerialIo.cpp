#include "QromaCommSerialIo.h"


QromaCommSerialIo::QromaCommSerialIo() {

}


    // void onSerialReceive() { }


void QromaCommSerialIo::init(QromaCommSerialIoConfig * config) {
  _qromaCommMemBuffer = config->qromaCommMemBuffer;
  _bytesProcessingPipeline.init(config->qromaBytesProcessors, config->qromaBytesProcessorsCount);

  // Serial.onReceive(&QromaCommSerialIo::onSerialReceive);
  // QromaCommSerialIo * self = this;
  Serial.onReceive([this]() {
    this->onSerialReceive();
  });
  Serial.setRxBufferSize(100);

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
