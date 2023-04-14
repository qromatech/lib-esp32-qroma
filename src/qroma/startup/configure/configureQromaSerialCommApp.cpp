#include "configureQromaSerialCommApp.h"


void configureSerialCommIo(QromaCommSerialIoConfigFn serialIoConfigFn, QromaSerialCommApp * app) {
  serialIoConfigFn(app->getSerialIoConfigRef());
}
