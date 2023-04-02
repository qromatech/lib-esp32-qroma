#ifndef REGISTER_PB_COMMAND_HANDLERS_H
#define REGISTER_PB_COMMAND_HANDLERS_H

#include <pb.h>
#include <functional>

#include "../../qroma-app/QromaAppConfig.h"
#include "../../qroma-comm/pb-commands/PbCommandHandler.h"
#include "../../qroma-comm/pb-commands/PbCommandWithResponseHandler.h"


template<
  typename PbMessage, 
  const pb_msgdesc_t *PbMessageFields
  >
void registerPbCommandFunction(std::function<void(PbMessage*)> handlerFunction, PbCommandsRegistry * pbCommandsRegistry) {
  PbCommandHandler<PbMessage, PbMessageFields> * pbCommandHandler = 
    new PbCommandHandler<PbMessage, PbMessageFields>(handlerFunction);

  pbCommandsRegistry->addPbCommandProcessor(pbCommandHandler);
  
  // QromaAppConfig * appConfig = getQromaAppConfig();
}

template<
  typename PbMessage, 
  const pb_msgdesc_t *PbMessageFields,
  typename PbResponse, 
  const pb_msgdesc_t *PbResponseFields
  >
void registerPbCommandFunction(std::function<void(PbMessage*, PbResponse*)> handlerFunction, PbCommandsRegistry * pbCommandsRegistry)
{
  PbCommandWithResponseHandler<PbMessage, PbMessageFields, PbResponse, PbResponseFields> * pbCommandHandler = 
    new PbCommandWithResponseHandler<PbMessage, PbMessageFields, PbResponse, PbResponseFields>(handlerFunction);

  pbCommandsRegistry->addPbCommandProcessor(pbCommandHandler);

  // QromaAppConfig * appConfig = getQromaAppConfig();

  

  // config->serialIoConfig.qromaBytesProcessors = qromaBytesProcessors;
  // config->serialIoConfig.qromaBytesProcessorsCount = sizeof(qromaBytesProcessors) / sizeof(QromaBytesProcessor*);

}

#endif
