#include "QromaCommConfigProcessor.h"


uint32_t QromaCommConfigProcessor::handleQromaCommConfigCommand(QromaCommConfigCommand * command, 
  QromaCommResponse * response, std::function<void(uint8_t*, uint32_t)> txFn)
{
//   #define QromaCommConfigCommand_requestQromaCommConfig_tag 1
// #define QromaCommConfigCommand_setLogLevel_tag   2
// #define QromaCommConfigCommand_setHeartbeatInterval_tag 3

  switch (command->which_command) {
    case QromaCommConfigCommand_requestQromaCommConfig_tag:

      break;
    case QromaCommConfigCommand_setLogLevel_tag:
      // Serial.println("SETTING COMM CONFIG - LOG LEVEL");
      setLogLevel(command->command.setLogLevel.logLevel);
      break;
    case QromaCommConfigCommand_setHeartbeatInterval_tag:

      break;
  }
  return 0;
}
