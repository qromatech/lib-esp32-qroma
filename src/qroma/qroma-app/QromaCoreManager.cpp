#include "QromaCoreManager.h"
#include "../qroma-comm/io/SerialCommandProcessingTask.h"
#include <qroma/util/heartbeat.h>


void QromaCoreManager::initQromaCoreConfigDefaults(QromaCoreConfig * config) {
  config->has_serialIoConfig = true;
  config->serialIoConfig = {
    .baudRate = 115200,
    .rxBufferSize = 1000,
    .txBufferSize = 1000,
  };

  config->has_serialProcessingConfig = true;
  config->serialProcessingConfig = {
    .msDelayInProcessingLoop = 10,
  };

  config->has_loggingConfig = true;
  config->loggingConfig = {
    .logLevel = Qroma_LogLevel_LogLevel_Info,
  };

  config->has_managementConfig = true;
  config->managementConfig = {
    .projectLoopDelayInMs = 100,
    .has_heartbeatConfiguration = true,
    .heartbeatConfiguration = {
      .heartbeatType = HeartbeatType_HeartbeatType_Interval,
      .heartbeatIntervalInMs = 1000,
    },
  };
}


void QromaCoreManager::applyQromaCoreConfig(QromaCoreConfig * config) {
  if (config->has_serialIoConfig) {
    logError("UPDATING SERIAL IO CONFIG IS UNSUPPORTED");
  }

  if (config->has_serialProcessingConfig) {
    setMsDelayInProcessingLoop(config->serialProcessingConfig.msDelayInProcessingLoop);
  }

  if (config->has_loggingConfig) {
    setLogLevel(config->loggingConfig.logLevel);
  }

  if (config->has_managementConfig) {
    setProjectLoopDelayInMs(config->managementConfig.projectLoopDelayInMs);
    if (config->managementConfig.has_heartbeatConfiguration) {
      setHeartbeatIntervalInMs(config->managementConfig.heartbeatConfiguration.heartbeatIntervalInMs);
      setHeartbeatType(config->managementConfig.heartbeatConfiguration.heartbeatType);
    }
  }
}


void QromaCoreManager::populateQromaCoreConfig(QromaCoreConfig * dstConfig, QromaCoreConfig * srcConfig) {
  memcpy(dstConfig, srcConfig, sizeof(QromaCoreConfig));
}
