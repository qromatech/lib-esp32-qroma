// #include "PbCommandProcessor.h"

// // PbCommandProcessor::PbCommandProcessor() {

// // }


// // int PbCommandProcessor::checkCommBufferForNewPbCommand(QromaCommCommand * cmd) {
// //   int commBufferWriteIndex = cbGetCommBufferWriteIndex();
// //   const uint8_t * commBuffer = cbGetCommBuffer();

// //   for (int i=1; i <= commBufferWriteIndex; i++) {
// //     pb_istream_t stream = pb_istream_from_buffer(commBuffer, i);
// //     bool decoded = pb_decode(&stream, QromaCommCommand_fields, cmd);

// //     if (decoded) {
// //       cbRemoveFirstNFromBuffer(i);
// //       logInfo("REMOVE N FROM BUFFER");
// //       logInfo(i);
// //       logInfo(commBufferWriteIndex - i);
// //       return i;
// //     }
// //   }

// //   return -1;
// // }
