#ifndef PB_SERIAL_COMM_H
#define PB_SERIAL_COMM_H

// #include "pbUartBleComm.h"
#include <pb.h>


class PbSerialComm {

  public:
    bool readData();
    uint32_t readSerialToFile(uint32_t silenceDelayTimeoutInMs, uint32_t filesize, char * fname);

    void setPbBuildingMessage(bool buildingMessage) { /* no-op */ };
    void pbSendBytes(uint8_t * values, uint32_t count);
};


#endif
