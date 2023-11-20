#include "heartbeat.h"
#include "../../qroma-lib-proto/qroma-comm.pb.h"


uint32_t _heartbeatIntervalInMs = 0;


void setHeartbeatIntervalInMs(uint32_t interval) {
  _heartbeatIntervalInMs = interval;
}

uint32_t getHeartbeatIntervalInMs() {
  return _heartbeatIntervalInMs;
}
