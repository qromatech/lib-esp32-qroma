#include "QromaAppConfig.h"


void initConfigWithDefaultValues(QromaAppConfig * config) {
  // config->serialIoConfig.baudRate = 115200;
  // config->serialIoConfig.rxBufferSize = 1000;

  config->loggerConfig.logLevel = Qroma_LogLevel_LogLevel_Error;
}


void handleInvalidQromaAppConfig(QromaAppConfig * config) {

}
