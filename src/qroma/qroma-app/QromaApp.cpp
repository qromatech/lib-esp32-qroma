#include "QromaApp.h"

QromaApp::QromaApp() {

}


QromaSerial * QromaApp::initSerial() {
  _qromaSerial.init();
  return &_qromaSerial;
}


QromaSerial * QromaApp::getSerial() {
  return &_qromaSerial;
}
