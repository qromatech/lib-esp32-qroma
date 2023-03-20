#ifndef QROMA_APP_SERIAL_IO_CONFIG_H
#define QROMA_APP_SERIAL_IO_CONFIG_H

#include <functional>

#include "../qroma-comm/io/QromaCommSerialIoConfig.h"
#include "../util/logger.h"


class QromaAppConfig {
  public:
    QromaCommSerialIoConfig serialIoConfig;
    QromaLoggerConfig loggerConfig;

  
  // buffers
  // processors
  // comm speeds/configs
  // wifi passwords
  // 
};


typedef std::function<void(QromaAppConfig * config)> QromaAppConfigFn;

void initQromaAppConfigWithDefaults(
  QromaAppConfig * config, 
  QromaCommMemBuffer * serialCommMemBuffer, 
  QromaAppConfigFn qromaAppConfigFn
);

#endif
