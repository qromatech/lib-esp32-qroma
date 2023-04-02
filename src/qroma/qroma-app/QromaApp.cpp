#include "QromaApp.h"


// QromaApp _gQromaApp = QromaApp();
QromaApp * _gQromaApp;

QromaApp * getQromaApp() {
  return _gQromaApp;
}

void setQromaApp(QromaApp * qromaApp) {
  _gQromaApp = qromaApp;
}


// QromaApp::QromaApp() {

// }

void QromaApp::initApp() {
  setLogLevel(_appConfig.loggerConfig.logLevel);
}


// void QromaApp::init(QromaAppConfig * config) {
// //   _qromaCommSerialIo.init(&(config->serialIoConfig));
  
//   setLogLevel(config->loggerConfig.logLevel);
// }


// QromaCommSerialIo * QromaApp::getSerialCommIo() {
//   return &_qromaCommSerialIo;
// }
