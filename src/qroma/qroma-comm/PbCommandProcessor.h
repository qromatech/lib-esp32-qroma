#ifndef PB_COMMAND_PROCESSOR_H
#define PB_COMMAND_PROCESSOR_H

#include "QromaCommBuffer.h"

// #include "pbSerialComm.h"
// #include "chunkedPrintBuffer.h"

// #include "../../proto-nanopb/qroma-comm.pb.h"
// #include "../../proto-nanopb/file-system-commands.pb.h"


// typedef enum _CommReadingMode { 
//     CommReadingMode_NOT_SET = 0, 
//     CommReadingMode_PB_COMMANDS = 1, 
//     CommReadingMode_FILE_FROM_COMM = 2
// } CommReadingMode;


class PbCommandProcessor {

  public:
    uint32_t processQromaCommBuffer(QromaCommBuffer * buffer);
    
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
