#ifndef QROMA_APP_H
#define QROMA_APP_H

#include <functional>
#include "QromaAppConfig.h"
#include "QromaCoreManager.h"
#include <qroma-lib-proto/qroma-core.pb.h>


typedef std::function<void(QromaCoreConfig * config)> QromaCoreConfigFn;

class QromaApp {
  public:
    virtual void init() = 0;
    void initApp();

    QromaCoreConfig * getCoreConfigRef() { return &_qromaCoreConfig; }
    QromaCoreManagementConfiguration * getCoreManagementConfigRef();
    void configureQromaCore(QromaCoreConfigFn configFn);

    void applyQromaCoreConfig(QromaCoreConfig * config);
    void populateQromaCoreConfig(QromaCoreConfig * config);

  private:
    // QromaAppConfig _appConfig = {
    //   .loggerConfig = {
    //     .logLevel = Qroma_LogLevel_LogLevel_Error
    //   }
    // };

    QromaCoreConfig _qromaCoreConfig;
    QromaCoreManager _qromaCoreManager;

    bool _qromaCoreConfigSet = false;
};



QromaApp * getQromaApp();
void setQromaApp(QromaApp * qromaApp);

// void initQromaCoreConfig(QromaCoreConfig * config);

#endif
