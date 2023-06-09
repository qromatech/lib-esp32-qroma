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
    // uint32_t processBytes(const uint8_t * bytes, uint32_t byteCount);

    bool handleFileSystemCommand(FileSystemCommand * fsCommand,
      QromaCommResponse * qromaCommResponse,
      std::function<void(uint8_t*, uint32_t)> txFn,
      IQromaFsCommandProcessorListener * fsListener);

  private:
    bool handleRmFileCommand(RmFileCommand * cmd);
    bool handleResetFilesystemCommand(ResetFilesystemCommand * cmd);

    bool handleReportFileDataCommand(ReportFileDataCommand * cmd, QromaCommResponse * qromaCommResponse);
    // void handleStoreUpcomingFileCommand(StoreUpcomingFileDataCommand * cmd, IQromaFsCommandProcessorListener * fsListener);

    bool handleWriteFileDataCommand(WriteFileDataCommand * cmd, QromaCommResponse * qromaCommResponse);

    // void handleListDirContents(ListDirContentsCommand * cmd);
    void handlePrintDirContents(PrintDirContentsCommand * cmd, std::function<void(uint8_t*, uint32_t)> txFn);
    bool handleGetFileContents(GetFileContentsCommand * cmd, QromaCommResponse * response);

    bool handleListDirContentsCommand(ListDirContentsCommand * cmd, QromaCommResponse * response);
    bool handleMkDirCommand(MkDirCommand * cmd, QromaCommResponse * response);
    bool handleRmDirCommand(RmDirCommand * cmd, QromaCommResponse * response);

};

#endif
