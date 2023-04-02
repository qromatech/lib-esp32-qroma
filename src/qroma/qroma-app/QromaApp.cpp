#include "QromaApp.h"


QromaApp * _gQromaApp;

QromaApp * getQromaApp() {
  return _gQromaApp;
}


void setQromaApp(QromaApp * qromaApp) {
  _gQromaApp = qromaApp;
}


void QromaApp::initApp() {
  setLogLevel(_appConfig.loggerConfig.logLevel);
}
