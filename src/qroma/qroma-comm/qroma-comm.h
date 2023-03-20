#ifndef QROMA_MODULE__COMM_H
#define QROMA_MODULE__COMM_H

#include <pb.h>
#include <functional>
#include "serial/serial.h"

#include "processors/PbCommandProcessor.h"


template <typename PbMessage, const pb_msgdesc_t *PbPbMessageFields>
void registerSerialPbMessage(std::function<void(PbMessage*)> fn)
{
  QromaCommSerialIo * qcSerialIo = getQromaApp()->getSerialCommIo();
  // qcSerialIo->registerSerialPbMessage(fn);
}


#endif
