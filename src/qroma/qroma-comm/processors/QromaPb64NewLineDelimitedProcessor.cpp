#include "QromaPb64NewLineDelimitedProcessor.h"
#include "../pb-commands/IPbCommandHandler.h"
#include "../../util/logger.h"
#include "../../util/qbase64.h"
#include <pb_decode.h>
#include <pb_encode.h>


// void QromaPb64NewLineDelimitedProcessor::reset() { }


// uint32_t QromaPb64NewLineDelimitedProcessor::processBytes(const uint8_t * bytes, uint32_t byteCount,
//   PbCommandsRegistry * pbCommandsRegistry, std::function<void(uint8_t*, uint32_t)> txFn) 
// {
//   bool scanComplete = false;
//   bool newLineFound = false;
//   uint32_t newLineIndex = 0;
//   uint32_t trimCount = 0;
//   int scanIndex = 0;
//   uint32_t numBytesConsumed = 0;

//   while (scanIndex < byteCount && !scanComplete) {
//     if (bytes[scanIndex] == '\n') {
//       newLineFound = true;
//       trimCount = scanIndex;
//       newLineIndex = scanIndex;
//       scanComplete = true;
//       numBytesConsumed = newLineIndex + 1;
//     }
//     scanIndex++;
//   }

//   if (!scanComplete) {
//     return 0;
//   }

//   auto decodedBufferLength = q_decode_base64(bytes, newLineIndex, _base64DecodeBuffer);

//   return handleQromaCommCommand(_base64DecodeBuffer, decodedBufferLength, pbCommandsRegistry, txFn);


//   // logInfo("FOUND NEWLINE DELIMITED MESSAGE");
//   // logInfo(decodedBufferLength);

//   // auto base64EncodeAndTx = [this, txFn](uint8_t * bytes, uint32_t bytesLength) {
//   //   logInfo("base64EncodeAndTx()");
//   //   unsigned int encodedBufferLength = q_encode_base64(bytes, bytesLength, _base64EncodeBuffer);
//   //   txFn(_base64EncodeBuffer, encodedBufferLength);
//   //   txFn((uint8_t*)"\n", 1);
//   // };
  
//   // for (int i=0; i < pbCommandsRegistry->getCommandHandlersCount(); i++) {
//   //   IPbCommandHandler * thisHandler = pbCommandsRegistry->getCommandHandler(i);
//   //   uint32_t numBytesProcessed = thisHandler->handleBytes(_base64DecodeBuffer, decodedBufferLength, base64EncodeAndTx);
//   //   if (numBytesProcessed > 0) {
//   //     logInfo("PROCESSED BYTES");
//   //     logInfo(numBytesConsumed);
//   //     return numBytesConsumed;
//   //   }
//   // }

//   return 0;
// }


// bool decode_callback(pb_istream_t *stream, const pb_field_t *field, void ** arg) {

// }

// uint32_t QromaPb64NewLineDelimitedProcessor::handleQromaCommCommand(uint8_t * bytes, uint32_t bytesLength, 
//   PbCommandsRegistry * pbCommandsRegistry, std::function<void(uint8_t*, uint32_t)> txFn) 
// {
//   QromaCommCommand qromaCommCommand = QromaCommCommand_init_zero;
//   qromaCommCommand.command.appCommand.funcs.decode = pbCommandsRegistry->decodeFunc;
//   // qromaCommCommand.command.appCommand.funcs.decode = decode_callback;

//   pb_istream_t istream = pb_istream_from_buffer(bytes, bytesLength);
//   bool decoded = pb_decode(&istream, QromaCommCommand_fields, &qromaCommCommand);

//   if (decoded) {
//     QromaCommResponse qromaCommResponse = QromaCommResponse_init_zero;
//     // memset(&qromaCommResponse, 0, sizeof(qromaCommResponse));

//     // uint32_t bytesConsumed = 0;

//     switch (qromaCommCommand.which_command) {
//       case QromaCommCommand_appCommand_tag:
//         // qromaCommCommand.command.
//         // handleAppCommand(&(qromaCommCommand.command.appCommand), )
//         // handleAppCommand(bytes, bytesLength, pbCommandsRegistry, txFn);

//         break;
//       case QromaCommCommand_fsCommand_tag:
//         handleQromaCommFileSystemCommand(&(qromaCommCommand.command.fsCommand), &qromaCommResponse);
//         break;
//       case QromaCommCommand_commConfigCommand_tag:
//         handleQromaCommConfigCommand(&(qromaCommCommand.command.commConfigCommand), &qromaCommResponse);
//         break;
//     }

//     // _handlerFunction(&pbMessage, &pbResponse);

//     uint8_t encodeBuffer[2000];
//     memset(encodeBuffer, 0, sizeof(encodeBuffer));

//     pb_ostream_t ostream = pb_ostream_from_buffer(encodeBuffer, sizeof(encodeBuffer));
//     bool encoded = pb_encode(&ostream, QromaCommResponse_fields, &qromaCommResponse);
//     if (!encoded) {
//       logError("ERROR handleQromaCommCommand - handleBytes/encode");
//       return 0;
//     }

//     txFn(encodeBuffer, ostream.bytes_written);
//     return bytesLength;
//   }

//   return 0;
// }


// uint32_t QromaPb64NewLineDelimitedProcessor::handleAppCommand(uint8_t * bytes, uint32_t bytesLength, 
//   PbCommandsRegistry * pbCommandsRegistry, std::function<void(uint8_t*, uint32_t)> txFn) 
// {

//   auto base64EncodeAndTx = [this, txFn](uint8_t * bytes, uint32_t bytesLength) {
//     logInfo("base64EncodeAndTx()");
//     unsigned int encodedBufferLength = q_encode_base64(bytes, bytesLength, _base64EncodeBuffer);
//     txFn(_base64EncodeBuffer, encodedBufferLength);
//     txFn((uint8_t*)"\n", 1);
//   };
  
//   if (pbCommandsRegistry->getAppCommandHandler() != NULL) {
//     pbCommandsRegistry->getAppCommandHandler()->handleBytes(bytes, bytesLength, base64EncodeAndTx);
//   }

//   // for (int i=0; i < pbCommandsRegistry->getCommandHandlersCount(); i++) {
//   //   IPbCommandHandler * thisHandler = pbCommandsRegistry->getCommandHandler(i);
//   //   uint32_t numBytesProcessed = thisHandler->handleBytes(_base64DecodeBuffer, decodedBufferLength, base64EncodeAndTx);
//   //   if (numBytesProcessed > 0) {
//   //     logInfo("PROCESSED BYTES");
//   //     logInfo(numBytesConsumed);
//   //     return numBytesConsumed;
//   //   }
//   // }

//   return 0;
// }


// uint32_t QromaPb64NewLineDelimitedProcessor::handleQromaCommFileSystemCommand(FileSystemCommand * command, QromaCommResponse * response) {
//   return 0;
// }


// uint32_t QromaPb64NewLineDelimitedProcessor::handleQromaCommConfigCommand(QromaCommConfigCommand * command, QromaCommResponse * response) {
//   switch (command->which_command) {
//     case QromaCommConfigCommand_setLogLevel_tag:
//       setLogLevel(command->command.setLogLevel.logLevel);
//       break;
//   }
//   return 0;
// }
