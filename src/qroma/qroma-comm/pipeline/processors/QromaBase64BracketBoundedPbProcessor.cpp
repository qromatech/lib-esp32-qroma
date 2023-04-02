// #include "QromaBase64BracketBoundedPbProcessor.h"
// #include "../../pb-commands/IPbCommandHandler.h"
// #include "../../../util/logger.h"


// void QromaBase64BracketBoundedPbProcessor::reset() { }


// uint32_t QromaBase64BracketBoundedPbProcessor::processBytes(const uint8_t * bytes, uint32_t byteCount, PbCommandsRegistry * pbCommandsRegistry, std::function<void(uint8_t*, uint32_t)> txFn) {
  
  
//   logInfo("QromaBase64BracketBoundedPbProcessor - PROCESSING PB COMMANDS - NO BASE 64");
//   // for (int i=0; i < _qromaBytesProcessorsCount; i++) {
//   //   QromaBytesProcessor * thisProcessor = _qromaBytesProcessors[i];
//   //   uint32_t numBytesProcessed = thisProcessor->processBytes(bytes, byteCount);
//   //   if (numBytesProcessed > 0) {
//   //     logInfo("PROCESSED BYTES");
//   //     logInfo(numBytesProcessed);
//   //     return numBytesProcessed;
//   //   }
//   // }

//   for (int i=0; i < pbCommandsRegistry->getCommandHandlersCount(); i++) {
//     // QromaBytesProcessor * thisProcessor = _qromaBytesProcessors[i];
//     IPbCommandHandler * thisHandler = pbCommandsRegistry->getCommandHandler(i);
//     uint32_t numBytesProcessed = thisHandler->handleBytes(bytes, byteCount, txFn);
//     if (numBytesProcessed > 0) {
//       logInfo("PROCESSED BYTES");
//       logInfo(numBytesProcessed);
//       return numBytesProcessed;
//     }
//   }

//   return 0;
// }
