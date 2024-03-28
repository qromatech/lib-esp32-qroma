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

    bool tick();

    QromaCoreConfig * getCoreConfigRef() { return &_qromaCoreConfig; }
    QromaCoreManagementConfiguration * getCoreManagementConfigRef();

    void configureQromaCore(QromaCoreConfigFn configFn);
    void updateQromaCoreConfig(QromaCoreConfigFn configFn);

    void applyQromaCoreConfig(QromaCoreConfig * config);
    void populateQromaCoreConfig(QromaCoreConfig * config);

  protected:
    QromaCoreConfig _qromaCoreConfig;
    QromaCoreManager _qromaCoreManager;
    QromaCoreConfigFn _appCoreConfigFn;

    bool _qromaCoreConfigSet = false;
};



QromaApp * getQromaApp();
void setQromaApp(QromaApp * qromaApp);

void updateQromaAppCoreConfig(QromaCoreConfigFn configFn);

// void initQromaCoreConfig(QromaCoreConfig * config);

#endif
