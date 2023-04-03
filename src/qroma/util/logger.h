#ifndef QROMA_LOGGER_H
#define QROMA_LOGGER_H

#include <qroma-lib-proto/qroma-types.pb.h>


class QromaLoggerConfig {
  public:
    Qroma_LogLevel logLevel;
};


void initLogger();

void logInfo(const char * msg);
void logInfo(int value);
void logInfoIntWithDescription(const char * msg, int value);

void logError(const char * msg);
void logError(int value);

void debugComm(const char * message, Qroma_DebugCommMode commMode, Qroma_LogLevel logLevel);
void debugCommInt(int value, Qroma_DebugCommMode commMode, Qroma_LogLevel logLevel);
void debugCommIntWithDescription(const char * intDescription, int value, Qroma_DebugCommMode commMode, Qroma_LogLevel logLevel);


void setDebugCommMode(Qroma_DebugCommMode mode);
void setLogLevel(Qroma_LogLevel level);


extern Qroma_DebugCommMode _commMode;
extern Qroma_LogLevel _logLevel;

#endif
