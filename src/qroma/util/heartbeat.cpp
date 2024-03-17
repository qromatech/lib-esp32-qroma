#include "heartbeat.h"
#include "../../qroma-lib-proto/qroma-comm.pb.h"


uint32_t _projectLoopDelayInMs = 1000;
uint32_t _heartbeatIntervalInMs = 1000;
HeartbeatType _heartbeatType = HeartbeatType_HeartbeatType_None;


void setProjectLoopDelayInMs(uint32_t msDelay) {
  if (msDelay < 1 || msDelay > 5000) {
    return;
  }
  _projectLoopDelayInMs = msDelay;
}

uint32_t getProjectLoopDelayInMs() {
  return _projectLoopDelayInMs;
}

void setHeartbeatIntervalInMs(uint32_t interval) {
  _heartbeatIntervalInMs = interval;
}

uint32_t getHeartbeatIntervalInMs() {
  return _heartbeatIntervalInMs;
}

void setHeartbeatType(HeartbeatType heartbeatType) {
  _heartbeatType = heartbeatType;
}

HeartbeatType getHeartbeatType() {
  return _heartbeatType;
}