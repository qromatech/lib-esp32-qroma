#ifndef QROMA_COMM_STREAM_READER_H
#define QROMA_COMM_STREAM_READER_H

#include "LittleFS.h"
#include <qroma-lib-proto/qroma-streams.pb.h>
#include <qroma-lib-proto/qroma-comm.pb.h>
#include "IQromaCommStreamRxHandler.h"


class QromaCommStreamReader {
  public:
    void handleQromaStreamCommand(QromaStreamCommand * streamCommand, std::function<void(uint8_t*, uint32_t)> txFn,
      IQromaCommStreamRxHandler * streamRxHandler);
    uint32_t processBytes(const uint8_t * bytes, uint32_t byteCount);

    void populateInitWriteFileStreamAckResponse(QromaCommResponse * qromaCommResponse,
      bool success, const char * message, uint32_t fileStreamId);
    void populateWriteFileStreamCompleteWithErrResponse(QromaCommResponse * qromaCommResponse,
      const char * message, uint32_t fileStreamId);
    void populateWriteFileStreamCompleteSuccessResponse(QromaCommResponse * qromaCommResponse,
      const char * message, uint32_t fileStreamId, uint32_t crc);

    void handleInitWriteFileStreamCommand(InitWriteFileStreamCommand * command,
      std::function<void(uint8_t*, uint32_t)> txFn, IQromaCommStreamRxHandler * streamRxHandler);

    // void startStreamReadingMode(uint32_t silenceDelayTimeoutInMs, FileData * fileData);

  private:
    File _streamToFile;
    char _readToFileName[40];
    uint32_t _expectedChecksum;
    uint32_t _expectedFileSize;
    uint32_t _fileStreamId;

    std::function<void(uint8_t*, uint32_t)> _txFn;
    IQromaCommStreamRxHandler * _streamRxHandler;

    uint32_t _numberOfBytesWrittenSoFar;
    uint32_t _lastCommReadTimeInMs;

    // uint32_t _readToBufferSize;
    // uint32_t _silenceDelayTimeoutInMs;
    // uint32_t _readToBufferTimeoutInMs;
};

#endif