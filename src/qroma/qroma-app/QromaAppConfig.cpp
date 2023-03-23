#include "QromaAppConfig.h"

QromaAppConfig _gQromaAppConfig = QromaAppConfig();


QromaAppConfig * getQromaAppConfig() {
  return &_gQromaAppConfig;
}


bool QromaAppConfig::validate() {
  return true;
}
