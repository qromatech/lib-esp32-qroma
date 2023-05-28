// #include "SPIFFS.h"
#include "FS.h"
#include "LittleFS.h"
#include "fs_comm_handlers.h"
#include <pb_encode.h>
#include <pb_decode.h>
#include "../../proto-nanopb/qroma-comm.pb.h"
#include "../util/fs.h"
#include "../util/logger.h"
#include "pbBufferCommProcessor.h"
#include "chunkedPrintBuffer.h"


void handleFileSystemCommand(FileSystemCommand * fsCommand, PbBufferCommProcessor * comm) {

  logInfoIntWithDescription("handleFileSystemCommand - ", fsCommand->which_command);

  switch (fsCommand->which_command)
  {
    case FileSystemCommand_rmFileCommand_tag:
      handleRmFileCommand(&(fsCommand->command.rmFileCommand));
      break;

    case FileSystemCommand_resetFilesystemCommand_tag:
      handleResetFilesystemCommand(&(fsCommand->command.resetFilesystemCommand));
      break;

    case FileSystemCommand_storeUpcomingFileDataCommand_tag:
      logInfo("STORE UPCOMING FILE");
      handleStoreUpcomingFileCommand(&(fsCommand->command.storeUpcomingFileDataCommand), comm);
      break;

    case FileSystemCommand_reportFileDataCommand_tag:
      handleReportFileDataCommand(&(fsCommand->command.reportFileDataCommand), comm);
      break;

    case FileSystemCommand_listDirContentsCommand_tag:
      handleListDirContents(&(fsCommand->command.listDirContentsCommand), comm);
      break;

    case FileSystemCommand_printDirContentsCommand_tag:
      handlePrintDirContents(&(fsCommand->command.printDirContentsCommand), comm);
      break;

    case FileSystemCommand_printFileContentsCommand_tag:
      handlePrintFileContents(&(fsCommand->command.printFileContentsCommand), comm);
      break;

    default:
      break;
  }
}


void handleRmFileCommand(RmFileCommand * cmd) {
  SPIFFS.remove(cmd->filePath);
  logInfo("HANDLED RM FILE");
  logInfo(cmd->filePath);
}


void handleResetFilesystemCommand(ResetFilesystemCommand * cmd) {
  resetFilesystem();
}

void handleStoreUpcomingFileCommand(StoreUpcomingFileDataCommand * cmd, PbBufferCommProcessor * comm) {
  logInfo("HANDLE STORE FILE");
  comm->readSerialToFile(5000, &(cmd->fileData));
}


void handleReportFileDataCommand(ReportFileDataCommand * cmd, PbBufferCommProcessor * comm) {
  logInfo("REPORT FILE DATA: ");
  logInfo(cmd->filename);

  bool isFile = true;
  File file = SPIFFS.open(cmd->filename);
  if (!file || file.isDirectory()){
    isFile = false;
    logInfo("− failed to open file for reading");
  }

  int fileSize = file.size();
  uint32_t checkSum = getFileChecksum(cmd->filename);

  QromaCommResponse response;
  response.which_response = QromaCommResponse_fsResponse_tag;
  response.response.fsResponse.which_response = FileSystemResponse_reportFileDataResponse_tag;
  response.response.fsResponse.response.reportFileDataResponse.fileExists = isFile;
  response.response.fsResponse.response.reportFileDataResponse.fileData.filesize = fileSize;
  response.response.fsResponse.response.reportFileDataResponse.fileData.checksum = checkSum;
  strncpy(response.response.fsResponse.response.reportFileDataResponse.fileData.filename, cmd->filename, 
    sizeof(response.response.fsResponse.response.reportFileDataResponse.fileData.filename));

  uint8_t buffer[2000];
  memset(buffer, 0, sizeof buffer);
  pb_ostream_t stream = pb_ostream_from_buffer(buffer, sizeof(buffer));
  bool status = pb_encode(&stream, QromaCommResponse_fields, &response);

  if (!status) {
    logInfo("UNABLE TO ENCODE ReportFileDataCommand RESPONSE");
  } else {
    logInfoIntWithDescription("REPORT FILE: ", stream.bytes_written);
  }

  comm->pbSendQromacommResponse(buffer, (uint32_t)stream.bytes_written);
}


bool listDirContents_callback(pb_ostream_t *stream, const pb_field_t *field, void * const *arg)
{
  char * dirName = (char*)*arg;
  File root = SPIFFS.open(dirName, FILE_READ);

  if (root == NULL) {
    logInfo("FS ROOT IS NULL");
  } else {
    logInfo("SPIFFS OPEN");
  }

  File file = root.openNextFile();

  while (file) {
    logInfoIntWithDescription("F: ", strlen(file.name()));

    DirItem dirItem = DirItem_init_zero;
    strncpy(dirItem.name, file.name(), sizeof(dirItem.name));
    dirItem.name[sizeof(dirItem.name) - 1] = '\0';

    logInfo("D: ");

    if (file.isDirectory()) {
      dirItem.dirItemType = DirItemType_DIT_DIR;
      dirItem.filesize = 0;
    } else {
      dirItem.dirItemType = DirItemType_DIT_FILE;
      dirItem.filesize = file.size();
    }
    
    /* This encodes the header for the field, based on the constant info
      * from pb_field_t. */
    if (!pb_encode_tag_for_field(stream, field)) {
      return false;
    }
    
    /* This encodes the data for the field, based on our DirItem structure. */
    if (!pb_encode_submessage(stream, DirItem_fields, &dirItem)) {
      return false;
    }

    file.close();

    file = root.openNextFile();
  }

  logInfo("ROOT C");
  root.close();
  logInfo("DONE DIR CB");

  return true;
}


void doPrintDirPreamble(PrintDirContentsCommand * cmd, PbBufferCommProcessor * comm) {
  File root = SPIFFS.open(cmd->dirPath);

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
  comm->pbSendLine("DIR NAME: ", cmd->dirPath);
  comm->pbSendIntMessageLine("DIR SIZE: ", fileCount);
}


void doPrintDirFiles(PrintDirContentsCommand * cmd, PbBufferCommProcessor * comm) {
  File root = SPIFFS.open(cmd->dirPath);

  if (root == NULL) {
    logError("doPrintDirFiles - failed to open directory");
    logError("FS ROOT IS NULL");
    return;
  }

  File file = root.openNextFile();

  while (file) {
    comm->pbSendMessage(file.name());
    file = root.openNextFile();
  }

  root.close();
}


void handlePrintDirContents(PrintDirContentsCommand * cmd, PbBufferCommProcessor * comm) {
  comm->setPbBuildingMessage(true);

  doPrintDirPreamble(cmd, comm);
  doPrintDirFiles(cmd, comm);

  comm->setPbBuildingMessage(false);
}


void doPrintFilePreamble(PrintFileContentsCommand * cmd, PbBufferCommProcessor * comm) {
  File file = SPIFFS.open(cmd->filePath);

  if (file == NULL) {
    logError("doPrintFilePreamble - failed to open file");
    logError(cmd->filePath);
    logError("FILE IS NULL");
    return;
  }

  if (file.isDirectory()) {
    logError("doPrintFilePreamble - not a file; it's a directory");
    logError(cmd->filePath);
    logError("GOT DIRECTORY");
    return;
  }

  int fileSize = file.size();

  file.close();

  comm->pbSendLine("FILE PATH: ", cmd->filePath);
  comm->pbSendIntMessageLine("FILE SIZE: ", fileSize);
}


void doPrintFileContents(PrintFileContentsCommand * cmd, PbBufferCommProcessor * comm) {
  File file = SPIFFS.open(cmd->filePath);

  if (file == NULL) {
    logError("doPrintFileContents - failed to open file");
    logError(cmd->filePath);
    logError("FILE IS NULL");
    return;
  }

  const int FILE_BUFFER_SIZE = 250;
  char fileBuffer[FILE_BUFFER_SIZE];
  memset(fileBuffer, 0, sizeof fileBuffer);

  int fileSize = file.available();
  int bytesToPrint = fileSize;
  logInfoIntWithDescription("!BYTES REMAINING: ", bytesToPrint);

  while (bytesToPrint > 0) {
    int byteCount = file.readBytes(fileBuffer, sizeof fileBuffer);
    logInfoIntWithDescription("SENDING BYTES: ", byteCount);
    comm->pbSendBytes((uint8_t*)fileBuffer, byteCount);
    bytesToPrint -= byteCount;
    logInfoIntWithDescription("BYTES REMAINING: ", bytesToPrint);
  }

  file.close();
}


void handlePrintFileContents(PrintFileContentsCommand * cmd, PbBufferCommProcessor * comm) {
  comm->setPbBuildingMessage(true);

  doPrintFilePreamble(cmd, comm);
  doPrintFileContents(cmd, comm);

  comm->setPbBuildingMessage(false);
}

void handleListDirContents(ListDirContentsCommand * cmd, PbBufferCommProcessor * comm) {
  logInfo("LISTING DIR CONTENTS >> ");
  logInfo(cmd->dirPath);

  QromaCommResponse response = QromaCommResponse_init_zero;
  response.which_response = QromaCommResponse_fsResponse_tag;
  response.response.fsResponse.which_response = FileSystemResponse_listDirContentsResponse_tag;
  strncpy(response.response.fsResponse.response.listDirContentsResponse.dirPath, cmd->dirPath, 
    sizeof(response.response.fsResponse.response.listDirContentsResponse.dirPath));
  response.response.fsResponse.response.listDirContentsResponse.dirItems.funcs.encode = &listDirContents_callback;
  response.response.fsResponse.response.listDirContentsResponse.dirItems.arg = &(cmd->dirPath);

  logInfo("PRE DIR ENCODE");
  uint8_t buffer[10000];
  memset(buffer, 0, sizeof buffer);
  pb_ostream_t stream = pb_ostream_from_buffer(buffer, sizeof(buffer));

  logInfo("MID DIR ENCODE");

  bool status = pb_encode(&stream, QromaCommResponse_fields, &response);

  logInfo("POST DIR ENCODE");

  if (!status) {
    logError("ERR LISTING DIR CONTENTS");
  } else {
    logInfo("DONE LISTING DIR CONTENTS");
  }

  comm->pbSendQromacommResponse(buffer, (uint32_t)stream.bytes_written);
}
