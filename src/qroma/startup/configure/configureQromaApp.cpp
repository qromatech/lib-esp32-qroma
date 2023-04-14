#include "configureQromaApp.h"


void configureQromaApp(QromaAppConfigFn configFn, QromaApp * app) {
  configFn(app->getAppConfigRef());
}
