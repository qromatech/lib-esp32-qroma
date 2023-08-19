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


//  uint32_t QromaFsCommandProcessor::processBytes(const uint8_t * bytes, uint32_t byteCount) {

//  }
 

// return true if caller should return the populated QromaCommResponse
bool QromaFsCommandProcessor::handleFileSystemCommand(FileSystemCommand * fsCommand,
  QromaCommResponse * qromaCommResponse,
  std::function<void(uint8_t*, uint32_t)> txFn,
  IQromaFsCommandProcessorListener * fsListener)
{
  logInfoIntWithDescription("handleFileSystemCommand - ", fsCommand->which_command);
  
  switch (fsCommand->which_command)
  {
    case FileSystemCommand_rmFileCommand_tag:
      handleRmFileCommand(&(fsCommand->command.rmFileCommand));
      break;

    case FileSystemCommand_resetFilesystemCommand_tag:
      handleResetFilesystemCommand(&(fsCommand->command.resetFilesystemCommand));
      break;

    // case FileSystemCommand_storeUpcomingFileDataCommand_tag:
    //   logInfo("STORE UPCOMING FILE");
    //   handleStoreUpcomingFileCommand(&(fsCommand->command.storeUpcomingFileDataCommand), fsListener);
    //   break;

    case FileSystemCommand_writeFileDataCommand_tag:
      logInfo("WRITE FILE DATA");
      return handleWriteFileDataCommand(&(fsCommand->command.writeFileDataCommand), qromaCommResponse);

    case FileSystemCommand_reportFileDataCommand_tag:
      return handleReportFileDataCommand(&(fsCommand->command.reportFileDataCommand), qromaCommResponse);
      break;

    // case FileSystemCommand_listDirContentsCommand_tag:
    //   handleListDirContents(&(fsCommand->command.listDirContentsCommand));
    //   break;

    // case FileSystemCommand_printDirContentsCommand_tag:
    //   handlePrintDirContents(&(fsCommand->command.printDirContentsCommand), txFn);
    //   break;

    case FileSystemCommand_getFileContentsCommand_tag:
      return handleGetFileContents(&(fsCommand->command.getFileContentsCommand), qromaCommResponse);
      break;

    case FileSystemCommand_listDirContentsCommand_tag:
      return handleListDirContentsCommand(&(fsCommand->command.listDirContentsCommand), qromaCommResponse);
      break;
    case FileSystemCommand_mkDirCommand_tag:
      return handleMkDirCommand(&(fsCommand->command.mkDirCommand), qromaCommResponse);
      break;
    case FileSystemCommand_rmDirCommand_tag:
      return handleRmDirCommand(&(fsCommand->command.rmDirCommand), qromaCommResponse);
      break;

    default:
      break;
  }

  return false;
}


bool QromaFsCommandProcessor::handleListDirContentsCommand(ListDirContentsCommand * cmd, QromaCommResponse * response) {
  response->which_response = QromaCommResponse_fsResponse_tag;
  response->response.fsResponse.which_response = FileSystemResponse_listDirContentsResponse_tag;
  response->response.fsResponse.response.listDirContentsResponse.success = false;

  File root = LittleFS.open(cmd->dirPath);
  if (root == NULL) {
    logError("handleListDirContentsCommand - failed to open directory");
    logError("FS ROOT IS NULL");
    return true;
  }

  File file = root.openNextFile();

  int fileIndex = 0;

  int maxDirItemsAllowed = sizeof(response->response.fsResponse.response.listDirContentsResponse.dirItems) /
    sizeof(response->response.fsResponse.response.listDirContentsResponse.dirItems[0]);

  response->response.fsResponse.response.listDirContentsResponse.dirItems_count = 0;
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
        strncpy(response->response.fsResponse.response.listDirContentsResponse.dirItems[fileIndex].name, file.name(),
          sizeof(response->response.fsResponse.response.listDirContentsResponse.dirItems[0].name));
        if (file.isDirectory()) {
          response->response.fsResponse.response.listDirContentsResponse.dirItems[fileIndex].dirItemType = DirItemType_DIT_DIR;
        } else {
          response->response.fsResponse.response.listDirContentsResponse.dirItems[fileIndex].dirItemType = DirItemType_DIT_FILE;
        }
        response->response.fsResponse.response.listDirContentsResponse.dirItems_count++;
      fileIndex++;
      }

    file = root.openNextFile();
  }

  response->response.fsResponse.response.listDirContentsResponse.success = true;
  strncpy(response->response.fsResponse.response.listDirContentsResponse.dirPath,
          cmd->dirPath,
          sizeof(response->response.fsResponse.response.listDirContentsResponse.dirPath));

  return true;
}

// void doPrintDirPreamble(PrintDirContentsCommand * cmd, std::function<void(uint8_t*, uint32_t)> txFn) {
//   File root = LittleFS.open(cmd->dirPath);

//   if (root == NULL) {
//     logError("doPrintDirPreamble - failed to open directory");
//     logError("FS ROOT IS NULL");
//     return;
//   }

//   File file = root.openNextFile();

//   int fileCount = 0;

//   while (file) {
//     fileCount++;
//     file = root.openNextFile();
//   }

//   root.close();
//   pbSendLine("DIR NAME: ", cmd->dirPath, txFn);
//   pbSendIntMessageLine("DIR SIZE: ", fileCount, txFn);
// }


// void doPrintDirFiles(PrintDirContentsCommand * cmd, std::function<void(uint8_t*, uint32_t)> txFn) {
//   File root = LittleFS.open(cmd->dirPath);

//   if (root == NULL) {
//     logError("doPrintDirFiles - failed to open directory");
//     logError("FS ROOT IS NULL");
//     return;
//   }

//   File file = root.openNextFile();

//   while (file) {
//     pbSendMessage(file.name(), txFn);
//     file = root.openNextFile();
//   }

//   root.close();
// }



bool QromaFsCommandProcessor::handleMkDirCommand(MkDirCommand * cmd, QromaCommResponse * response) {
  bool success = LittleFS.mkdir(cmd->dirPath);

  response->which_response = QromaCommResponse_fsResponse_tag;
  response->response.fsResponse.which_response = FileSystemResponse_mkDirResponse_tag;
  response->response.fsResponse.response.mkDirResponse.success = success;
  response->response.fsResponse.response.mkDirResponse.has_mkDirCommand = true;
  strncpy(response->response.fsResponse.response.mkDirResponse.mkDirCommand.dirPath, cmd->dirPath,
    sizeof(response->response.fsResponse.response.mkDirResponse.mkDirCommand.dirPath));

  logInfo("handleMkDirCommand");
  logInfo(cmd->dirPath);
  logInfo(response->response.fsResponse.response.mkDirResponse.mkDirCommand.dirPath);

  return true;
}


bool QromaFsCommandProcessor::handleRmDirCommand(RmDirCommand * cmd, QromaCommResponse * response) {
  bool success = LittleFS.rmdir(cmd->dirPath);

  response->which_response = QromaCommResponse_fsResponse_tag;
  response->response.fsResponse.which_response = FileSystemResponse_rmDirResponse_tag;
  response->response.fsResponse.response.rmDirResponse.success = success;
  response->response.fsResponse.response.rmDirResponse.has_rmDirCommand = true;
  strncpy(response->response.fsResponse.response.rmDirResponse.rmDirCommand.dirPath, cmd->dirPath,
    sizeof(response->response.fsResponse.response.rmDirResponse.rmDirCommand.dirPath));

  logInfo("handleRmDirCommand");
  logInfo(cmd->dirPath);
  logInfo(response->response.fsResponse.response.rmDirResponse.rmDirCommand.dirPath);

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

// void QromaFsCommandProcessor::handleStoreUpcomingFileCommand(StoreUpcomingFileDataCommand * cmd, IQromaFsCommandProcessorListener * fsListener) {
//   logInfo("HANDLE STORE FILE");
//   fsListener->startFileReadingMode(5000, &(cmd->fileData));
// }


bool QromaFsCommandProcessor::handleWriteFileDataCommand(WriteFileDataCommand * cmd, QromaCommResponse * response) {

  response->which_response = QromaCommResponse_fsResponse_tag;
  response->response.fsResponse.which_response = FileSystemResponse_writeFileDataResponse_tag;


  File file = LittleFS.open(cmd->fileData.filename, FILE_WRITE);
  if (!file) {
    logInfo("NO FILE OPENED");
    logInfo(cmd->fileData.filename);
    response->response.fsResponse.response.writeFileDataResponse.statusCode = WriteFileDataStatusCode_WFDSC_ERR_OPEN_FILE;
    return true;
  }

  bool writeSuccess = file.write(cmd->fileBytes.bytes, cmd->fileBytes.size);
  file.close();

  uint32_t crc = getFileChecksum(cmd->fileData.filename);

  if (crc != cmd->fileData.checksum) {
    response->response.fsResponse.response.writeFileDataResponse.statusCode = WriteFileDataStatusCode_WFDSC_ERR_CRC_MISMATCH;
    return true;
  }

  response->response.fsResponse.response.writeFileDataResponse.statusCode = WriteFileDataStatusCode_WFDSC_SUCCESS;
  return true;



// bool QromaCommFileReader::finalizeReadToFileContents() {
//   const uint8_t * commBuffer = cbGetCommBuffer();

//   logInfo("ADD TO FILE");
//   File file = LittleFS.open(_readToFileName, FILE_WRITE);
//   if (!file) {
//     logInfo("NO FILE OPENED");
//     logInfo(_readToFileName);
//     sendReadSerialToFileResponse(false, 0);
//     return true;
//   }

//   bool writeSuccess = file.write(commBuffer, _readToBufferSize);
//   file.close();

//   logInfoIntWithDescription("FILE WRITE COMPLETE: ", writeSuccess);

//   if (writeSuccess) {
//     logInfo("WROTE FILE - COMM BUFFER");
//     logInfo(_readToFileName);
//   } else {
//     logInfo("ERR WRITE FILE");
//     logInfo(_readToFileName);

//     sendReadSerialToFileResponse(false, 0);
//     return true;
//   }

//   uint32_t crc = getFileChecksum(_readToFileName);

//   sendReadSerialToFileResponse(writeSuccess, crc);
  
//   cbRemoveFirstNFromBuffer(_readToBufferSize);
//   setCommReadingMode(CommReadingMode_PB_COMMANDS);  

//   return true;
// }

}


bool QromaFsCommandProcessor::handleReportFileDataCommand(ReportFileDataCommand * cmd, QromaCommResponse * response) {
  logInfo("REPORT FILE DATA: ");
  logInfo(cmd->filename);

  bool isFile = true;
  File file = LittleFS.open(cmd->filename);
  if (!file || file.isDirectory()){
    isFile = false;
    logInfo("− failed to open file for reading");
  }

  int fileSize = file.size();
  uint32_t checkSum = getFileChecksum(cmd->filename);

  logInfo("FILE CHECKED");
  response->which_response = QromaCommResponse_fsResponse_tag;
  response->response.fsResponse.which_response = FileSystemResponse_reportFileDataResponse_tag;
  response->response.fsResponse.response.reportFileDataResponse.fileExists = isFile;
  response->response.fsResponse.response.reportFileDataResponse.has_fileData = true;
  response->response.fsResponse.response.reportFileDataResponse.fileData.filesize = fileSize;
  response->response.fsResponse.response.reportFileDataResponse.fileData.checksum = checkSum;
  strncpy(response->response.fsResponse.response.reportFileDataResponse.fileData.filename, cmd->filename, 
    sizeof(response->response.fsResponse.response.reportFileDataResponse.fileData.filename));

  logInfo("RESPONSE DONE");

  return true;
}


// bool listDirContents_callback(pb_ostream_t *stream, const pb_field_t *field, void * const *arg)
// {
//   char * dirName = (char*)*arg;
//   File root = SPIFFS.open(dirName, FILE_READ);

//   if (root == NULL) {
//     logInfo("FS ROOT IS NULL");
//   } else {
//     logInfo("SPIFFS OPEN");
//   }

//   File file = root.openNextFile();

//   while (file) {
//     logInfoIntWithDescription("F: ", strlen(file.name()));

//     DirItem dirItem = DirItem_init_zero;
//     strncpy(dirItem.name, file.name(), sizeof(dirItem.name));
//     dirItem.name[sizeof(dirItem.name) - 1] = '\0';

//     logInfo("D: ");

//     if (file.isDirectory()) {
//       dirItem.dirItemType = DirItemType_DIT_DIR;
//       dirItem.filesize = 0;
//     } else {
//       dirItem.dirItemType = DirItemType_DIT_FILE;
//       dirItem.filesize = file.size();
//     }
    
//     /* This encodes the header for the field, based on the constant info
//       * from pb_field_t. */
//     if (!pb_encode_tag_for_field(stream, field)) {
//       return false;
//     }
    
//     /* This encodes the data for the field, based on our DirItem structure. */
//     if (!pb_encode_submessage(stream, DirItem_fields, &dirItem)) {
//       return false;
//     }

//     file.close();

//     file = root.openNextFile();
//   }

//   logInfo("ROOT C");
//   root.close();
//   logInfo("DONE DIR CB");

//   return true;
// }


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
  // comm->setPbBuildingMessage(true);
  logInfo("PRINT DIR CONTENTS");

  doPrintDirPreamble(cmd, txFn);
  doPrintDirFiles(cmd, txFn);

  // comm->setPbBuildingMessage(false);
}


// void doPrintFilePreamble(PrintFileContentsCommand * cmd, std::function<void(uint8_t*, uint32_t)> txFn) {
//   File file = LittleFS.open(cmd->filePath);

//   if (file == NULL) {
//     logError("doPrintFilePreamble - failed to open file");
//     logError(cmd->filePath);
//     logError("FILE IS NULL");
//     return;
//   }

//   if (file.isDirectory()) {
//     logError("doPrintFilePreamble - not a file; it's a directory");
//     logError(cmd->filePath);
//     logError("GOT DIRECTORY");
//     return;
//   }

//   int fileSize = file.size();

//   file.close();

//   pbSendLine("FILE PATH: ", cmd->filePath, txFn);
//   pbSendIntMessageLine("FILE SIZE: ", fileSize, txFn);
// }


// void doPrintFileContents(PrintFileContentsCommand * cmd, std::function<void(uint8_t*, uint32_t)> txFn) {
//   File file = LittleFS.open(cmd->filePath);

//   if (file == NULL) {
//     logError("doPrintFileContents - failed to open file");
//     logError(cmd->filePath);
//     logError("FILE IS NULL");
//     return;
//   }

//   const int FILE_BUFFER_SIZE = 250;
//   char fileBuffer[FILE_BUFFER_SIZE];
//   memset(fileBuffer, 0, sizeof fileBuffer);

//   int fileSize = file.available();
//   int bytesToPrint = fileSize;
//   logInfoIntWithDescription("!BYTES REMAINING: ", bytesToPrint);

//   while (bytesToPrint > 0) {
//     int byteCount = file.readBytes(fileBuffer, sizeof fileBuffer);
//     logInfoIntWithDescription("SENDING BYTES: ", byteCount);
//     // comm->pbSendBytes((uint8_t*)fileBuffer, byteCount);
//     txFn((uint8_t*)fileBuffer, byteCount);
//     bytesToPrint -= byteCount;
//     logInfoIntWithDescription("BYTES REMAINING: ", bytesToPrint);
//   }

//   file.close();
// }


bool QromaFsCommandProcessor::handleGetFileContents(GetFileContentsCommand * cmd, QromaCommResponse * response) {
  response->which_response = QromaCommResponse_fsResponse_tag;
  response->response.fsResponse.which_response = FileSystemResponse_getFileContentsResponse_tag;
  
  File file = LittleFS.open(cmd->filePath);

  if (file == NULL) {
    logError("doPrintFilePreamble - failed to open file");
    logError(cmd->filePath);
    logError("FILE IS NULL");
    response->response.fsResponse.response.getFileContentsResponse.statusCode = GetFileStatusCode_GFSC_ERR_OPEN_FILE;
    return true;
  }

  if (file.isDirectory()) {
    logError("doPrintFilePreamble - not a file; it's a directory");
    logError(cmd->filePath);
    logError("GOT DIRECTORY");
    response->response.fsResponse.response.getFileContentsResponse.statusCode = GetFileStatusCode_GFSC_ERR_INVALID_FILE;
    return true;
  }

  int fileSize = file.size();
  uint32_t checkSum = getFileChecksum(cmd->filePath);

  response->response.fsResponse.response.getFileContentsResponse.has_fileData = true;
  response->response.fsResponse.response.getFileContentsResponse.fileData.filesize = fileSize;
  response->response.fsResponse.response.getFileContentsResponse.fileData.checksum = checkSum;
  strncpy(response->response.fsResponse.response.getFileContentsResponse.fileData.filename, cmd->filePath, 
    sizeof(response->response.fsResponse.response.getFileContentsResponse.fileData.filename));

  response->response.fsResponse.response.getFileContentsResponse.fileBytes.size = fileSize;
  file.readBytes((char*)response->response.fsResponse.response.getFileContentsResponse.fileBytes.bytes, fileSize);

  response->response.fsResponse.response.getFileContentsResponse.statusCode = GetFileStatusCode_GFSC_SUCCESS;

  file.close();

  return true;
}

// void handleListDirContents(ListDirContentsCommand * cmd) {
//   logInfo("LISTING DIR CONTENTS >> ");
//   logInfo(cmd->dirPath);

//   QromaCommResponse response = QromaCommResponse_init_zero;
//   response.which_response = QromaCommResponse_fsResponse_tag;
//   response.response.fsResponse.which_response = FileSystemResponse_listDirContentsResponse_tag;
//   strncpy(response.response.fsResponse.response.listDirContentsResponse.dirPath, cmd->dirPath, 
//     sizeof(response.response.fsResponse.response.listDirContentsResponse.dirPath));
//   response.response.fsResponse.response.listDirContentsResponse.dirItems.funcs.encode = &listDirContents_callback;
//   response.response.fsResponse.response.listDirContentsResponse.dirItems.arg = &(cmd->dirPath);

//   logInfo("PRE DIR ENCODE");
//   uint8_t buffer[10000];
//   memset(buffer, 0, sizeof buffer);
//   pb_ostream_t stream = pb_ostream_from_buffer(buffer, sizeof(buffer));

//   logInfo("MID DIR ENCODE");

//   bool status = pb_encode(&stream, QromaCommResponse_fields, &response);

//   logInfo("POST DIR ENCODE");

//   if (!status) {
//     logError("ERR LISTING DIR CONTENTS");
//   } else {
//     logInfo("DONE LISTING DIR CONTENTS");
//   }

//   comm->pbSendQromacommResponse(buffer, (uint32_t)stream.bytes_written);
// }

