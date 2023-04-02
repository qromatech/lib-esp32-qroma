#ifndef PB_COMMANDS_REGISTRY_H
#define PB_COMMANDS_REGISTRY_H

#include <pb.h>
#include <functional>
#include <vector>
#include "IPbCommandHandler.h"


class PbCommandsRegistry {

  public:
    void addPbCommandProcessor(IPbCommandHandler * pbCommandHandler);

    int getCommandHandlersCount();
    IPbCommandHandler * getCommandHandler(int i);


  private:
    std::vector<IPbCommandHandler*> _pbCommandHandlers;

};

#endif
