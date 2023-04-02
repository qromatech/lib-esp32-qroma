#ifndef QROMA_APP_SERIAL_IO_CONFIG_H
#define QROMA_APP_SERIAL_IO_CONFIG_H

#include <functional>

#include "../qroma-comm/io/QromaCommSerialIoConfig.h"
#include "../qroma-comm/pb-commands/PbCommandsRegistry.h"
#include "../util/logger.h"


class QromaAppConfig {
  public:
    QromaLoggerConfig loggerConfig;

    // PbCommandsRegistry pbCommandsRegistry;

    // QromaCommSerialIoConfig serialIoConfig;

    // bool validate();

  
  // buffers
  // processors
  // comm speeds/configs
  // wifi passwords
  // 
};


// QromaAppConfig * getQromaAppConfig();

// void initConfigWithDefaultValues(QromaAppConfig * config);
// void handleInvalidQromaAppConfig(QromaAppConfig * config);

#endif
