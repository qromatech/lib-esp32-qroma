#ifndef QROMA_APP_H
#define QROMA_APP_H

#include "QromaAppConfig.h"


class QromaApp {
  public:
    virtual void init() = 0;
    void initApp();

    QromaAppConfig * getAppConfigRef() { return &_appConfig; }

  private:
    QromaAppConfig _appConfig = {
      .loggerConfig = {
        .logLevel = Qroma_LogLevel_LogLevel_Error
      }
    };
};



QromaApp * getQromaApp();
void setQromaApp(QromaApp * qromaApp);

#endif
