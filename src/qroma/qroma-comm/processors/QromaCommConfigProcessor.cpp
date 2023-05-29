#include "QromaCommConfigProcessor.h"


uint32_t QromaCommConfigProcessor::handleQromaCommConfigCommand(QromaCommConfigCommand * command, QromaCommResponse * response) {
  switch (command->which_command) {
    case QromaCommConfigCommand_setLogLevel_tag:
      setLogLevel(command->command.setLogLevel.logLevel);
      break;
  }
  return 0;
}
