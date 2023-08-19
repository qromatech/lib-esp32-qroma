#ifndef PB_COMMANDS_REGISTRY_H
#define PB_COMMANDS_REGISTRY_H

#include <pb.h>
#include <functional>
#include <vector>
#include "IPbCommandHandler.h"


class PbCommandsRegistry {

  // public:
  //   void addPbCommandProcessor(IPbCommandHandler * pbCommandHandler);

  //   int getCommandHandlersCount();
  //   IPbCommandHandler * getCommandHandler(int i);


  // private:
  //   std::vector<IPbCommandHandler*> _pbCommandHandlers;

  
  public:
    void setAppCommandProcessor(IPbCommandHandler * pbCommandHandler);

    // int getCommandHandlersCount();
    IPbCommandHandler * getAppCommandHandler();

    // bool decode_callback(pb_istream_t *stream, const pb_field_t *field, void ** arg)
    bool (*decodeFunc)(pb_istream_t *stream, const pb_field_t *field, void **arg);

    


  private:
    // std::vector<IPbCommandHandler*> _pbCommandHandlers;
    IPbCommandHandler * _appCommandHandler;


};

#endif
