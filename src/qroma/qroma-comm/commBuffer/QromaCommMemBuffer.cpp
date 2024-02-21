#include "QromaCommMemBuffer.h"
#include <qroma/util/logger.h>


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


uint32_t QromaCommMemBuffer::getRemainingBufferByteCount() {
  return _bufferSize - _bufferWriteIndex;
}


uint32_t QromaCommMemBuffer::addByte(uint8_t incomingByte, int now) {
  _bufferMemory[_bufferWriteIndex] = incomingByte;
  _bufferWriteIndex++;
  _lastTimeBufferAddedTo = now;

  return getRemainingBufferByteCount();
}


uint32_t QromaCommMemBuffer::getLastTimeAddedToInMs() {
  return _lastTimeBufferAddedTo;
}


void QromaCommMemBuffer::removeFirstNFromBuffer(uint32_t n) {
  // logInfoIntWithDescription("REMOVE FIRST N FROM BUFFER: ", n);
  // logInfoIntWithDescription("BUFFER WRITE INDEX: ", _bufferWriteIndex);

  if (n >= _bufferWriteIndex) {
    reset();
    return;
  }

  int remaining = _bufferWriteIndex - n;
  logInfoIntWithDescription("BUFFER REMAINING: ", remaining);

  for (int i=0; i < remaining; i++) {
    _bufferMemory[i] = _bufferMemory[n + i];
  }
  memset(_bufferMemory + remaining, 0, _bufferSize - remaining);
  _bufferWriteIndex -= n;

  logInfo((const char*)_bufferMemory);
  logInfo(_bufferWriteIndex);
}
