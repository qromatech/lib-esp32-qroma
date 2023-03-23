#ifndef QROMA_STARTUP_H
#define QROMA_STARTUP_H

#include "../qroma-app/QromaAppConfig.h"

typedef std::function<void(QromaAppConfig * config)> QromaAppConfigFn;


void startupQroma(QromaCommMemBuffer * memBuffer);

void startupQroma(QromaCommMemBuffer * memBuffer, QromaAppConfigFn myQromaAppConfigFn);


#endif
