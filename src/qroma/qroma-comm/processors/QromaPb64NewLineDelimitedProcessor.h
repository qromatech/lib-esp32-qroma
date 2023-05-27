#ifndef QROMA_PB64_NEWLINE_DELIMITED_PROCESSOR_H
#define QROMA_PB64_NEWLINE_DELIMITED_PROCESSOR_H

#include <pb.h>
#include "IQromaNewDataPbProcessor.h"
#include <qroma-lib-proto/qroma-comm.pb.h>
#include "../../util/logger.h"
#include "../../util/qbase64.h"
#include <pb_decode.h>
#include <pb_encode.h>


template<
  const pb_msgdesc_t *PbMessageFields
>
bool decodeAppCommand(pb_istream_t *istream, const pb_field_t *field, void **arg) {
  logInfo("IN DECODE APP COMMAND");
  // PbMessage pbMessage;
  bool decoded = pb_decode(istream, PbMessageFields, arg);

  return decoded;
}


template<
  typename PbMessage, 
  const pb_msgdesc_t *PbMessageFields,
  typename PbResponse, 
  const pb_msgdesc_t *PbResponseFields
>
class QromaPb64NewLineDelimitedProcessor: public IQromaNewDataPbProcessor {
  public:
    QromaPb64NewLineDelimitedProcessor(std::function<void(PbMessage*, PbResponse*)> handlerFunction) {
      _handlerFunction = handlerFunction;
    }

    // void reset();
    // uint32_t processBytes(const uint8_t * bytes, uint32_t byteCount, PbCommandsRegistry * pbCommandsRegistry, std::function<void(uint8_t*, uint32_t)> txFn);

      
  void reset() { }

  uint32_t processBytes(const uint8_t * bytes, uint32_t byteCount, std::function<void(const uint8_t*, uint32_t)> txFn) {
    // bool scanComplete = false;
    bool newLineFound = false;
    uint32_t newLineIndex = 0;
    // uint32_t trimCount = 0;
    int scanIndex = 0;
    uint32_t numBytesConsumed = 0;

    while (scanIndex < byteCount && !newLineFound) {
      if (bytes[scanIndex] == '\n') {
        newLineFound = true;
        // trimCount = scanIndex;
        newLineIndex = scanIndex;
        // scanComplete = true;
        numBytesConsumed = newLineIndex + 1;
      }
      scanIndex++;
    }

    txFn((uint8_t *)"====!\n", 6);
    txFn(bytes, byteCount);

    if (!newLineFound) {
      return 0;
    }

    txFn((uint8_t *)"DECODING", 8);

    char outBuffer[10];
    itoa(newLineIndex, outBuffer, 10);

    txFn((uint8_t *)"NEWLINE-INDEX>", 14);
    txFn((uint8_t *)outBuffer, (uint32_t)strlen(outBuffer));
    txFn((uint8_t *)"<.>", 3);

    auto decodedBufferLength = q_decode_base64(bytes, newLineIndex, _base64DecodeBuffer);

    txFn((uint8_t *)"HANDLING", 8);
    handleQromaCommCommand(_base64DecodeBuffer, decodedBufferLength, txFn);

    return numBytesConsumed;


    // logInfo("FOUND NEWLINE DELIMITED MESSAGE");
    // logInfo(decodedBufferLength);

    // auto base64EncodeAndTx = [this, txFn](uint8_t * bytes, uint32_t bytesLength) {
    //   logInfo("base64EncodeAndTx()");
    //   unsigned int encodedBufferLength = q_encode_base64(bytes, bytesLength, _base64EncodeBuffer);
    //   txFn(_base64EncodeBuffer, encodedBufferLength);
    //   txFn((uint8_t*)"\n", 1);
    // };
    
    // for (int i=0; i < pbCommandsRegistry->getCommandHandlersCount(); i++) {
    //   IPbCommandHandler * thisHandler = pbCommandsRegistry->getCommandHandler(i);
    //   uint32_t numBytesProcessed = thisHandler->handleBytes(_base64DecodeBuffer, decodedBufferLength, base64EncodeAndTx);
    //   if (numBytesProcessed > 0) {
    //     logInfo("PROCESSED BYTES");
    //     logInfo(numBytesConsumed);
    //     return numBytesConsumed;
    //   }
    // }

    return 0;
  }



    // uint32_t handleQromaCommCommand(uint8_t * bytes, uint32_t bytesLength, PbCommandsRegistry * pbCommandsRegistry, std::function<void(uint8_t*, uint32_t)> txFn);
    // uint32_t handleAppCommand(uint8_t * bytes, uint32_t bytesLength, PbCommandsRegistry * pbCommandsRegistry, std::function<void(uint8_t*, uint32_t)> txFn);
    // uint32_t handleQromaCommFileSystemCommand(FileSystemCommand * command, QromaCommResponse * response);
    // uint32_t handleQromaCommConfigCommand(QromaCommConfigCommand * command, QromaCommResponse * response);
    
    

    // PbMessage pbMessage;

    // // pb_istream_t istream = pb_istream_from_buffer(bytes, byteCount);
    // bool decoded = pb_decode(istream, PbMessageFields, &pbMessage);
    // // logInfo("base64EncodeAndTx()");
    // // unsigned int encodedBufferLength = q_encode_base64(bytes, bytesLength, _base64EncodeBuffer);
    // // txFn(_base64EncodeBuffer, encodedBufferLength);
    // // txFn((uint8_t*)"\n", 1);

    // if (decoded) {
    //   PbResponse pbResponse;
    //   memset(&pbResponse, 0, sizeof(pbResponse));

    //   // handlerFunction(&pbMessage, &pbResponse);

    //   uint8_t encodeBuffer[2000];
    //   memset(encodeBuffer, 0, sizeof(encodeBuffer));
  
    //   pb_ostream_t ostream = pb_ostream_from_buffer(encodeBuffer, sizeof(encodeBuffer));
    //   bool encoded = pb_encode(&ostream, PbResponseFields, &pbResponse);
    //   if (!encoded) {
    //     logError("ERROR PbCommandWithResponseHandler - handleBytes/encode");
    //     return false;
    //   }

    //   // responseFn(encodeBuffer, ostream.bytes_written);
    //   // return byteCount;
    //   return true;
    // }

    // return decoded;


  // bool decodeAppCommand(pb_istream_t *istream, const pb_field_t *field, void **arg) {
  //   // PbMessage pbMessage;
  //   bool decoded = pb_decode(istream, PbMessageFields, arg);

  //   return decoded;
  // }


  uint32_t handleQromaCommCommand(uint8_t * bytes, uint32_t bytesLength, std::function<void(uint8_t*, uint32_t)> txFn) {
    QromaCommCommand qromaCommCommand = QromaCommCommand_init_zero;

    PbMessage appMessage;
    memset(&appMessage, 0, sizeof(appMessage));
    // qromaCommCommand.command.appCommandBytes.arg = &appMessage;
    // qromaCommCommand.command.appCommandBytes.funcs.decode = decodeAppCommand<PbMessageFields>;

    pb_istream_t istream = pb_istream_from_buffer(bytes, bytesLength);
    bool decoded = pb_decode(&istream, QromaCommCommand_fields, &qromaCommCommand);

    char outBuffer[10];
    itoa(bytesLength, outBuffer, 10);

    txFn((uint8_t *)"QROMAAPP>", 9);
    txFn((uint8_t *)outBuffer, (uint32_t)strlen(outBuffer));
    txFn((uint8_t *)"<.>", 3);

    for (int i=0; i < bytesLength; i++) {
      itoa(bytes[i], outBuffer, 10);
      
      txFn((uint8_t *)outBuffer, (uint32_t)strlen(outBuffer));
      txFn((uint8_t *)".", 1);
    }
    txFn((uint8_t *)"---", 3);

    if (decoded) {
      QromaCommResponse qromaCommResponse = QromaCommResponse_init_zero;
      // memset(&qromaCommResponse, 0, sizeof(qromaCommResponse));

      // uint32_t bytesConsumed = 0;

      // PbMessage * appCommand = (PbMessage*)qromaCommCommand.command.appCommandBytes.arg;
      // PbResponse appResponse;

      switch (qromaCommCommand.which_command) {
        case QromaCommCommand_appCommandBytes_tag: {
          PbMessage appCommand;
          pb_istream_t appCommand_istream = pb_istream_from_buffer(qromaCommCommand.command.appCommandBytes.bytes, qromaCommCommand.command.appCommandBytes.size);
          bool appCommandDecoded = pb_decode(&appCommand_istream, PbMessageFields, &appCommand);
          if (!appCommandDecoded) {
            txFn((uint8_t *)"ERR APP COMMAND", 15);
            return 0;
          }

          txFn((uint8_t *)"DO APP COMMAND", 14);
          PbResponse appResponse;
          handleAppCommand(&appCommand, &(qromaCommResponse));
        }

          // handleAppCommand(appCommand, &appResponse);
          // handleAppCommand(bytes, bytesLength, pbCommandsRegistry, txFn);

          break;
        case QromaCommCommand_fsCommand_tag:
          txFn((uint8_t *)"FS COMMAND", 10);

          handleQromaCommFileSystemCommand(&(qromaCommCommand.command.fsCommand), &qromaCommResponse);
          break;
        case QromaCommCommand_commConfigCommand_tag:
          txFn((uint8_t *)"COMM COMMAND", 12);

          handleQromaCommConfigCommand(&(qromaCommCommand.command.commConfigCommand), &qromaCommResponse);
          break;
      }

      // _handlerFunction(&pbMessage, &pbResponse);

      uint8_t encodeBuffer[2000];
      memset(encodeBuffer, 0, sizeof(encodeBuffer));

      pb_ostream_t ostream = pb_ostream_from_buffer(encodeBuffer, sizeof(encodeBuffer));
      bool encoded = pb_encode(&ostream, QromaCommResponse_fields, &qromaCommResponse);
      if (!encoded) {
        logError("ERROR handleQromaCommCommand - handleBytes/encode");
        return 0;
      }

      txFn(encodeBuffer, ostream.bytes_written);
      return bytesLength;
    }

    return 0;
  }


  // uint32_t handleAppCommand(uint8_t * bytes, uint32_t bytesLength, PbResponse * pbResponse, std::function<void(uint8_t*, uint32_t)> txFn) {
    uint32_t handleAppCommand(PbMessage * pbMessage, QromaCommResponse * qromaCommResponse) {

      PbResponse appCommandResponse;
      _handlerFunction(pbMessage, &appCommandResponse);

      // uint8_t encodeBuffer[1000];
      
      memset(&(qromaCommResponse->response.appResponseBytes), 0, sizeof(qromaCommResponse->response.appResponseBytes));

      pb_ostream_t ostream = pb_ostream_from_buffer(
        qromaCommResponse->response.appResponseBytes.bytes,
        sizeof(qromaCommResponse->response.appResponseBytes.bytes)
      );
      bool encoded = pb_encode(&ostream, PbResponseFields, &appCommandResponse);
      if (!encoded) {
        logError("ERROR handleAppCommand - handleBytes/encode");
        return false;
      }

      qromaCommResponse->response.appResponseBytes.size = ostream.bytes_written;
      qromaCommResponse->which_response = QromaCommResponse_appResponseBytes_tag;



    // auto base64EncodeAndTx = [this, txFn](uint8_t * bytes, uint32_t bytesLength) {
    //   logInfo("base64EncodeAndTx()");
    //   unsigned int encodedBufferLength = q_encode_base64(bytes, bytesLength, _base64EncodeBuffer);
    //   txFn(_base64EncodeBuffer, encodedBufferLength);
    //   txFn((uint8_t*)"\n", 1);
    // };
    
    // if (pbCommandsRegistry->getAppCommandHandler() != NULL) {
    //   pbCommandsRegistry->getAppCommandHandler()->handleBytes(bytes, bytesLength, base64EncodeAndTx);
    // }

    // for (int i=0; i < pbCommandsRegistry->getCommandHandlersCount(); i++) {
    //   IPbCommandHandler * thisHandler = pbCommandsRegistry->getCommandHandler(i);
    //   uint32_t numBytesProcessed = thisHandler->handleBytes(_base64DecodeBuffer, decodedBufferLength, base64EncodeAndTx);
    //   if (numBytesProcessed > 0) {
    //     logInfo("PROCESSED BYTES");
    //     logInfo(numBytesConsumed);
    //     return numBytesConsumed;
    //   }
    // }

    return 0;
  }


  uint32_t handleQromaCommFileSystemCommand(FileSystemCommand * command, QromaCommResponse * response) {
    return 0;
  }


  uint32_t handleQromaCommConfigCommand(QromaCommConfigCommand * command, QromaCommResponse * response) {
    switch (command->which_command) {
      case QromaCommConfigCommand_setLogLevel_tag:
        setLogLevel(command->command.setLogLevel.logLevel);
        break;
    }
    return 0;
  }


  private:
    std::function<void(PbMessage*, PbResponse*)> _handlerFunction;
    unsigned char _base64DecodeBuffer[1000];
    unsigned char _base64EncodeBuffer[1000];
};

#endif
