#ifndef QROMA_PB64_NEWLINE_DELIMITED_PROCESSOR_H
#define QROMA_PB64_NEWLINE_DELIMITED_PROCESSOR_H

#include <pb.h>
#include "IQromaNewDataPbProcessor.h"
#include <qroma-lib-proto/qroma-comm.pb.h>
#include "../../util/logger.h"
#include "../../util/qbase64.h"
#include <pb_decode.h>
#include <pb_encode.h>
#include "fs_comm_handlers.h"


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
      
    void reset() { }

    uint32_t processBytes(const uint8_t * bytes, uint32_t byteCount, std::function<void(const uint8_t*, uint32_t)> txFn) {
      bool newLineFound = false;
      uint32_t newLineIndex = 0;
      int scanIndex = 0;
      uint32_t numBytesConsumed = 0;

      while (scanIndex < byteCount && !newLineFound) {
        if (bytes[scanIndex] == '\n') {
          newLineFound = true;
          newLineIndex = scanIndex;
          numBytesConsumed = newLineIndex + 1;
        }
        scanIndex++;
      }

      if (!newLineFound) {
        return 0;
      }

      auto decodedBufferLength = q_decode_base64(bytes, newLineIndex, _base64DecodeBuffer);

      handleQromaCommCommand(_base64DecodeBuffer, decodedBufferLength, txFn);

      return numBytesConsumed;
    }

    uint32_t handleQromaCommCommand(uint8_t * bytes, uint32_t bytesLength, std::function<void(uint8_t*, uint32_t)> txFn) {
      QromaCommCommand qromaCommCommand = QromaCommCommand_init_zero;

      PbMessage appMessage;
      memset(&appMessage, 0, sizeof(appMessage));

      pb_istream_t istream = pb_istream_from_buffer(bytes, bytesLength);
      bool decoded = pb_decode(&istream, QromaCommCommand_fields, &qromaCommCommand);

      if (decoded) {
        QromaCommResponse qromaCommResponse = QromaCommResponse_init_zero;

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
            break;
          case QromaCommCommand_fsCommand_tag:
            txFn((uint8_t *)"FS COMMAND", 10);

            handleFileSystemCommand(&(qromaCommCommand.command.fsCommand));
            // handleQromaCommFileSystemCommand(&(qromaCommCommand.command.fsCommand), &qromaCommResponse);
            break;
          case QromaCommCommand_commConfigCommand_tag:
            txFn((uint8_t *)"COMM COMMAND", 12);

            handleQromaCommConfigCommand(&(qromaCommCommand.command.commConfigCommand), &qromaCommResponse);
            break;
        }

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
      } else {
        // unsuccessful decode after reading a newline
      }

      return 0;
    }

    uint32_t handleAppCommand(PbMessage * pbMessage, QromaCommResponse * qromaCommResponse) {

      PbResponse appCommandResponse;
      _handlerFunction(pbMessage, &appCommandResponse);
      
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

      return 0;
    }


  // uint32_t handleQromaCommFileSystemCommand(FileSystemCommand * command, QromaCommResponse * response) {

  //   return 0;
  // }
  // uint32_t handleQromaCommFileSystemCommand(FileSystemCommand * command, QromaCommResponse * response);

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
