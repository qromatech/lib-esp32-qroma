#ifndef IQROMA_COMM_SERIAL_TX_H
#define IQROMA_COMM_SERIAL_TX_H

#include <pb.h>

class IQromaCommSerialTx {
  public:
    virtual void serialTxBytes(const uint8_t * bytes, uint32_t byteCount) = 0;
};


#endif
