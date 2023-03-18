#ifndef QROMA_COMM_BUFFER_H
#define QROMA_COMM_BUFFER_H

#include <stdint.h>
#include <stdio.h>
#include <string.h>


class QromaCommBuffer {

  public:
    QromaCommBuffer(uint8_t * bufferMemory, uint32_t bufferSize);

    void reset();
    void removeFirstNFromBuffer(uint32_t n);

    const uint8_t * getBufferMemory();
    int getBufferWriteIndex();
    
    void addByte(uint8_t incomingByte, int now);
    int getLastTimeAddedToInMs();

  private:
    uint32_t _bufferSize;
    uint8_t * _bufferMemory;

    uint32_t _bufferWriteIndex = 0;
    uint32_t _lastTimeBufferAddedTo = 0;
};



#endif  // QROMA_COMM_BUFFER_H