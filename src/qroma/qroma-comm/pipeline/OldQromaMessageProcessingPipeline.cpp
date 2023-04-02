// #include "QromaMessageProcessingPipeline.h"
// #include "../../util/logger.h"
// #include "../../util/qbase64.h"


// QromaMessageProcessingPipeline::QromaMessageProcessingPipeline() {
//   _commSilenceDelayToClearBuffer = 3000;
//   _defaultProcessingMode = QromaBytesProcessingMode_PB_BASE64_COMMANDS;
//   _processingMode = _defaultProcessingMode;
// }


// // void QromaMessageProcessingPipeline::init(QromaBytesProcessor** qromaBytesProcessors, uint8_t qromaBytesProcessorsCount) {
// //   _qromaBytesProcessors = qromaBytesProcessors;
// //   _qromaBytesProcessorsCount = qromaBytesProcessorsCount;
// // }


// bool QromaMessageProcessingPipeline::processCommBuffer(IQromaCommBuffer * commBuffer) {
//   int commBufferWriteIndex = commBuffer->getBufferWriteIndex();
//   if (commBufferWriteIndex == 0) {
//     return false;
//   }

//   int now = millis();
//   int bufferExpirationTime = commBuffer->getLastTimeAddedToInMs() + _commSilenceDelayToClearBuffer;
//   if (now > bufferExpirationTime) {
//     logInfo("processCommBuffer EXPIRED");
//     setProcessingMode(_defaultProcessingMode);
//     commBuffer->reset();
//     return false;
//   }

//   const uint8_t * bytes = commBuffer->getBufferContent();
//   uint32_t byteCount = commBuffer->getBufferWriteIndex();

//   uint32_t numBytesProcessed = 0;

//   switch (_processingMode) {
//     case QromaBytesProcessingMode_PB_COMMANDS:
//       // logInfo("Mode_PB_COMMANDS");
//       numBytesProcessed = processPbCommands(bytes, byteCount);
//       break;
//     case QromaBytesProcessingMode_PB_BASE64_COMMANDS:
//       numBytesProcessed = processBase64PbCommands(bytes, byteCount);
//       break;
//     // case CommReadingMode_FILE_FROM_COMM:
//     // case CommReadingMode_QROMA_DEVICE_CMD_FROM_COMM:
//     // case CommReadingMode_QROMA_POINT_CMD_FROM_COMM:
//     //   logInfo("Mode_FILE_FROM_COMM");
//     //   return processReadToBuffer();
//     //   break;
//     case QromaBytesProcessingMode_NOT_SET:
//       logError("Mode_NOT_SET");
//       break;
//     default:
//       logError("Unrecognized Mode");
//   }

//   if (numBytesProcessed > 0) {
//     commBuffer->removeFirstNFromBuffer(numBytesProcessed);
//     return true;
//   }

//   return false;
// }


// void QromaMessageProcessingPipeline::setProcessingMode(QromaBytesProcessingMode mode) {
//   _processingMode = mode;
// }


// uint32_t QromaMessageProcessingPipeline::processPbCommands(const uint8_t * bytes, uint32_t byteCount) {

//   logInfo("PROCESSING PB COMMANDS");
//   // for (int i=0; i < _qromaBytesProcessorsCount; i++) {
//   //   QromaBytesProcessor * thisProcessor = _qromaBytesProcessors[i];
//   //   uint32_t numBytesProcessed = thisProcessor->processBytes(bytes, byteCount);
//   //   if (numBytesProcessed > 0) {
//   //     logInfo("PROCESSED BYTES");
//   //     logInfo(numBytesProcessed);
//   //     return numBytesProcessed;
//   //   }
//   // }

//   return 0;
// }


// uint32_t QromaMessageProcessingPipeline::processBase64PbCommands(const uint8_t * bytes, uint32_t byteCount) {

//   logInfo("PROCESSING BASE64 PB COMMANDS");

//   uint8_t pbBytes[2000];
  
//   bool b64MessageFound = false;
//   uint32_t scanIndex = 0;
//   while (!b64MessageFound) {
//     if (bytes[scanIndex] == '\n') {
//       unsigned int binary_length = q_decode_base64(bytes, scanIndex, pbBytes);
//       processPbCommands(pbBytes, binary_length);
//       return scanIndex + 1;
//     }
//     scanIndex++;
//   }
  
//   // for (int i=0; i < _qromaBytesProcessorsCount; i++) {
//   //   QromaBytesProcessor * thisProcessor = _qromaBytesProcessors[i];
//   //   uint32_t numBytesProcessed = thisProcessor->processBytes(bytes, byteCount);
//   //   if (numBytesProcessed > 0) {
//   //     logInfo("PROCESSED BYTES");
//   //     logInfo(numBytesProcessed);
//   //     return numBytesProcessed;
//   //   }
//   // }

//   return 0;
// }


// // int BytesProcessor::checkCommBufferForNewPbCommand(QromaCommCommand * cmd) {
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



// // bool BytesProcessor::processQromaCommPbCommands() {

// //   int validBufferSize = checkForNewQromaCommCommand(&_commPbQromaCommCommand);
// //   if (validBufferSize <= 0) {
// //     return false;
// //   }

// //   QromaCommCommand * cmd = &_commPbQromaCommCommand;

// //   switch (cmd->which_command)
// //   {
// //     case QromaCommCommand_clearToSendQuery_tag:
// //       logInfo("CTS QUERY - LC");
// //       handleClearToSendQuery(&(cmd->command.clearToSendQuery));
// //       break;

// //     case QromaCommCommand_fsCommand_tag:
// //       logInfo("FILESYS - LC");
// //       handleFileSystemCommand(&(cmd->command.fsCommand), this);
// //       break;

// //     default:
// //       break;
// //   }

// //   return true;
// // }


// // int BytesProcessor::checkForNewQromaCommCommand(QromaCommCommand * cmd) {
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