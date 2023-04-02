#ifndef IQROMA_COMM_BUFFER_H
#define IQROMA_COMM_BUFFER_H

#include <stdint.h>
#include <stdio.h>
#include <string.h>


class IQromaCommReadBuffer {

  public:

    virtual void reset();
    virtual void removeFirstNFromBuffer(uint32_t n);

    virtual const uint8_t * getBufferContent();
    virtual uint32_t getBufferWriteIndex();
    
    virtual uint32_t getLastTimeAddedToInMs();

  private:
};

#endif
