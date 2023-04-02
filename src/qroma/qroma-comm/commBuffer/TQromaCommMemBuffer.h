#ifndef T_QROMA_COMM_MEM_BUFFER_H
#define T_QROMA_COMM_MEM_BUFFER_H


#include "QromaCommMemBuffer.h"

template<
  uint32_t bufferSize
>
class TQromaCommMemBuffer: public QromaCommMemBuffer {

  public:
    // QromaCommMemBuffer(uint8_t * bufferMemory, uint32_t bufferSize);
    TQromaCommMemBuffer() : QromaCommMemBuffer((uint8_t*)_tBufferMemory, bufferSize) { }

    // void reset();
    // void removeFirstNFromBuffer(uint32_t n);

    // const uint8_t * getBufferContent();
    // uint32_t getBufferWriteIndex();
    
    // void addByte(uint8_t incomingByte, int now);
    // uint32_t getLastTimeAddedToInMs();

  private:
    // uint32_t _bufferSize;
    // uint8_t * _bufferMemory;
    uint8_t _tBufferMemory[bufferSize];


    // uint32_t _bufferWriteIndex = 0;
    // uint32_t _lastTimeBufferAddedTo = 0;
};



#endif  // T_QROMA_COMM_MEM_BUFFER_H
