#include "QromaSerialCommApp.h"


QromaSerialCommApp * _gQromaSerialCommApp;

QromaSerialCommApp * getQromaSerialCommApp() {
  return _gQromaSerialCommApp;
}


void setQromaSerialCommApp(QromaSerialCommApp * qromaApp) {
  _gQromaSerialCommApp = qromaApp;
}


void QromaSerialCommApp::startupQroma() {
  setQromaApp(this);
  setQromaSerialCommApp(this);
  init();
  _whenHeartbeatLastSentInMs = 0;
  _numHeartbeatTicks = 0;
}