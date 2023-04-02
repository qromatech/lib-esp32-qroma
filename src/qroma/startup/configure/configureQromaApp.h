#ifndef CONFIGURE_QROMA_APP_H
#define CONFIGURE_QROMA_APP_H

#include <functional>
#include "../../qroma-app/QromaApp.h"
#include "../../qroma-app/QromaAppConfig.h"


typedef std::function<void(QromaAppConfig * config)> QromaAppConfigFn;

void configureQromaApp(QromaAppConfigFn configFn, QromaApp * app) {
  configFn(app->getAppConfigRef());
}

#endif


