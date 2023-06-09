#ifndef IQROMA_NEW_DATA_PB_PROCESSOR_H
#define IQROMA_NEW_DATA_PB_PROCESSOR_H

#include <pb.h>
#include "../pb-commands/PbCommandsRegistry.h"
#include <functional>


class IQromaNewDataPbProcessor {
  public:
    virtual uint32_t processBytes(
      const uint8_t * bytes,
      uint32_t byteCount, 
      PbCommandsRegistry * pbCommandsRegistry, 
      std::function<void(uint8_t*, uint32_t)> txFn
    ) = 0;

  private:

};

#endif
