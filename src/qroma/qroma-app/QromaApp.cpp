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


// QromaCommSerialIo * QromaApp::initSerialCommIo() {
//   _qromaCommSerialIo.init();
//   return &_qromaCommSerialIo;
// }


QromaCommSerialIo * QromaApp::getSerialCommIo() {
  return &_qromaCommSerialIo;
}
