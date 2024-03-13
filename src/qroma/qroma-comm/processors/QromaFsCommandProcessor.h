#ifndef QROMA_FS_COMMAND_PROCESSOR_INCLUDED
#define QROMA_FS_COMMAND_PROCESSOR_INCLUDED


#include <qroma-lib-proto/qroma-comm.pb.h>
#include <qroma-lib-proto/file-system-commands.pb.h>
#include "stdint.h"
#include <functional>
#include <pb_encode.h>


class QromaFsCommandProcessor {
  public:
    bool handleFileSystemCommand(FileSystemCommand * fsCommand,
      QromaCommResponse * qromaCommResponse,
      std::function<void(uint8_t*, uint32_t)> txFn
      );

  private:
    bool handleRmFileCommand(RmFileCommand * cmd);
    bool handleResetFilesystemCommand(ResetFilesystemCommand * cmd);

    bool handleReportFileDataCommand(ReportFileDataCommand * cmd, FileSystemResponse * fsResponse);

    bool handleWriteFileDataCommand(WriteFileDataCommand * cmd, FileSystemResponse * fsResponse);

    void handlePrintDirContents(PrintDirContentsCommand * cmd, std::function<void(uint8_t*, uint32_t)> txFn);
    bool handleGetFileContents(GetFileContentsCommand * cmd, FileSystemResponse * fsResponse);

    bool handleListDirContentsCommand(ListDirContentsCommand * cmd, FileSystemResponse * fsResponse);
    bool handleMkDirCommand(MkDirCommand * cmd, FileSystemResponse * fsResponse);
    bool handleRmDirCommand(RmDirCommand * cmd, FileSystemResponse * fsResponse);
};

#endif
