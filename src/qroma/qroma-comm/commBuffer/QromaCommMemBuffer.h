#ifndef QROMA_COMM_MEM_BUFFER_H
#define QROMA_COMM_MEM_BUFFER_H


#include "IQromaCommReadBuffer.h"


class QromaCommMemBuffer: public IQromaCommReadBuffer {

  public:
    QromaCommMemBuffer(uint8_t * bufferMemory, uint32_t bufferSize);

    void reset();
    void removeFirstNFromBuffer(uint32_t n);

    const uint8_t * getBufferContent();
    uint32_t getBufferWriteIndex();
    
    void addByte(uint8_t incomingByte, int now);
    uint32_t getLastTimeAddedToInMs();

  private:
    uint32_t _bufferSize;
    uint8_t * _bufferMemory;

    uint32_t _bufferWriteIndex = 0;
    uint32_t _lastTimeBufferAddedTo = 0;
};



#endif
