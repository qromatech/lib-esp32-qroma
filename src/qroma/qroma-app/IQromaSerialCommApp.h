#ifndef IQROMA_SERIAL_COMM_APP_H
#define IQROMA_SERIAL_COMM_APP_H

#include <qroma/qroma-comm/io/IQromaCommSerialTx.h>


class IQromaSerialCommApp {
  public:
    virtual IQromaCommSerialTx * getSerialTx() = 0;
};

#endif
