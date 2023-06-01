#ifndef QROMA_FS_COMMAND_PROCESSOR_INCLUDED
#define QROMA_FS_COMMAND_PROCESSOR_INCLUDED

#include "../../qroma-lib-proto/file-system-commands.pb.h"
#include "stdint.h"

class IQromaFsCommandProcessorListener {
  virtual void startFileReadingMode() = 0;
  virtual void endFileReadingMode() = 0;
}


class QromaFsCommandProcessor {
  public:
    uint32_t processBytes(const uint8_t * bytes, uint32_t byteCount);

    void handleFileSystemCommand(FileSystemCommand * fsCommand,
      QromaCommResponse * qromaCommResponse,
      std::function<void(uint8_t*, uint32_t)> txFn,
      IQromaFsCommandProcessorListener * fsListener);

    void handleRmFileCommand(RmFileCommand * cmd);
    void handleResetFilesystemCommand(ResetFilesystemCommand * cmd);

    void handleReportFileDataCommand(ReportFileDataCommand * cmd, PbBufferCommProcessor * comm);
    void handleStoreUpcomingFileCommand(StoreUpcomingFileDataCommand * cmd, PbBufferCommProcessor * comm);

    void handleListDirContents(ListDirContentsCommand * cmd, PbBufferCommProcessor * comm);
    void handlePrintDirContents(PrintDirContentsCommand * cmd, PbBufferCommProcessor * comm);
    void handlePrintFileContents(PrintFileContentsCommand * cmd, PbBufferCommProcessor * comm);
};

#endif
