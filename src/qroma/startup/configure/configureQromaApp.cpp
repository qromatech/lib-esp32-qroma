#include "configureQromaApp.h"


void configureQromaApp(QromaCoreConfigFn configFn, QromaApp * app) {
  configFn(app->getCoreConfigRef());
}
