#include "PbCommandsRegistry.h"


void PbCommandsRegistry::setAppCommandProcessor(IPbCommandHandler * pbCommandHandler) {
  _appCommandHandler = pbCommandHandler;
}

IPbCommandHandler * PbCommandsRegistry::PbCommandsRegistry::getAppCommandHandler() {
  return _appCommandHandler;
}