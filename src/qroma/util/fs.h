#ifndef QROMA_FILESYSTEM_H
#define QROMA_FILESYSTEM_H

#include <pb.h>

void initFileSystem();
bool resetFilesystem();

bool doesFileExist(const char * fname);
uint32_t getFileChecksum(const char * fname);

uint32_t getFileCountForDirectory(const char * dirName);

#endif