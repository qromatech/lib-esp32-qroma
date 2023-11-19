#include "logger.h"
#include <HardwareSerial.h>


Qroma_DebugCommMode _commMode = Qroma_DebugCommMode_DebugCommMode_SerialOnly;
Qroma_LogLevel _logLevel = Qroma_LogLevel_LogLevel_Info;


void setDebugCommMode(Qroma_DebugCommMode mode) {
  _commMode = mode;
}


void setLogLevel(Qroma_LogLevel level) {
  _logLevel = level;
}


Qroma_LogLevel getLogLevel() {
  return _logLevel;
}


void initLogger() {
  Serial.begin(115200);
  Serial.setRxBufferSize(10000);
}


void logInfo(const char * msg) {
  debugComm(msg, _commMode, Qroma_LogLevel_LogLevel_Info);
}

void logInfo(int value) {
  debugCommInt(value, _commMode, Qroma_LogLevel_LogLevel_Info);
}

void logInfoIntWithDescription(const char * msg, int value) {
  debugCommIntWithDescription(msg, value, _commMode, Qroma_LogLevel_LogLevel_Info);
}

void logError(const char * msg) {
  debugComm(msg, _commMode, Qroma_LogLevel_LogLevel_Error);
}

void logError(int value) {
  debugCommInt(value, _commMode, Qroma_LogLevel_LogLevel_Error);
}

bool shouldBeLogged(Qroma_LogLevel logLevel) {
  return logLevel >= _logLevel;
}



void debugComm(const char * message, Qroma_DebugCommMode commMode, Qroma_LogLevel logLevel) {
  if (commMode == Qroma_DebugCommMode_DebugCommMode_None ||
      !shouldBeLogged(logLevel))
  {
    return;
  }

  if (commMode == Qroma_DebugCommMode_DebugCommMode_BluetoothOnly ||
      commMode == Qroma_DebugCommMode_DebugCommMode_SerialAndBluetooth)
  {
    // if (gQromaBluetoothCommInitComplete) {
    //   sendQromaLogMessageBt(message);
    // }
  }

  if (commMode == Qroma_DebugCommMode_DebugCommMode_SerialOnly ||
      commMode == Qroma_DebugCommMode_DebugCommMode_SerialAndBluetooth)
  {
    Serial.println(message);
  }
}

void debugCommInt(int value, Qroma_DebugCommMode commMode, Qroma_LogLevel logLevel) {
  if (commMode == Qroma_DebugCommMode_DebugCommMode_None ||
      !shouldBeLogged(logLevel))
  {
    return;
  }

  if (commMode == Qroma_DebugCommMode_DebugCommMode_BluetoothOnly ||
      commMode == Qroma_DebugCommMode_DebugCommMode_SerialAndBluetooth)
  {
    // sendQromaLogMessageBt(value);
  }

  if (commMode == Qroma_DebugCommMode_DebugCommMode_SerialOnly ||
      commMode == Qroma_DebugCommMode_DebugCommMode_SerialAndBluetooth)
  {
    Serial.println(value);
  }
}

void debugCommIntWithDescription(const char * intDescription, int value, Qroma_DebugCommMode commMode, Qroma_LogLevel logLevel) {
  if (commMode == Qroma_DebugCommMode_DebugCommMode_None ||
      !shouldBeLogged(logLevel)) {
    return;
  }

  if (commMode == Qroma_DebugCommMode_DebugCommMode_BluetoothOnly ||
      commMode == Qroma_DebugCommMode_DebugCommMode_SerialAndBluetooth)
  {
    // sendQromaLogMessageBt(intDescription);
    // appendQromaLogMessageBt(value);
  }

  if (commMode == Qroma_DebugCommMode_DebugCommMode_SerialOnly ||
      commMode == Qroma_DebugCommMode_DebugCommMode_SerialAndBluetooth)
  {
    Serial.print(intDescription);
    Serial.println(value);
  }
}
