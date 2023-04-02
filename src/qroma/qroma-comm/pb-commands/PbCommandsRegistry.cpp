#include "PbCommandsRegistry.h"


void PbCommandsRegistry::addPbCommandProcessor(IPbCommandHandler * pbCommandHandler) {
  _pbCommandHandlers.push_back(pbCommandHandler);
}


int PbCommandsRegistry::getCommandHandlersCount() {
  return _pbCommandHandlers.size();
}


IPbCommandHandler * PbCommandsRegistry::getCommandHandler(int i) {
  return _pbCommandHandlers.at(i);
}