#ifndef QROMA_STARTUP_H
#define QROMA_STARTUP_H

#include "../qroma-app/QromaAppConfig.h"
#include "../qroma-app/QromaSerialCommApp.h"
#include "register/registerPbCommandHandlers.h"

typedef std::function<void(QromaAppConfig * config)> QromaAppConfigFn;


void startupQroma(QromaCommMemBuffer * memBuffer);

void startupQroma(QromaCommMemBuffer * memBuffer, QromaAppConfigFn myQromaAppConfigFn);

void startupQroma(QromaSerialCommApp * app, QromaAppConfigFn myQromaAppConfigFn);

void startupQroma(QromaSerialCommApp * app);


#endif
