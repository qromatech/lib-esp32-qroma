#ifndef QROMA_APP_H
#define QROMA_APP_H

#include "QromaAppConfig.h"
#include "../qroma-comm/io/QromaCommSerialIo.h"


class QromaApp {
  public:
    QromaApp();

    void init(QromaAppConfig * config);

    QromaCommSerialIo * getSerialCommIo();


    // QromaSerial * initSerial();
    // void initLogger();

    // QromaSerial * getSerial();

  private:
    QromaCommSerialIo _qromaCommSerialIo;
};



QromaApp * getQromaApp();

#endif
