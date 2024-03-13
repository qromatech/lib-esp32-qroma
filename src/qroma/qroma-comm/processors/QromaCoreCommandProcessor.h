#ifndef QROMA_CORE_COMMAND_PROCESSOR_H
#define QROMA_CORE_COMMAND_PROCESSOR_H

#include <pb.h>
#include <qroma-lib-proto/qroma-comm.pb.h>
#include <qroma-lib-proto/qroma-core.pb.h>
#include <qroma/util/logger.h>
#include <qroma/util/heartbeat.h>
#include <qroma/util/qbase64.h>
#include <pb_decode.h>
#include <pb_encode.h>
#include <functional>
#include "IQromaCommResponseHandler.h"


class QromaCoreCommandProcessor {
  public:
    void handleQromaCoreCommand(QromaCoreCommand * command, QromaCommResponse * response,
      IQromaCommResponseHandler * responseHandler, std::function<void(uint8_t*, uint32_t)> txFn);

    void populateGetFirmwareDetailsResponse(FirmwareDetails * response);
    void populateCoreConfigurationResponse(QromaCoreResponse * response);

    void handleSetQromaCommSerialIoConfig(QromaCommSerialIoConfig * config);
    void handleSetQromaCommSerialProcessingConfig(QromaCommSerialProcessingConfig * config);
    void handleSetQromaCoreLoggingConfig(QromaCoreLoggingConfig * config);
    void handleSetQromaProjectConfiguration(QromaProjectConfiguration * config);
};



// extern void populateQromaProjectConfiguration(QromaProjectConfiguration * config);
// extern void setHeartbeatConfiguration(QromaProjectConfiguration * config);

// extern void populateHeartbeatConfiguration(HeartbeatConfiguration * config);
// extern void setHeartbeatConfiguration(HeartbeatConfiguration * config);

#endif
