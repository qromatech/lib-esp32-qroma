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
}


void QromaApp::configureQromaCore(QromaCoreConfigFn configFn) {
  configFn(&_qromaCoreConfig);
}


void QromaApp::applyQromaCoreConfig(QromaCoreConfig * config) {
  _qromaCoreManager.applyQromaCoreConfig(config);
}


void QromaApp::populateQromaCoreConfig(QromaCoreConfig * config) {
  _qromaCoreManager.populateQromaCoreConfig(config, &_qromaCoreConfig);
}
