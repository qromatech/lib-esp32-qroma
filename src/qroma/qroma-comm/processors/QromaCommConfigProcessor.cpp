#include "QromaCommConfigProcessor.h"
#include "../../qroma-app/QromaSerialCommApp.h"


uint32_t QromaCommConfigProcessor::handleQromaCommConfigCommand(QromaCommConfigCommand * command, 
  QromaCommResponse * response, std::function<void(uint8_t*, uint32_t)> txFn)
{
  switch (command->which_command) {
    case QromaCommConfigCommand_requestQromaCommConfig_tag:
    {
      response->response.commConfigResponse.which_response = QromaCommConfigResponse_qromaCommConfig_tag;
      
      response->response.commConfigResponse.response.qromaCommConfig.has_serialIoConfig = true;
      QromaSerialCommApp * serialCommApp = getQromaSerialCommApp();
      if (serialCommApp != NULL) {
        serialCommApp->copySerialIoConfig(&(response->response.commConfigResponse.response.qromaCommSerialIoConfig));
      }

      response->response.commConfigResponse.response.qromaCommConfig.has_reportingConfig = true;
      response->response.commConfigResponse.response.qromaCommConfig.reportingConfig.logLevel = getLogLevel();
      response->response.commConfigResponse.response.qromaCommConfig.reportingConfig.heartbeatIntervalInMs = getHeartbeatIntervalInMs();
    }
      break;

    case QromaCommConfigCommand_requestQromaCommSerialIoConfig_tag:
    {
      response->response.commConfigResponse.which_response = QromaCommConfigResponse_qromaCommSerialIoConfig_tag;
      QromaSerialCommApp * serialCommApp = getQromaSerialCommApp();
      if (serialCommApp != NULL) {
        serialCommApp->copySerialIoConfig(&(response->response.commConfigResponse.response.qromaCommSerialIoConfig));
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
      break;

    case QromaCommConfigCommand_setHeartbeatInterval_tag:
      setHeartbeatIntervalInMs(command->command.setHeartbeatInterval.heartbeatIntervalInMs);
      response->response.commConfigResponse.which_response = QromaCommConfigResponse_setHeartbeatInterval_tag;
      response->response.commConfigResponse.response.setHeartbeatInterval.heartbeatIntervalInMs = getHeartbeatIntervalInMs();
      break;
  }
  return 0;
}
