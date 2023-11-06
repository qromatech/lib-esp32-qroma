#include "qroma_startup.h"
#include <qroma/qroma-app/QromaApp.h>
#include <qroma/qroma-app/QromaSerialCommApp.h>
#include <qroma/qroma-app/QromaAppConfig.h>


void _startupQroma(QromaApp * qromaApp) {

  setQromaApp(qromaApp);
  qromaApp->init();
}
