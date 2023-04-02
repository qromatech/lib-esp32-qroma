#ifndef PB_COMMAND_PROCESSOR_H
#define PB_COMMAND_PROCESSOR_H

#include <RTOS.h>
#include <pb.h>
#include <pb_decode.h>
#include <functional>
#include "IPbCommandHandler.h"
// #include "commandTaskHandlers.h"

// #include "pbSerialComm.h"
// #include "chunkedPrintBuffer.h"

// #include "../../proto-nanopb/qroma-comm.pb.h"
// #include "../../proto-nanopb/file-system-commands.pb.h"


// typedef enum _CommReadingMode { 
//     CommReadingMode_NOT_SET = 0, 
//     CommReadingMode_PB_COMMANDS = 1, 
//     CommReadingMode_FILE_FROM_COMM = 2
// } CommReadingMode;

template<typename PbMessage, const pb_msgdesc_t *PbMessageFields>
class PbCommandHandler: public IPbCommandHandler {

  public:
    PbCommandHandler(std::function<void(PbMessage*)> handlerFunction) {
      _handlerFunction = handlerFunction;
    }
    
    // uint32_t processBytes(const uint8_t * bytes, uint32_t byteCount) {
    //   PbMessage pbMessage;

    //   for (int i=1; i <= byteCount; i++) {
    //     pb_istream_t stream = pb_istream_from_buffer(bytes, i);
    //     bool decoded = pb_decode(&stream, PbMessageFields, &pbMessage);

    //     if (decoded) {
    //       memcpy(&_pbMessage, &pbMessage, sizeof(PbMessage));

    //       BaseType_t xTaskStatus = xTaskCreate(taskHandlePbCommandProcessorCommand,
    //         "taskHandlePbCommandProcessorCommand", 12000, (void*)(QromaBytesProcessor*)this, 1, NULL);

    //       if (xTaskStatus != pdPASS) {
    //         logError("ERROR CREATING TASK: taskHandlePbCommandProcessorCommand");
    //         logError(xTaskStatus);
    //       }

    //       logInfo("PROCESSED");
    //       logInfo(i);

    //       return i;
    //     }
    //   }

    //   return 0;
    // }

    
    uint32_t handleBytes(const uint8_t * bytes, uint32_t byteCount, std::function<void(uint8_t*, uint32_t)> responseFn) {
      PbMessage pbMessage;

      for (int i=1; i <= byteCount; i++) {
        pb_istream_t stream = pb_istream_from_buffer(bytes, i);
        bool decoded = pb_decode(&stream, PbMessageFields, &pbMessage);

        if (decoded) {
          // memcpy(&_pbMessage, &pbMessage, sizeof(PbMessage));
          _handlerFunction(&pbMessage);

          // BaseType_t xTaskStatus = xTaskCreate(taskHandlePbCommandProcessorCommand,
          //   "taskHandlePbCommandProcessorCommand", 12000, (void*)(QromaBytesProcessor*)this, 1, NULL);

          // if (xTaskStatus != pdPASS) {
          //   logError("ERROR CREATING TASK: taskHandlePbCommandProcessorCommand");
          //   logError(xTaskStatus);
          // }

          logInfo("PROCESSED");
          logInfo(i);

          return i;
        }
      }

      return 0;
    }

    // void executeHandler() {
    //   _handlerFunction(&_pbMessage);
    // }
    
    // void doPbCommSetup();

    // void setLastCommTimeReadInMs(int when);
    // int getLastCommReadTimeInMs();

    // bool processCommBuffer();
    // int checkForNewPbCommCommand(QromaCommCommand * cmd);

    // void handleClearToSendQuery(ClearToSendQuery * ctsQuery);

    // void readSerialToFile(uint32_t silenceDelayTimeoutInMs, FileData * fileData);
    // void processFileData(char incomingByte);
    // void sendReadSerialToFileResponse(bool success, uint32_t crc);
    
    // void pbSendBytes(uint8_t * values, uint32_t count);
    // void pbSendMessage(const char * msg);
    // void pbSendQromacommResponse(uint8_t * values, uint32_t count);

    // void pbSendLine(const char * msg, const char * value);
    // void pbSendIntMessageLine(const char * msg, int value);

    // void setPbBuildingMessage(bool building);

  private:
    // PbMessage _pbMessage;

    std::function<void(PbMessage*)> _handlerFunction;
    // CommReadingMode _commReadingMode;
    // void setCommReadingMode(CommReadingMode mode);
    // bool processPbCommands();
    // bool processReadToFile();

    // char _readToFileName[40];
    // uint32_t _readToFileCount;
    // uint32_t _readToFileSize;
    // uint32_t _lastCommReadTimeInMs;
    // uint32_t _silenceDelayTimeoutInMs;
    // uint32_t _readToFileTimeoutInMs;
    // uint32_t _expectedChecksum;

    // bool _buildingMessage;
};

#endif
