#ifndef QROMA_COMM_FILE_READER_H
#define QROMA_COMM_FILE_READER_H

#include <qroma-lib-proto/file-system-commands.pb.h>


class QromaCommFileReader {
  public:
    void startFileReadingMode(uint32_t silenceDelayTimeoutInMs, FileData * fileData);

  private:
    char _readToFileName[40];
    uint32_t _expectedChecksum;

    uint32_t _readToBufferCount;
    uint32_t _readToBufferSize;
    uint32_t _lastCommReadTimeInMs;
    uint32_t _silenceDelayTimeoutInMs;
    uint32_t _readToBufferTimeoutInMs;
};

#endif