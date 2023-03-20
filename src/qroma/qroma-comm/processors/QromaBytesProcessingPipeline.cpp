#include "QromaBytesProcessingPipeline.h"
#include "../../util/logger.h"


QromaBytesProcessingPipeline::QromaBytesProcessingPipeline() {
  _commSilenceDelayToClearBuffer = 3000;
  _processingMode = QromaBytesProcessingMode_PB_COMMANDS;
}


void QromaBytesProcessingPipeline::init(QromaBytesProcessor** qromaBytesProcessors, uint8_t qromaBytesProcessorsCount) {
  _qromaBytesProcessors = qromaBytesProcessors;
  _qromaBytesProcessorsCount = qromaBytesProcessorsCount;
}


bool QromaBytesProcessingPipeline::processCommBuffer(IQromaCommBuffer * commBuffer) {
  int commBufferWriteIndex = commBuffer->getBufferWriteIndex();
  if (commBufferWriteIndex == 0) {
    return false;
  }

  int now = millis();
  int bufferExpirationTime = commBuffer->getLastTimeAddedToInMs() + _commSilenceDelayToClearBuffer;
  if (now > bufferExpirationTime) {
    logInfo("processCommBuffer EXPIRED");
    setProcessingMode(QromaBytesProcessingMode_PB_COMMANDS);
    commBuffer->reset();
    return false;
  }

  const uint8_t * bytes = commBuffer->getBufferContent();
  uint32_t byteCount = commBuffer->getBufferWriteIndex();

  uint32_t numBytesProcessed = 0;

  switch (_processingMode) {
    case QromaBytesProcessingMode_PB_COMMANDS:
      // logInfo("Mode_PB_COMMANDS");
      numBytesProcessed = processPbCommands(bytes, byteCount);
      break;
    // case CommReadingMode_FILE_FROM_COMM:
    // case CommReadingMode_QROMA_DEVICE_CMD_FROM_COMM:
    // case CommReadingMode_QROMA_POINT_CMD_FROM_COMM:
    //   logInfo("Mode_FILE_FROM_COMM");
    //   return processReadToBuffer();
    //   break;
    case QromaBytesProcessingMode_NOT_SET:
      logError("Mode_NOT_SET");
      break;
    default:
      logError("Unrecognized Mode");
  }

  if (numBytesProcessed > 0) {
    commBuffer->removeFirstNFromBuffer(numBytesProcessed);
    return true;
  }

  return false;
}


void QromaBytesProcessingPipeline::setProcessingMode(QromaBytesProcessingMode mode) {
  _processingMode = mode;
}


uint32_t QromaBytesProcessingPipeline::processPbCommands(const uint8_t * bytes, uint32_t byteCount) {

  for (int i=0; i < _qromaBytesProcessorsCount; i++) {
    QromaBytesProcessor * thisProcessor = _qromaBytesProcessors[i];
    uint32_t numBytesProcessed = thisProcessor->processBytes(bytes, byteCount);
    if (numBytesProcessed > 0) {
      return numBytesProcessed;
      //     if (decoded) {
//       cbRemoveFirstNFromBuffer(i);
//       logInfo("REMOVE N FROM BUFFER");
//       logInfo(i);
//       logInfo(commBufferWriteIndex - i);
//       return i;
//     }
    }
  }

  return 0;




  // int validBufferSize = checkCommBufferForNewPbCommand(&_commPbQromaCommCommand);
  // if (validBufferSize <= 0) {
  //   return false;
  // }

  // QromaCommCommand * cmd = &_commPbQromaCommCommand;

  // switch (cmd->which_command)
  // {
  //   case QromaCommCommand_clearToSendQuery_tag:
  //     logInfo("CTS QUERY - LC");
  //     handleClearToSendQuery(&(cmd->command.clearToSendQuery));
  //     break;

  //   case QromaCommCommand_fsCommand_tag:
  //     logInfo("FILESYS - LC");
  //     handleFileSystemCommand(&(cmd->command.fsCommand), this);
  //     break;

  //   default:
  //     break;
  // }

  return true;
}


// int BytesProcessor::checkCommBufferForNewPbCommand(QromaCommCommand * cmd) {
//   int commBufferWriteIndex = cbGetCommBufferWriteIndex();
//   const uint8_t * commBuffer = cbGetCommBuffer();

//   for (int i=1; i <= commBufferWriteIndex; i++) {
//     pb_istream_t stream = pb_istream_from_buffer(commBuffer, i);
//     bool decoded = pb_decode(&stream, QromaCommCommand_fields, cmd);

//     if (decoded) {
//       cbRemoveFirstNFromBuffer(i);
//       logInfo("REMOVE N FROM BUFFER");
//       logInfo(i);
//       logInfo(commBufferWriteIndex - i);
//       return i;
//     }
//   }

//   return -1;
// }



// bool BytesProcessor::processQromaCommPbCommands() {

//   int validBufferSize = checkForNewQromaCommCommand(&_commPbQromaCommCommand);
//   if (validBufferSize <= 0) {
//     return false;
//   }

//   QromaCommCommand * cmd = &_commPbQromaCommCommand;

//   switch (cmd->which_command)
//   {
//     case QromaCommCommand_clearToSendQuery_tag:
//       logInfo("CTS QUERY - LC");
//       handleClearToSendQuery(&(cmd->command.clearToSendQuery));
//       break;

//     case QromaCommCommand_fsCommand_tag:
//       logInfo("FILESYS - LC");
//       handleFileSystemCommand(&(cmd->command.fsCommand), this);
//       break;

//     default:
//       break;
//   }

//   return true;
// }


// int BytesProcessor::checkForNewQromaCommCommand(QromaCommCommand * cmd) {
//   int commBufferWriteIndex = cbGetCommBufferWriteIndex();
//   const uint8_t * commBuffer = cbGetCommBuffer();

//   for (int i=1; i <= commBufferWriteIndex; i++) {
//     pb_istream_t stream = pb_istream_from_buffer(commBuffer, i);
//     bool decoded = pb_decode(&stream, QromaCommCommand_fields, cmd);

//     if (decoded) {
//       cbRemoveFirstNFromBuffer(i);
//       logInfo("REMOVE N FROM BUFFER");
//       logInfo(i);
//       logInfo(commBufferWriteIndex - i);
//       return i;
//     }
//   }

//   return -1;
// }