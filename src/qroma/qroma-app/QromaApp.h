#ifndef QROMA_APP_H
#define QROMA_APP_H

#include "QromaAppConfig.h"
// #include "../qroma-comm/pipeline/processors/QromaBase64BracketBoundedProcessor.h"


class QromaApp {
  public:
    // QromaApp();
    virtual void init() = 0;
    virtual void initApp();

    QromaAppConfig * getAppConfigRef() { return &_appConfig; }
    // QromaCommSerialIo * getSerialCommIo();

  private:
    // QromaCommSerialIoImpl<1000, QromaBase64BracketBoundedProcessor, &Serial> _qromaCommSerialIo;
    // PbCommandsRegistry _pbCommandsRegistry;
    QromaAppConfig _appConfig = {
      .loggerConfig = {
        .logLevel = Qroma_LogLevel_LogLevel_Error
      }
      // .baudRate = 115200,
      // .rxBufferSize = 1000
    };
};



QromaApp * getQromaApp();
void setQromaApp(QromaApp * qromaApp);

#endif
