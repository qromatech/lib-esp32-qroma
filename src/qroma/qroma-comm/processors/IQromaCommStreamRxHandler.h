#ifndef QROMA_COMM_STREAM_RX_HANDLER_H
#define QROMA_COMM_STREAM_RX_HANDLER_H

#include "IQromaCommResponseHandler.h"


class IQromaCommStreamRxHandler: public IQromaCommResponseHandler {
  public:
    virtual void startStreamReadingMode() = 0;
    virtual void endStreamReadingMode() = 0;
};

#endif
