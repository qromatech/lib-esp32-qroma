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


void populateQromaCoreConfig(QromaCoreConfig * config) {
  if (hasQromaCoreConfigFile()) {
    if (copyQromaCoreConfigFromFile(config)) {
      return;
    }
  }

  getQromaApp()->populateQromaCoreConfig(config);
}


bool saveQromaCoreConfig() {
  logInfo("SAVING QROMA CORE CONFIG");
  QromaCoreConfig config;
  
  getQromaApp()->populateQromaCoreConfig(&config);

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
    case QromaCoreCommand_noArgCommand_tag:
      handleQromaCoreNoArgCommand(command->command.noArgCommand, qromaCommResponse);
      break;

    // case QromaCoreCommand_getFirmwareDetails_tag:
    //   coreResponse->which_response = QromaCoreResponse_firmwareDetails_tag;
    //   populateGetFirmwareDetailsResponse(&(coreResponse->response.firmwareDetails));
    //   break;

    case QromaCoreCommand_restartQromaDevice_tag:
      QromaCommResponse ackResponse;
      ackResponse.which_response = QromaCommResponse_coreResponse_tag;
      ackResponse.response.coreResponse.which_response = QromaCoreResponse_restartAck_tag;

      if (!command->command.restartQromaDevice.areYouSure) {
        ackResponse.response.coreResponse.response.restartAck.youWerentSureSoWeDidnt = true;
      }
  
      responseHandler->sendQromaCommResponse(&ackResponse, txFn);
      delay(100);

      if (command->command.restartQromaDevice.areYouSure) {
        ESP.restart();
      }

      break;

    // case QromaCoreCommand_getQromaCoreConfig_tag:
    //   qromaCommResponse->which_response = QromaCommResponse_coreResponse_tag;
    //   populateCoreConfigurationResponse(coreResponse);
    //   break;

    case QromaCoreCommand_setQromaCommSerialIoConfig_tag:
      if (command->command.setQromaCommSerialIoConfig.has_config) {
        handleSetQromaCommSerialIoConfig(&(command->command.setQromaCommSerialIoConfig.config));
      } else {
        logError("NO CONFIG VALUE PROVIDED FOR CORE COMMAND");
        logError(command->which_command);
      }
      qromaCommResponse->which_response = QromaCommResponse_coreResponse_tag;
      populateCoreConfigurationResponse(coreResponse);
      break;

    case QromaCoreCommand_setQromaCommSerialProcessingConfig_tag:
      if (command->command.setQromaCommSerialProcessingConfig.has_config) {
        handleSetQromaCommSerialProcessingConfig(&(command->command.setQromaCommSerialProcessingConfig.config));
      } else {
        logError("NO CONFIG VALUE PROVIDED FOR CORE COMMAND");
        logError(command->which_command);
      }
      qromaCommResponse->which_response = QromaCommResponse_coreResponse_tag;
      populateCoreConfigurationResponse(coreResponse);
      break;

    case QromaCoreCommand_setQromaCoreLoggingConfig_tag:
      if (command->command.setQromaCoreLoggingConfig.has_config) {
        handleSetQromaCoreLoggingConfig(&(command->command.setQromaCoreLoggingConfig.config));
      } else {
        logError("NO CONFIG VALUE PROVIDED FOR CORE COMMAND");
        logError(command->which_command);
      }
      qromaCommResponse->which_response = QromaCommResponse_coreResponse_tag;
      populateCoreConfigurationResponse(coreResponse);
      break;

    case QromaCoreCommand_setQromaCoreManagementConfiguration_tag:
      if (command->command.setQromaCoreManagementConfiguration.has_config) {
        handleSetQromaCoreManagementConfiguration(&(command->command.setQromaCoreManagementConfiguration.config));
      } else {
        logError("NO CONFIG VALUE PROVIDED FOR CORE COMMAND");
        logError(command->which_command);
      }
      qromaCommResponse->which_response = QromaCommResponse_coreResponse_tag;
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


void QromaCoreCommandProcessor::handleSetQromaCoreManagementConfiguration(QromaCoreManagementConfiguration * config) {
  QromaCoreConfig refConfig;
  getQromaApp()->populateQromaCoreConfig(&refConfig);
  if (refConfig.has_managementConfig) {
    memcpy(&(refConfig.managementConfig), config, sizeof(refConfig.managementConfig));
  }
  getQromaApp()->applyQromaCoreConfig(&refConfig);
}


void QromaCoreCommandProcessor::handleQromaCoreNoArgCommand(QromaCoreNoArgCommands noArgCommand, QromaCommResponse * qromaCommResponse) {
  QromaCoreResponse * coreResponse = &(qromaCommResponse->response.coreResponse);
  
  switch (noArgCommand) {
    case QromaCoreNoArgCommands_Qc_Nac_GetQromaCoreConfig:
      qromaCommResponse->which_response = QromaCommResponse_coreResponse_tag;
      populateCoreConfigurationResponse(coreResponse);
      break;

    case QromaCoreNoArgCommands_Qc_Nac_GetQromaCoreFirmwareDetails:
      qromaCommResponse->which_response = QromaCommResponse_coreResponse_tag;
      coreResponse->which_response = QromaCoreResponse_firmwareDetails_tag;
      populateGetFirmwareDetailsResponse(&(coreResponse->response.firmwareDetails));
      break;

    case QromaCoreNoArgCommands_Qc_Nac_DisableCoreHeartbeat:
      updateQromaAppCoreConfig([](QromaCoreConfig * config) {
        if (config->has_managementConfig && config->managementConfig.has_heartbeatConfiguration) {
          config->managementConfig.heartbeatConfiguration.heartbeatType = HeartbeatType_HeartbeatType_None;
        }
      });

      qromaCommResponse->which_response = QromaCommResponse_coreResponse_tag;
      populateCoreConfigurationResponse(coreResponse);
      break;

    case QromaCoreNoArgCommands_Qc_Nac_EnableCoreHeartbeat:
      updateQromaAppCoreConfig([](QromaCoreConfig * config) {
        if (config->has_managementConfig && config->managementConfig.has_heartbeatConfiguration) {
          config->managementConfig.heartbeatConfiguration.heartbeatType = HeartbeatType_HeartbeatType_Interval;
        }
      });

      qromaCommResponse->which_response = QromaCommResponse_coreResponse_tag;
      populateCoreConfigurationResponse(coreResponse);
      break;

    case QromaCoreNoArgCommands_Qc_Nac_DisableLogging:
      updateQromaAppCoreConfig([](QromaCoreConfig * config) {
        if (config->has_loggingConfig) {
          config->loggingConfig.logLevel = Qroma_LogLevel_LogLevel_Nothing;
        }
      });

      qromaCommResponse->which_response = QromaCommResponse_coreResponse_tag;
      populateCoreConfigurationResponse(coreResponse);
      break;

    case QromaCoreNoArgCommands_Qc_Nac_EnableAllLogging:
      updateQromaAppCoreConfig([](QromaCoreConfig * config) {
        if (config->has_loggingConfig) {
          config->loggingConfig.logLevel = Qroma_LogLevel_LogLevel_All;
        }
      });

      qromaCommResponse->which_response = QromaCommResponse_coreResponse_tag;
      populateCoreConfigurationResponse(coreResponse);
      break;

    default:
      logError("UNRECOGNIZED CORE NO-ARG COMMAND");
      logError(noArgCommand);
  }
}
