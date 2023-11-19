#ifndef QROMA_HEARTBEAT_H
#define QROMA_HEARTBEAT_H

#include <pb.h>
#include <qroma/qroma-app/IQromaSerialCommApp.h>

void setHeartbeatIntervalInMs(uint32_t interval);
uint32_t getHeartbeatIntervalInMs();

#endif
