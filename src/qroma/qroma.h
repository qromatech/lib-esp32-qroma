#ifndef QROMA_H
#define QROMA_H

// #include <RTOS.h>
#include <pb.h>
#include <functional>

// #include "../bluetooth/bluetooth.h"
// #include "../qroma-point/QromaDevice.h"
// #include "../qroma-point/QromaPointInitializer.h"

// typedef std::function<void(void)> OnReceiveCb;


// void startupQroma(QromaDeviceDefaults * deviceDefaults, QromaPointInitializer * qromaPointDefaults, ...);

void startupQroma();

template <typename PbMessage, const pb_msgdesc_t *PbPbMessageFields>
void registerPbMessage(std::function<void(PbMessage*)> fn)
{
  
}


#endif
