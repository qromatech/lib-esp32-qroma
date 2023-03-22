#include "QromaApp.h"


QromaApp _gQromaApp = QromaApp();

QromaApp * getQromaApp() {
  return &_gQromaApp;
}


QromaApp::QromaApp() {

}


void QromaApp::init(QromaAppConfig * config) {
  _qromaCommSerialIo.init(&(config->serialIoConfig));
}


QromaCommSerialIo * QromaApp::getSerialCommIo() {
  return &_qromaCommSerialIo;
}
