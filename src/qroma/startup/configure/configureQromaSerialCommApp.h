#ifndef CONFIGURE_QROMA_SERIAL_COMM_APP_H
#define CONFIGURE_QROMA_SERIAL_COMM_APP_H

#include <functional>
#include "../../qroma-app/QromaApp.h"
#include "../../qroma-app/QromaAppConfig.h"
#include "../../qroma-comm/io/QromaCommSerialIoConfig.h"
#include "../../qroma-app/QromaSerialCommApp.h"


typedef std::function<void(QromaCommSerialIoConfig * config)> QromaCommSerialIoConfigFn;

void configureSerialCommIo(QromaCommSerialIoConfigFn serialIoConfigFn, QromaSerialCommApp * app);

#endif
