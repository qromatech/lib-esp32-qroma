#ifndef QROMA_MODULE__STARTUP_H
#define QROMA_MODULE__STARTUP_H

// #include <RTOS.h>

// #include "../bluetooth/bluetooth.h"
// #include "../qroma-point/QromaDevice.h"
// #include "../qroma-point/QromaPointInitializer.h"

#include "../qroma-app/QromaAppConfig.h"


// void startupQroma(QromaDeviceDefaults * deviceDefaults, QromaPointInitializer * qromaPointDefaults, ...);

void startupQroma(QromaAppConfig * appConfig);


#endif
