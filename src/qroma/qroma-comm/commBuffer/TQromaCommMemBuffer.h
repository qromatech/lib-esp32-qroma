#ifndef T_QROMA_COMM_MEM_BUFFER_H
#define T_QROMA_COMM_MEM_BUFFER_H


#include "QromaCommMemBuffer.h"

template<
  uint32_t bufferSize
>
class TQromaCommMemBuffer: public QromaCommMemBuffer {

  public:
    TQromaCommMemBuffer() : QromaCommMemBuffer((uint8_t*)_tBufferMemory, bufferSize) { }

  private:
    uint8_t _tBufferMemory[bufferSize];
};



#endif  // T_QROMA_COMM_MEM_BUFFER_H
