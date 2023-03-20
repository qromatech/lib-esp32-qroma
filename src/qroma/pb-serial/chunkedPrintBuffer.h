// #ifndef CHUNKED_PRINT_BUFFER_H
// #define CHUNKED_PRINT_BUFFER_H

// #include <stdint.h>
// #include <stdio.h>
// #include <string.h>
// #include <CircularBuffer.h>

// #define CHUNKED_PRINT_BUFFER_SIZE 10000


// class ChunkedPrintBuffer {
//   public:
//     ChunkedPrintBuffer();

//     void _addByte(uint8_t byte);
//     void addBytes(const uint8_t * bytes, size_t length);

//     void addMessage(const char * msg);
    
//     void addLine(const char * msg);
//     void addLine(const char * msg, const char * value);
//     void addIntMessageLine(const char * msg, int value);

//     uint32_t size();
//     size_t readBytes(uint8_t *buffer, size_t length);

//     bool isEmpty();


//   private:
//     int _lastTimeChunkedPrintBufferAddedTo = 0;

//     CircularBuffer<uint8_t, CHUNKED_PRINT_BUFFER_SIZE> * _buffer;
// };


// #endif  // CHUNKED_PRINT_BUFFER_H