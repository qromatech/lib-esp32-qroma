#ifndef QROMA_FS_COMMAND_PROCESSOR_INCLUDED
#define QROMA_FS_COMMAND_PROCESSOR_INCLUDED

// #include "../../proto-nanopb/file-system-commands.pb.h"
// #include "pbBufferCommProcessor.h"
#include "stdint.h"


// void handleRmFileCommand(RmFileCommand * cmd);
// void handleResetFilesystemCommand(ResetFilesystemCommand * cmd);

// void handleFileSystemCommand(FileSystemCommand * fsCommand, PbBufferCommProcessor * comm);
// void handleReportFileDataCommand(ReportFileDataCommand * cmd, PbBufferCommProcessor * comm);
// void handleStoreUpcomingFileCommand(StoreUpcomingFileDataCommand * cmd, PbBufferCommProcessor * comm);

// void handleListDirContents(ListDirContentsCommand * cmd, PbBufferCommProcessor * comm);
// void handlePrintDirContents(PrintDirContentsCommand * cmd, PbBufferCommProcessor * comm);
// void handlePrintFileContents(PrintFileContentsCommand * cmd, PbBufferCommProcessor * comm);

class QromaFsCommandProcessor {
  public:
    uint32_t processBytes(const uint8_t * bytes, uint32_t byteCount);
};

#endif
