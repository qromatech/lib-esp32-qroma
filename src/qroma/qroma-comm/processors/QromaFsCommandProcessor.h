#ifndef QROMA_FS_COMMAND_PROCESSOR_INCLUDED
#define QROMA_FS_COMMAND_PROCESSOR_INCLUDED


#include <qroma-lib-proto/qroma-comm.pb.h>
#include <qroma-lib-proto/file-system-commands.pb.h>
#include "stdint.h"
#include <functional>
#include <pb_encode.h>


class IQromaFsCommandProcessorListener {
  public:
    virtual void startFileReadingMode(uint32_t silenceDelayTimeoutInMs, FileData * fileData) = 0;
  virtual void endFileReadingMode() = 0;
};


class QromaFsCommandProcessor {
  public:
    uint32_t processBytes(const uint8_t * bytes, uint32_t byteCount);

    bool handleFileSystemCommand(FileSystemCommand * fsCommand,
      QromaCommResponse * qromaCommResponse,
      std::function<void(uint8_t*, uint32_t)> txFn,
      IQromaFsCommandProcessorListener * fsListener);

  private:
    void handleRmFileCommand(RmFileCommand * cmd);
    void handleResetFilesystemCommand(ResetFilesystemCommand * cmd);

    bool handleReportFileDataCommand(ReportFileDataCommand * cmd, QromaCommResponse * qromaCommResponse);
    void handleStoreUpcomingFileCommand(StoreUpcomingFileDataCommand * cmd, IQromaFsCommandProcessorListener * fsListener);

    // void handleListDirContents(ListDirContentsCommand * cmd);
    void handlePrintDirContents(PrintDirContentsCommand * cmd, std::function<void(uint8_t*, uint32_t)> txFn);
    void handlePrintFileContents(PrintFileContentsCommand * cmd, std::function<void(uint8_t*, uint32_t)> txFn);
};

#endif
