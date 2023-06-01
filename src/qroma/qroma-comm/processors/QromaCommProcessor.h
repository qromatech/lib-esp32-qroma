#ifndef QROMA_PB64_NEWLINE_DELIMITED_PROCESSOR_H
#define QROMA_PB64_NEWLINE_DELIMITED_PROCESSOR_H

#include <pb.h>
#include "IQromaNewBytesProcessor.h"
#include <qroma-lib-proto/qroma-comm.pb.h>
#include "../../util/logger.h"
#include "../../util/qbase64.h"
#include <pb_decode.h>
#include <pb_encode.h>
// #include "fs_comm_handlers.h"
#include "QromaFsCommandProcessor.h"
#include "QromaCommConfigProcessor.h"
#include "IAppCommandProcessor.h"
#include "QromaCommFileReader.h"


enum QromaCommProcessingMode {
  QromaCommProcessingMode_NotSet,
  QromaCommProcessingMode_QromaCommands,
  QromaCommProcessingMode_FileReader
};


// template<
//   typename PbMessage, 
//   const pb_msgdesc_t *PbMessageFields,
//   typename PbResponse, 
//   const pb_msgdesc_t *PbResponseFields
// >
class QromaCommProcessor: public IQromaNewBytesProcessor, 
                                 IQromaFsCommandProcessorListener 
{
  public:
    void init(IAppCommandProcessor * appCommandProcessor);
      
    void reset();

    uint32_t processBytes(const uint8_t * bytes, uint32_t byteCount, std::function<void(const uint8_t*, uint32_t)> txFn);

    uint32_t handleQromaCommCommand(uint8_t * bytes, uint32_t bytesLength, std::function<void(uint8_t*, uint32_t)> txFn);

    void startFileReadingMode(uint32_t silenceDelayTimeoutInMs, FileData * fileData);
    
    void endFileReadingMode();


  //   uint32_t handleAppCommand(PbMessage * pbMessage, QromaCommResponse * qromaCommResponse) {

  //     PbResponse appCommandResponse;
  //     _handlerFunction(pbMessage, &appCommandResponse);
      
  //     memset(&(qromaCommResponse->response.appResponseBytes), 0, sizeof(qromaCommResponse->response.appResponseBytes));

  //     pb_ostream_t ostream = pb_ostream_from_buffer(
  //       qromaCommResponse->response.appResponseBytes.bytes,
  //       sizeof(qromaCommResponse->response.appResponseBytes.bytes)
  //     );
  //     bool encoded = pb_encode(&ostream, PbResponseFields, &appCommandResponse);
  //     if (!encoded) {
  //       logError("ERROR handleAppCommand - handleBytes/encode");
  //       return false;
  //     }

  //     qromaCommResponse->response.appResponseBytes.size = ostream.bytes_written;
  //     qromaCommResponse->which_response = QromaCommResponse_appResponseBytes_tag;

  //     return 0;
  //   }


  // // uint32_t handleQromaCommFileSystemCommand(FileSystemCommand * command, QromaCommResponse * response) {

  // //   return 0;
  // // }
  // // uint32_t handleQromaCommFileSystemCommand(FileSystemCommand * command, QromaCommResponse * response);

  // uint32_t handleQromaCommConfigCommand(QromaCommConfigCommand * command, QromaCommResponse * response) {
  //   switch (command->which_command) {
  //     case QromaCommConfigCommand_setLogLevel_tag:
  //       setLogLevel(command->command.setLogLevel.logLevel);
  //       break;
  //   }
  //   return 0;
  // }


  private:
    // std::function<void(PbMessage*, PbResponse*)> _handlerFunction;
    // IQromaNewBytesProcessor * _appCommandProcessor;
    // QromaCommandProcessor _qromaCommandProcessor;
    IAppCommandProcessor * _appCommandProcessor;
    QromaFsCommandProcessor _qromaFsCommandProcessor;
    QromaCommConfigProcessor _qromaCommConfigProcessor;
    QromaCommFileReader _qromaCommFileReader;

    QromaCommProcessingMode _processingMode;

    // char _readToFileName[40];
    // uint32_t _expectedChecksum;

    // uint32_t _readToBufferCount;
    // uint32_t _readToBufferSize;
    // uint32_t _lastCommReadTimeInMs;
    // uint32_t _silenceDelayTimeoutInMs;
    // uint32_t _readToBufferTimeoutInMs;

    // IQromaNewBytesProcessor * _activeNewBytesProcessor;
    
    unsigned char _base64DecodeBuffer[1000];
    unsigned char _base64EncodeBuffer[1000];
};

#endif
