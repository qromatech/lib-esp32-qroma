#include "QromaAppConfig.h"

bool validateQromaAppConfig(QromaAppConfig * config) {
  return true;
}

void handleInvalidQromaAppConfig(QromaAppConfig * config) {

}


void initQromaAppConfigWithDefaults(
  QromaAppConfig * config,
  QromaCommMemBuffer * serialCommMemBuffer,
  QromaAppConfigFn qromaAppConfigFn
  ) 
{
  config->serialIoConfig.qromaCommMemBuffer = serialCommMemBuffer;
  config->serialIoConfig.baudRate = 115200;

  config->loggerConfig.logLevel = Qroma_LogLevel_LogLevel_Error;

  bool isValidQromaAppConfig = validateQromaAppConfig(config);
  if (!isValidQromaAppConfig) {
    handleInvalidQromaAppConfig(config);
  }
}