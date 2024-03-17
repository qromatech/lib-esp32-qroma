#ifndef QROMA_HEARTBEAT_H
#define QROMA_HEARTBEAT_H

#include <pb.h>
#include <qroma/qroma-app/IQromaSerialCommApp.h>
#include <qroma-lib-proto/qroma-types.pb.h>

void setProjectLoopDelayInMs(uint32_t msDelay);
uint32_t getProjectLoopDelayInMs();

void setHeartbeatIntervalInMs(uint32_t interval);
uint32_t getHeartbeatIntervalInMs();

void setHeartbeatType(HeartbeatType heartbeatType);
HeartbeatType getHeartbeatType();

#endif
