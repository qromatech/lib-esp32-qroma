// #include "comm_buffer.h"
// #include "../util/logger.h"


// #define COMM_BUFFER_SIZE 10000

// uint32_t _commBufferWriteIndex = 0;
// uint8_t _commBuffer[COMM_BUFFER_SIZE];

// int _lastTimeCommBufferAddedTo = 0;



// void cbResetCommBuffer() {
//   memset(_commBuffer, 0, sizeof _commBuffer);
//   _commBufferWriteIndex = 0;
// }

// int cbGetCommBufferWriteIndex() {
//   return _commBufferWriteIndex;
// }

// const uint8_t * cbGetCommBuffer() {
//   return _commBuffer;
// }

// void cbAddToCommBuffer(char incomingByte, int now) {
//   _commBuffer[_commBufferWriteIndex] = incomingByte;
//   _commBufferWriteIndex++;
//   _lastTimeCommBufferAddedTo = now;
// }

// int cbGetLastTimeAddedToInMs() {
//   return _lastTimeCommBufferAddedTo;
// }

// void cbRemoveFirstNFromBuffer(int n) {
//   logInfo("cbRemoveFirstNFromBuffer");
//   logInfo(_commBufferWriteIndex);
//   logInfo(n);
//   logInfo((const char*)_commBuffer);

//   if (n >= _commBufferWriteIndex) {
//     cbResetCommBuffer();
//     return;
//   }

//   int remaining = _commBufferWriteIndex - n;

//   for (int i=0; i < remaining; i++) {
//     _commBuffer[i] = _commBuffer[n + i];
//   }
//   memset(_commBuffer + (_commBufferWriteIndex - n), 0, (sizeof _commBuffer) - remaining);
//   _commBufferWriteIndex -= n;

//   logInfo((const char*)_commBuffer);
//   logInfo(_commBufferWriteIndex);
// }
