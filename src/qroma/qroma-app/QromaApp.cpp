#include "QromaApp.h"


QromaApp * _gQromaApp;

QromaApp * getQromaApp() {
  return _gQromaApp;
}


void setQromaApp(QromaApp * qromaApp) {
  _gQromaApp = qromaApp;
}


void QromaApp::initApp() {
  _qromaCoreManager.initQromaCoreConfigDefaults(&_qromaCoreConfig);
  if (_appCoreConfigFn != NULL) {
    _appCoreConfigFn(&_qromaCoreConfig);
  }
  applyQromaCoreConfig(&_qromaCoreConfig);
}


void QromaApp::configureQromaCore(QromaCoreConfigFn configFn) {
  _appCoreConfigFn = configFn;
  // configFn(&_qromaCoreConfig);
  // applyQromaCoreConfig(&_qromaCoreConfig);
}


void QromaApp::applyQromaCoreConfig(QromaCoreConfig * config) {
  _qromaCoreManager.applyQromaCoreConfig(config);
}


void QromaApp::populateQromaCoreConfig(QromaCoreConfig * config) {
  _qromaCoreManager.populateQromaCoreConfig(config, &_qromaCoreConfig);
}


// bool QromaApp::tick() {
//   bool waitedConfiguredDelay = false;
  
//   if (_qromaCoreConfig.has_managementConfig && _qromaCoreConfig.managementConfig.projectLoopDelayInMs >= 10) {
//     logInfoUintWithDescription("QROMA APP PRE-DELAY - ", _qromaCoreConfig.managementConfig.projectLoopDelayInMs);
//     delay(_qromaCoreConfig.managementConfig.projectLoopDelayInMs);
//     logInfo("QROMA APP POST-DELAY");
//     waitedConfiguredDelay = true;
//   } else {
//     delay(100);
//     logInfo("QROMA APP UNABLE TO SUCCESSFULLY TICK - DELAYING 100 MS");
//   }

//   return waitedConfiguredDelay;
// }


QromaCoreManagementConfiguration * QromaApp::getCoreManagementConfigRef() {
  if (_qromaCoreConfig.has_managementConfig) {
    return &(_qromaCoreConfig.managementConfig);
  }
  return NULL;
}
