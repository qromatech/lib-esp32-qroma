#include "PbCommandsRegistry.h"


// void PbCommandsRegistry::addPbCommandProcessor(IPbCommandHandler * pbCommandHandler) {
//   _pbCommandHandlers.push_back(pbCommandHandler);
// }


// int PbCommandsRegistry::getCommandHandlersCount() {
//   return _pbCommandHandlers.size();
// }


// IPbCommandHandler * PbCommandsRegistry::getCommandHandler(int i) {
//   return _pbCommandHandlers.at(i);
// }

void PbCommandsRegistry::setAppCommandProcessor(IPbCommandHandler * pbCommandHandler) {
  _appCommandHandler = pbCommandHandler;
}

    // int getCommandHandlersCount();
IPbCommandHandler * PbCommandsRegistry::PbCommandsRegistry::getAppCommandHandler() {
  return _appCommandHandler;
}