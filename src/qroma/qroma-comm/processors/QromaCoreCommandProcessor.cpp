#include "../../lib_version.h"
#include "QromaCoreCommandProcessor.h"
#include "../io/SerialCommandProcessingTask.h"
#include <qroma/util/qroma-persist.h>
#include <qroma/util/heartbeat.h>


const char * QROMA_CORE_CONFIG_FILE_NAME = "/core-config.qroma";


bool hasQromaCoreConfigFile() {
  return doesFileExist(QROMA_CORE_CONFIG_FILE_NAME);
}


bool copyQromaCoreConfigFromFile(QromaCoreConfig * config) {
  bool success = loadPbFromPersistence(config, QROMA_CORE_CONFIG_FILE_NAME, QromaCoreConfig_fields);
  if (!success) {
    logError("ERROR LOADING QROMA CORE CONFIG");
    logError(QROMA_CORE_CONFIG_FILE_NAME);
  }

  return success;
}


// void copyQromaCoreConfig(QromaCoreConfig * config) {

//   QromaSerialCommApp * serialCommApp = getQromaSerialCommApp();
//   if (serialCommApp != NULL) {
//     config->has_serialIoConfig = true;
//     serialCommApp->copySerialIoConfig(&(config->serialIoConfig));
//   } else {
//     config->has_serialIoConfig = false;
//     config->serialIoConfig.baudRate = 0;
//     config->serialIoConfig.rxBufferSize = 0;
//     config->serialIoConfig.txBufferSize = 0;
//   }

//   config->has_loggingConfig = true;
//   config->loggingConfig.logLevel = getLogLevel();

//   config->has_projectConfiguration = true;
//   config->projectConfiguration.projectLoopDelayInMs = getProjectLoopDelayInMs();

//   config->projectConfiguration.has_heartbeatConfiguration = true;
//   config->projectConfiguration.heartbeatConfiguration.heartbeatType = getHeartbeatType();
//   config->projectConfiguration.heartbeatConfiguration.heartbeatIntervalInMs = getHeartbeatIntervalInMs();
// }


void populateQromaCoreConfig(QromaCoreConfig * config) {
  if (hasQromaCoreConfigFile()) {
    if (copyQromaCoreConfigFromFile(config)) {
      return;
    }
  }

  // copyQromaCoreConfig(config);
  getQromaApp()->populateQromaCoreConfig(config);
}


bool saveQromaCoreConfig() {
  logInfo("SAVING QROMA CORE CONFIG");
  QromaCoreConfig config;
  
  getQromaApp()->populateQromaCoreConfig(&config);

  // copyQromaCoreConfig(&config);

  bool saved = savePbToPersistence<QromaCoreConfig>(&config, QROMA_CORE_CONFIG_FILE_NAME, QromaCoreConfig_fields);

  if (!saved) {
    logError("ERROR SAVING QROMA CORE CONFIG");
    logError(QROMA_CORE_CONFIG_FILE_NAME);
  }

  logInfo("DONE SAVING QROMA CORE CONFIG");

  return saved;
}


void QromaCoreCommandProcessor::handleQromaCoreCommand(QromaCoreCommand * command, 
    QromaCommResponse * qromaCommResponse,
    IQromaCommResponseHandler * responseHandler,
    std::function<void(uint8_t*, uint32_t)> txFn)
{
  qromaCommResponse->which_response = QromaCommResponse_coreResponse_tag;
  QromaCoreResponse * coreResponse = &(qromaCommResponse->response.coreResponse);

  switch (command->which_command) {
    case QromaCoreCommand_getFirmwareDetails_tag:
      coreResponse->which_response = QromaCoreResponse_firmwareDetails_tag;
      populateGetFirmwareDetailsResponse(&(coreResponse->response.firmwareDetails));
      break;

    case QromaCoreCommand_restartQromaDevice_tag:
      QromaCommResponse ackResponse;
      ackResponse.which_response = QromaCommResponse_coreResponse_tag;
      ackResponse.response.coreResponse.which_response = QromaCoreResponse_restartAck_tag;
  
      responseHandler->sendQromaCommResponse(&ackResponse, txFn);
      delay(100);
      
      ESP.restart();
      break;

    case QromaCoreCommand_getQromaCoreConfig_tag:
      populateCoreConfigurationResponse(coreResponse);
      break;

    case QromaCoreCommand_setQromaCommSerialIoConfig_tag:
      if (command->command.setQromaCommSerialIoConfig.has_config) {
        handleSetQromaCommSerialIoConfig(&(command->command.setQromaCommSerialIoConfig.config));
      } else {
        logError("NO CONFIG VALUE PROVIDED FOR CORE COMMAND");
        logError(command->which_command);
      }
      populateCoreConfigurationResponse(coreResponse);
      break;

    case QromaCoreCommand_setQromaCommSerialProcessingConfig_tag:
      if (command->command.setQromaCommSerialProcessingConfig.has_config) {
        handleSetQromaCommSerialProcessingConfig(&(command->command.setQromaCommSerialProcessingConfig.config));
      } else {
        logError("NO CONFIG VALUE PROVIDED FOR CORE COMMAND");
        logError(command->which_command);
      }
      populateCoreConfigurationResponse(coreResponse);
      break;

    case QromaCoreCommand_setQromaCoreLoggingConfig_tag:
      if (command->command.setQromaCoreLoggingConfig.has_config) {
        handleSetQromaCoreLoggingConfig(&(command->command.setQromaCoreLoggingConfig.config));
      } else {
        logError("NO CONFIG VALUE PROVIDED FOR CORE COMMAND");
        logError(command->which_command);
      }
      populateCoreConfigurationResponse(coreResponse);
      break;

    case QromaCoreCommand_setQromaProjectConfiguration_tag:
      if (command->command.setQromaProjectConfiguration.has_config) {
        handleSetQromaProjectConfiguration(&(command->command.setQromaProjectConfiguration.config));
      } else {
        logError("NO CONFIG VALUE PROVIDED FOR CORE COMMAND");
        logError(command->which_command);
      }
      populateCoreConfigurationResponse(coreResponse);

    default:
      logError("UNRECOGNIZED CORE COMMAND");
      logError(command->which_command);
  }
}


void QromaCoreCommandProcessor::populateGetFirmwareDetailsResponse(FirmwareDetails * response) {
  strncpy(response->buildTime, __DATE__ " " __TIME__, sizeof(response->buildTime));
  strncpy(response->qromaFirmwareLibVersion, QROMA_LIB_FW_VERSION, sizeof(response->qromaFirmwareLibVersion));
  strncpy(response->qromaDeviceFirmwareVersion, QromaProjectFirmwareVersion, sizeof(response->qromaDeviceFirmwareVersion));
}


void QromaCoreCommandProcessor::populateCoreConfigurationResponse(QromaCoreResponse * response) {

  response->which_response = QromaCoreResponse_qromaCoreConfig_tag;
  getQromaApp()->populateQromaCoreConfig(&(response->response.qromaCoreConfig));

  logInfo("CORE CONFIG POPULATION MIGHT NOT BE INTEGRATED YET");
}


void QromaCoreCommandProcessor::handleSetQromaCommSerialIoConfig(QromaCommSerialIoConfig * config) {
  logError("SERIAL IO CONFIG NOT CONFIGURABLE YET");
}


void QromaCoreCommandProcessor::handleSetQromaCommSerialProcessingConfig(QromaCommSerialProcessingConfig * config) {
  QromaCoreConfig refConfig;
  getQromaApp()->populateQromaCoreConfig(&refConfig);
  if (refConfig.has_serialProcessingConfig) {
    memcpy(&(refConfig.serialProcessingConfig), config, sizeof(refConfig.serialProcessingConfig));
  }
  getQromaApp()->applyQromaCoreConfig(&refConfig);
}


void QromaCoreCommandProcessor::handleSetQromaCoreLoggingConfig(QromaCoreLoggingConfig * config) {
  QromaCoreConfig refConfig;
  getQromaApp()->populateQromaCoreConfig(&refConfig);
  if (refConfig.has_loggingConfig) {
    memcpy(&(refConfig.loggingConfig), config, sizeof(refConfig.loggingConfig));
  }
  getQromaApp()->applyQromaCoreConfig(&refConfig);
}


void QromaCoreCommandProcessor::handleSetQromaProjectConfiguration(QromaProjectConfiguration * config) {
  QromaCoreConfig refConfig;
  getQromaApp()->populateQromaCoreConfig(&refConfig);
  if (refConfig.has_projectConfiguration) {
    memcpy(&(refConfig.projectConfiguration), config, sizeof(refConfig.projectConfiguration));
  }
  getQromaApp()->applyQromaCoreConfig(&refConfig);
}
