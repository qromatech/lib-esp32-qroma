#ifndef QROMA_APP_H
#define QROMA_APP_H

#include "../qroma-comm/QromaSerial.h"

class QromaApp {
  public:
    QromaApp();

    QromaSerial * initSerial();
    // void initLogger();

    QromaSerial * getSerial();

  private:
    QromaSerial _qromaSerial;
};

#endif
