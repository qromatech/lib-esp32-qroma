#ifndef CONFIGURE_QROMA_SERIAL_COMM_APP_H
#define CONFIGURE_QROMA_SERIAL_COMM_APP_H

#include "../../qroma-comm/io/QromaCommSerialIoConfig.h"


typedef std::function<void(QromaCommSerialIoConfig * config)> QromaCommSerialIoConfigFn;

void configureSerialCommIo(QromaCommSerialIoConfigFn serialIoConfigFn, QromaSerialCommApp * app) {
  serialIoConfigFn(app->getSerialIoConfigRef());
}

#endif
