// #include "../util/logger.h"
// #include "chunkedPrintBuffer.h"
// #include <Arduino.h>


// ChunkedPrintBuffer::ChunkedPrintBuffer() {
//   _buffer = new CircularBuffer<uint8_t, CHUNKED_PRINT_BUFFER_SIZE>();
// }


// void ChunkedPrintBuffer::_addByte(uint8_t byte) {
//   _buffer->push(byte);
// }


// void ChunkedPrintBuffer::addBytes(const uint8_t * bytes, size_t length) {
//   for (int i=0; i < length; i++) {
//     _addByte(bytes[i]);
//   }
//   _lastTimeChunkedPrintBufferAddedTo = millis();
// }


// void ChunkedPrintBuffer::addMessage(const char * msg) {
//   size_t len = strnlen(msg, CHUNKED_PRINT_BUFFER_SIZE - _buffer->available());  
//   addBytes((uint8_t *)msg, len);
// }


// void ChunkedPrintBuffer::addLine(const char * msg) {
//   addMessage(msg);
//   _addByte('\n');
// }


// void ChunkedPrintBuffer::addLine(const char * msg, const char * value) {
//   addMessage(msg);
//   addLine(value);
// }


// void ChunkedPrintBuffer::addIntMessageLine(const char * msg, int value) {
//   char vBuf[20];
//   sprintf(vBuf, "%d", value);
  
//   addLine(msg, vBuf);
// }


// bool ChunkedPrintBuffer::isEmpty() {
//   return _buffer->isEmpty();
// }


// uint32_t ChunkedPrintBuffer::size() {
//   return _buffer->size();
// }


// size_t ChunkedPrintBuffer::readBytes(uint8_t * buffer, size_t bufferSize) {
//   size_t numBytesRead = 0;

//   while (!_buffer->isEmpty() && 
//          numBytesRead < bufferSize) 
//   {
//     buffer[numBytesRead] = _buffer->shift();
//     numBytesRead++;
//   }

//   return numBytesRead;
// }
