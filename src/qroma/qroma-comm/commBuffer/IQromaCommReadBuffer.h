#ifndef IQROMA_COMM_BUFFER_H
#define IQROMA_COMM_BUFFER_H

#include <stdint.h>
#include <stdio.h>
#include <string.h>


class IQromaCommReadBuffer {

  public:
    // QromaCommBuffer(uint8_t * bufferMemory, uint32_t bufferSize);

    virtual void reset();
    virtual void removeFirstNFromBuffer(uint32_t n);

    virtual const uint8_t * getBufferContent();
    virtual uint32_t getBufferWriteIndex();
    
    // void addByte(uint8_t incomingByte, int now);
    virtual uint32_t getLastTimeAddedToInMs();

  // private:
  //   uint32_t _bufferSize;
  //   uint8_t * _bufferMemory;

  //   uint32_t _bufferWriteIndex = 0;
  //   uint32_t _lastTimeBufferAddedTo = 0;
};



#endif  // QROMA_COMM_BUFFER_H