#include "QromaCommConfigProcessor.h"
#include "../../qroma-app/QromaSerialCommApp.h"
#include <qroma/util/qroma-persist.h>



const char * QROMA_COMM_CONFIG_FILE_NAME = "/comm-config.qroma";


bool hasQromaCommConfigFile() {
  return doesFileExist(QROMA_COMM_CONFIG_FILE_NAME);
}


bool copyQromaCommConfigFromFile(QromaCommConfig * config) {
  bool success = loadPbFromPersistence(config, QROMA_COMM_CONFIG_FILE_NAME, QromaCommConfig_fields);
  if (!success) {
    logError("ERROR LOADING QROMA COMM CONFIG");
    logError(QROMA_COMM_CONFIG_FILE_NAME);
  }

  return success;
}


void copyQromaCommConfig(QromaCommConfig * config) {

  QromaSerialCommApp * serialCommApp = getQromaSerialCommApp();
  if (serialCommApp != NULL) {
    config->has_serialIoConfig = true;
    serialCommApp->copySerialIoConfig(&(config->serialIoConfig));
  } else {
    config->has_serialIoConfig = false;
    config->serialIoConfig.baudRate = 0;
    config->serialIoConfig.rxBufferSize = 0;
    config->serialIoConfig.txBufferSize = 0;
  }

  config->has_reportingConfig = true;
  config->reportingConfig.logLevel = getLogLevel();
  config->reportingConfig.heartbeatIntervalInMs = getHeartbeatIntervalInMs();
}


void populateQromaCommConfig(QromaCommConfig * config) {
  if (hasQromaCommConfigFile()) {
    if (copyQromaCommConfigFromFile(config)) {
      return;
    }
  }

  copyQromaCommConfig(config);
}


bool saveQromaCommConfig() {
  logInfo("SAVING QROMA COMM CONFIG");
  QromaCommConfig config;
  
  copyQromaCommConfig(&config);

  bool saved = savePbToPersistence<QromaCommConfig>(&config, QROMA_COMM_CONFIG_FILE_NAME, QromaCommConfig_fields);

  if (!saved) {
    logError("ERROR SAVING QROMA COMM CONFIG");
    logError(QROMA_COMM_CONFIG_FILE_NAME);
  }

  logInfo("DONE SAVING QROMA COMM CONFIG");

  return saved;
}



uint32_t QromaCommConfigProcessor::handleQromaCommConfigCommand(QromaCommConfigCommand * command, 
  QromaCommResponse * response, std::function<void(uint8_t*, uint32_t)> txFn)
{
  switch (command->which_command) {
    case QromaCommConfigCommand_requestQromaCommConfig_tag:
      response->response.commConfigResponse.which_response = QromaCommConfigResponse_qromaCommConfig_tag;
      copyQromaCommConfig(&(response->response.commConfigResponse.response.qromaCommConfig));
      break;

    case QromaCommConfigCommand_requestQromaCommSerialIoConfig_tag:
    {
      response->response.commConfigResponse.which_response = QromaCommConfigResponse_qromaCommSerialIoConfig_tag;
      QromaSerialCommApp * serialCommApp = getQromaSerialCommApp();
      if (serialCommApp != NULL) {
        serialCommApp->copySerialIoConfig(&(response->response.commConfigResponse.response.qromaCommSerialIoConfig));
      } else {
        response->response.commConfigResponse.response.qromaCommSerialIoConfig.baudRate = 0;
        response->response.commConfigResponse.response.qromaCommSerialIoConfig.rxBufferSize = 0;
        response->response.commConfigResponse.response.qromaCommSerialIoConfig.txBufferSize = 0;
      }
    }
      break;

    case QromaCommConfigCommand_requestQromaCommReportingConfig_tag:
      response->response.commConfigResponse.which_response = QromaCommConfigResponse_qromaCommReportingConfig_tag;
      response->response.commConfigResponse.response.qromaCommReportingConfig.logLevel = getLogLevel();
      response->response.commConfigResponse.response.qromaCommReportingConfig.heartbeatIntervalInMs = getHeartbeatIntervalInMs();
      break;

    case QromaCommConfigCommand_setLogLevel_tag:
      setLogLevel(command->command.setLogLevel.logLevel);
      response->response.commConfigResponse.which_response = QromaCommConfigResponse_setLogLevel_tag;
      response->response.commConfigResponse.response.setLogLevel.logLevel = getLogLevel();
      saveQromaCommConfig();
      break;

    case QromaCommConfigCommand_setHeartbeatInterval_tag:
      setHeartbeatIntervalInMs(command->command.setHeartbeatInterval.heartbeatIntervalInMs);
      response->response.commConfigResponse.which_response = QromaCommConfigResponse_setHeartbeatInterval_tag;
      response->response.commConfigResponse.response.setHeartbeatInterval.heartbeatIntervalInMs = getHeartbeatIntervalInMs();
      saveQromaCommConfig();
      break;
  }

  return 0;
}
