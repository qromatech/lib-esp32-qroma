#include "QromaCommMemBuffer.h"
#include "../../util/logger.h"


QromaCommMemBuffer::QromaCommMemBuffer(uint8_t * bufferMemory, uint32_t bufferSize) {
  _bufferMemory = bufferMemory;
  _bufferSize = bufferSize;

  _bufferWriteIndex = 0;
  _lastTimeBufferAddedTo = 0;
}


void QromaCommMemBuffer::reset() {
  memset(_bufferMemory, 0, _bufferSize);
  _bufferWriteIndex = 0;
}


uint32_t QromaCommMemBuffer::getBufferWriteIndex() {
  return _bufferWriteIndex;
}


const uint8_t * QromaCommMemBuffer::getBufferContent() {
  return _bufferMemory;
}


void QromaCommMemBuffer::addByte(uint8_t incomingByte, int now) {
  _bufferMemory[_bufferWriteIndex] = incomingByte;
  _bufferWriteIndex++;
  _lastTimeBufferAddedTo = now;
}


uint32_t QromaCommMemBuffer::getLastTimeAddedToInMs() {
  return _lastTimeBufferAddedTo;
}


void QromaCommMemBuffer::removeFirstNFromBuffer(uint32_t n) {
  logInfo("removeFirstNFromBuffer");
  logInfo(_bufferWriteIndex);
  logInfo(n);
  logInfo((const char*)_bufferMemory);

  if (n >= _bufferWriteIndex) {
    reset();
    return;
  }

  int remaining = _bufferWriteIndex - n;

  for (int i=0; i < remaining; i++) {
    _bufferMemory[i] = _bufferMemory[n + i];
  }
  memset(_bufferMemory + (_bufferWriteIndex - n), 0, _bufferSize - remaining);
  _bufferWriteIndex -= n;

  logInfo((const char*)_bufferMemory);
  logInfo(_bufferWriteIndex);
}
