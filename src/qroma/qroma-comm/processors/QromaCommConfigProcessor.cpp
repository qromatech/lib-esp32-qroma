#include "QromaCommConfigProcessor.h"


uint32_t QromaCommConfigProcessor::handleQromaCommConfigCommand(QromaCommConfigCommand * command, 
  QromaCommResponse * response, std::function<void(uint8_t*, uint32_t)> txFn)
{
  switch (command->which_command) {
    case QromaCommConfigCommand_requestQromaCommConfig_tag:
      response->response.commConfigResponse.which_response = QromaCommConfigResponse_qromaCommConfig_tag;
      response->response.commConfigResponse.response.qromaCommConfig.logLevel = getLogLevel();
      response->response.commConfigResponse.response.qromaCommConfig.heartbeatIntervalInMs = getHeartbeatIntervalInMs();
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
