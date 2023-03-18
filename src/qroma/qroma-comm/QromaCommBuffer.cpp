#include "QromaCommBuffer.h"
#include "../util/logger.h"


QromaCommBuffer::QromaCommBuffer(uint8_t * bufferMemory, uint32_t bufferSize) {
  _bufferMemory = bufferMemory;
  _bufferSize = bufferSize;

  _bufferWriteIndex = 0;
  _lastTimeBufferAddedTo = 0;
}


void QromaCommBuffer::reset() {
  memset(_bufferMemory, 0, _bufferSize);
  _bufferWriteIndex = 0;
}


int QromaCommBuffer::getBufferWriteIndex() {
  return _bufferWriteIndex;
}


const uint8_t * QromaCommBuffer::getBufferMemory() {
  return _bufferMemory;
}


void QromaCommBuffer::addByte(uint8_t incomingByte, int now) {
  _bufferMemory[_bufferWriteIndex] = incomingByte;
  _bufferWriteIndex++;
  _lastTimeBufferAddedTo = now;
}


int QromaCommBuffer::getLastTimeAddedToInMs() {
  return _lastTimeBufferAddedTo;
}


void QromaCommBuffer::removeFirstNFromBuffer(uint32_t n) {
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
