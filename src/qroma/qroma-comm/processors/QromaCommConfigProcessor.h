#ifndef QROMA_COMM_CONFIG_PROCESSOR_H
#define QROMA_COMM_CONFIG_PROCESSOR_H

#include <pb.h>
#include <qroma-lib-proto/qroma-comm.pb.h>
#include "../../util/logger.h"
#include "../../util/qbase64.h"
#include <pb_decode.h>
#include <pb_encode.h>


class QromaCommConfigProcessor {
  public:
    uint32_t handleQromaCommConfigCommand(QromaCommConfigCommand * command, QromaCommResponse * response,
      std::function<void(uint8_t*, uint32_t)> txFn);
};

#endif
