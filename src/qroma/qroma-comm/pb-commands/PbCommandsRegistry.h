#ifndef PB_COMMANDS_REGISTRY_H
#define PB_COMMANDS_REGISTRY_H

#include <pb.h>
#include <functional>
#include <vector>
#include "IPbCommandHandler.h"


class PbCommandsRegistry {
  
  public:
    void setAppCommandProcessor(IPbCommandHandler * pbCommandHandler);

    IPbCommandHandler * getAppCommandHandler();

    bool (*decodeFunc)(pb_istream_t *stream, const pb_field_t *field, void **arg);

  private:
    IPbCommandHandler * _appCommandHandler;

};

#endif
