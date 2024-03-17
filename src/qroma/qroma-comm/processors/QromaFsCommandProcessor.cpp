#include "LittleFS.h"
#include "QromaFsCommandProcessor.h"
#include <qroma/util/logger.h>
#include <qroma/util/fs.h>



void pbSendLine(const char * msg, const char * value, std::function<void(uint8_t*, uint32_t)> txFn) {
  char msgBuffer[200];
  memset(msgBuffer, 0, sizeof msgBuffer);

  strlcpy(msgBuffer, msg, sizeof msgBuffer);
  strlcat(msgBuffer, value, sizeof msgBuffer);
  size_t len = strlcat(msgBuffer, "\n", sizeof msgBuffer);
  
  txFn((uint8_t *)msgBuffer, len);
}


void pbSendMessage(const char * msg, std::function<void(uint8_t*, uint32_t)> txFn) {
  pbSendLine(msg, "", txFn);
}


void pbSendIntMessageLine(const char * msg, int value, std::function<void(uint8_t*, uint32_t)> txFn) {
  char vBuf[20];
  sprintf(vBuf, "%d", value);
  
  pbSendLine(msg, vBuf, txFn);
}
 

// return true if caller should return the populated QromaCommResponse
bool QromaFsCommandProcessor::handleFileSystemCommand(FileSystemCommand * fsCommand,
  QromaCommResponse * qromaCommResponse,
  // FileSystemResponse * fsResponse,
  std::function<void(uint8_t*, uint32_t)> txFn)
{
  logInfoIntWithDescription("handleFileSystemCommand - ", fsCommand->which_command);

  qromaCommResponse->which_response = QromaCommResponse_fsResponse_tag;
  FileSystemResponse * fsResponse = &(qromaCommResponse->response.fsResponse);

  switch (fsCommand->which_command)
  {
    case FileSystemCommand_rmFileCommand_tag:
      handleRmFileCommand(&(fsCommand->command.rmFileCommand));
      break;

    case FileSystemCommand_resetFilesystemCommand_tag:
      handleResetFilesystemCommand(&(fsCommand->command.resetFilesystemCommand));
      break;

    case FileSystemCommand_writeFileDataCommand_tag:
      logInfo("WRITE FILE DATA");
      return handleWriteFileDataCommand(&(fsCommand->command.writeFileDataCommand), fsResponse);

    case FileSystemCommand_reportFileDataCommand_tag:
      return handleReportFileDataCommand(&(fsCommand->command.reportFileDataCommand), fsResponse);
      break;

    case FileSystemCommand_getFileContentsCommand_tag:
      return handleGetFileContents(&(fsCommand->command.getFileContentsCommand), fsResponse);
      break;

    case FileSystemCommand_listDirContentsCommand_tag:
      return handleListDirContentsCommand(&(fsCommand->command.listDirContentsCommand), fsResponse);
      break;
    
    case FileSystemCommand_mkDirCommand_tag:
      return handleMkDirCommand(&(fsCommand->command.mkDirCommand), fsResponse);
      break;

    case FileSystemCommand_rmDirCommand_tag:
      return handleRmDirCommand(&(fsCommand->command.rmDirCommand), fsResponse);
      break;

    default:
      break;
  }

  return false;
}


bool QromaFsCommandProcessor::handleReportFileDataCommand(ReportFileDataCommand * cmd, FileSystemResponse * fsResponse) {
  fsResponse->which_response = FileSystemResponse_reportFileDataResponse_tag;
  
  File file = LittleFS.open(cmd->filePath);

  if (file == NULL) {
    logError("reportFileDataResponse - failed to open file");
    logError(cmd->filePath);
    logError("FILE IS NULL");
    fsResponse->response.reportFileDataResponse.fileStatus = GetFileStatusCode_GFSC_ERR_OPEN_FILE;
    return true;
  }

  if (file.isDirectory()) {
    logError("reportFileDataResponse - not a file; it's a directory");
    logError(cmd->filePath);
    logError("GOT DIRECTORY");
    fsResponse->response.reportFileDataResponse.fileStatus = GetFileStatusCode_GFSC_ERR_INVALID_FILE_PATH;
    return true;
  }

  int fileSize = file.size();
  file.close();

  uint32_t checkSum = getFileChecksum(cmd->filePath);

  logInfoIntWithDescription("FILE SIZE: ", fileSize);
  logInfoUintWithDescription("FILE CHECKSUM: ", checkSum);

  fsResponse->response.reportFileDataResponse.fileStatus = GetFileStatusCode_GFSC_FILE_EXISTS;
  fsResponse->response.reportFileDataResponse.has_fileData = true;
  fsResponse->response.reportFileDataResponse.fileData.filesize = fileSize;
  fsResponse->response.reportFileDataResponse.fileData.checksum = checkSum;
  strncpy(fsResponse->response.reportFileDataResponse.fileData.filename, cmd->filePath, 
    sizeof(fsResponse->response.reportFileDataResponse.fileData.filename));

  return true;
}


bool QromaFsCommandProcessor::handleListDirContentsCommand(ListDirContentsCommand * cmd, FileSystemResponse * fsResponse) {
  fsResponse->which_response = FileSystemResponse_listDirContentsResponse_tag;
  fsResponse->response.listDirContentsResponse.success = false;

  File root = LittleFS.open(cmd->dirPath);
  if (root == NULL) {
    logError("handleListDirContentsCommand - failed to open directory");
    logError("FS ROOT IS NULL");
    return true;
  }

  File file = root.openNextFile();

  int fileIndex = 0;

  int maxDirItemsAllowed = sizeof(fsResponse->response.listDirContentsResponse.dirItems) /
    sizeof(fsResponse->response.listDirContentsResponse.dirItems[0]);

  fsResponse->response.listDirContentsResponse.dirItems_count = 0;
  while (file && fileIndex < maxDirItemsAllowed) {
    bool fileMeetsConstraints = true;
    if (strlen(cmd->startsWithConstraint) > 0) {
      if (strncmp(file.name(), cmd->startsWithConstraint, strlen(cmd->startsWithConstraint)) != 0) {
        fileMeetsConstraints = false;
      }
    }

    if (strlen(cmd->endsWithConstraint) > 0) {
      const char * fname = file.name();
      char * x = strrchr(fname, cmd->endsWithConstraint[0]);
      if (x == NULL) {
        fileMeetsConstraints = false;
      } else {
      if (strncmp(fname, cmd->endsWithConstraint, strlen(cmd->endsWithConstraint)) != 0) {
          fileMeetsConstraints = false;
        }
      }
    }

    if (fileMeetsConstraints) {
        strncpy(fsResponse->response.listDirContentsResponse.dirItems[fileIndex].name, file.name(),
          sizeof(fsResponse->response.listDirContentsResponse.dirItems[0].name));
        if (file.isDirectory()) {
          fsResponse->response.listDirContentsResponse.dirItems[fileIndex].dirItemType = DirItemType_DIT_DIR;
        } else {
          fsResponse->response.listDirContentsResponse.dirItems[fileIndex].dirItemType = DirItemType_DIT_FILE;
        }
        fsResponse->response.listDirContentsResponse.dirItems_count++;
      fileIndex++;
      }

    file = root.openNextFile();
  }

  fsResponse->response.listDirContentsResponse.success = true;
  strncpy(fsResponse->response.listDirContentsResponse.dirPath,
          cmd->dirPath,
          sizeof(fsResponse->response.listDirContentsResponse.dirPath));

  return true;
}


bool QromaFsCommandProcessor::handleMkDirCommand(MkDirCommand * cmd, FileSystemResponse * fsResponse) {
  bool success = LittleFS.mkdir(cmd->dirPath);

  fsResponse->which_response = FileSystemResponse_mkDirResponse_tag;
  fsResponse->response.mkDirResponse.success = success;
  fsResponse->response.mkDirResponse.has_mkDirCommand = true;
  strncpy(fsResponse->response.mkDirResponse.mkDirCommand.dirPath, cmd->dirPath,
    sizeof(fsResponse->response.mkDirResponse.mkDirCommand.dirPath));

  logInfo("handleMkDirCommand");
  logInfo(cmd->dirPath);
  logInfo(fsResponse->response.mkDirResponse.mkDirCommand.dirPath);

  return true;
}


bool QromaFsCommandProcessor::handleRmDirCommand(RmDirCommand * cmd, FileSystemResponse * fsResponse) {
  bool success = LittleFS.rmdir(cmd->dirPath);

  fsResponse->which_response = FileSystemResponse_rmDirResponse_tag;
  fsResponse->response.rmDirResponse.success = success;
  fsResponse->response.rmDirResponse.has_rmDirCommand = true;
  strncpy(fsResponse->response.rmDirResponse.rmDirCommand.dirPath, cmd->dirPath,
    sizeof(fsResponse->response.rmDirResponse.rmDirCommand.dirPath));

  logInfo("handleRmDirCommand");
  logInfo(cmd->dirPath);
  logInfo(fsResponse->response.rmDirResponse.rmDirCommand.dirPath);

  return true;
}


bool QromaFsCommandProcessor::handleRmFileCommand(RmFileCommand * cmd) {
  logInfo("REMOVING FILE");
  logInfo(cmd->filePath);

  LittleFS.remove(cmd->filePath);
  
  logInfo("HANDLED RM FILE");
  logInfo(cmd->filePath);
  
  return true;
}


bool QromaFsCommandProcessor::handleResetFilesystemCommand(ResetFilesystemCommand * cmd) {
  return resetFilesystem();
}


bool QromaFsCommandProcessor::handleWriteFileDataCommand(WriteFileDataCommand * cmd, FileSystemResponse * fsResponse) {

  fsResponse->which_response = FileSystemResponse_writeFileDataResponse_tag;

  logInfo("WRITING FILE");
  logInfo(cmd->fileData.filename);
  logInfo(cmd->fileData.filesize);
  logInfo(cmd->fileData.checksum);

  File file = LittleFS.open(cmd->fileData.filename, FILE_WRITE);
  if (!file) {
    logInfo("NO FILE OPENED");
    logInfo(cmd->fileData.filename);
    fsResponse->response.writeFileDataResponse.statusCode = WriteFileDataStatusCode_WFDSC_ERR_OPEN_FILE;
    return true;
  }

  bool writeSuccess = file.write(cmd->fileBytes.bytes, cmd->fileBytes.size);
  file.close();

  uint32_t crc = getFileChecksum(cmd->fileData.filename);

  if (crc != cmd->fileData.checksum) {
    fsResponse->response.writeFileDataResponse.statusCode = WriteFileDataStatusCode_WFDSC_ERR_CRC_MISMATCH;
    return true;
  }

  fsResponse->response.writeFileDataResponse.statusCode = WriteFileDataStatusCode_WFDSC_SUCCESS;
  return true;
}


void doPrintDirPreamble(PrintDirContentsCommand * cmd, std::function<void(uint8_t*, uint32_t)> txFn) {
  File root = LittleFS.open(cmd->dirPath);

  if (root == NULL) {
    logError("doPrintDirPreamble - failed to open directory");
    logError("FS ROOT IS NULL");
    return;
  }

  File file = root.openNextFile();

  int fileCount = 0;

  while (file) {
    fileCount++;
    file = root.openNextFile();
  }

  root.close();
  pbSendLine("DIR NAME: ", cmd->dirPath, txFn);
  pbSendIntMessageLine("DIR SIZE: ", fileCount, txFn);
}


void doPrintDirFiles(PrintDirContentsCommand * cmd, std::function<void(uint8_t*, uint32_t)> txFn) {
  File root = LittleFS.open(cmd->dirPath);

  if (root == NULL) {
    logError("doPrintDirFiles - failed to open directory");
    logError("FS ROOT IS NULL");
    return;
  }

  File file = root.openNextFile();

  while (file) {
    pbSendMessage(file.name(), txFn);
    file = root.openNextFile();
  }

  root.close();
}


void QromaFsCommandProcessor::handlePrintDirContents(PrintDirContentsCommand * cmd, std::function<void(uint8_t*, uint32_t)> txFn) {
  logInfo("PRINT DIR CONTENTS");

  doPrintDirPreamble(cmd, txFn);
  doPrintDirFiles(cmd, txFn);
}


bool QromaFsCommandProcessor::handleGetFileContents(GetFileContentsCommand * cmd, FileSystemResponse * fsResponse) {

  fsResponse->which_response = FileSystemResponse_getFileContentsResponse_tag;
  
  File file = LittleFS.open(cmd->filePath);

  if (file == NULL) {
    logError("doPrintFilePreamble - failed to open file");
    logError(cmd->filePath);
    logError("FILE IS NULL");
    fsResponse->response.getFileContentsResponse.statusCode = GetFileStatusCode_GFSC_ERR_OPEN_FILE;
    return true;
  }

  if (file.isDirectory()) {
    logError("doPrintFilePreamble - not a file; it's a directory");
    logError(cmd->filePath);
    logError("GOT DIRECTORY");
    fsResponse->response.getFileContentsResponse.statusCode = GetFileStatusCode_GFSC_ERR_INVALID_FILE_PATH;
    return true;
  }

  int fileSize = file.size();
  uint32_t checkSum = getFileChecksum(cmd->filePath);

  fsResponse->response.getFileContentsResponse.has_fileData = true;
  fsResponse->response.getFileContentsResponse.fileData.filesize = fileSize;
  fsResponse->response.getFileContentsResponse.fileData.checksum = checkSum;
  strncpy(fsResponse->response.getFileContentsResponse.fileData.filename, cmd->filePath, 
    sizeof(fsResponse->response.getFileContentsResponse.fileData.filename));

  fsResponse->response.getFileContentsResponse.fileBytes.size = fileSize;
  file.readBytes((char*)fsResponse->response.getFileContentsResponse.fileBytes.bytes, fileSize);

  fsResponse->response.getFileContentsResponse.statusCode = GetFileStatusCode_GFSC_FILE_EXISTS;

  file.close();

  return true;
}
