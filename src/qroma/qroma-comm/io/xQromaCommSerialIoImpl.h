// #ifndef xQROMA_COMM_SERIAL_IO_IMPL_H
// #define xQROMA_COMM_SERIAL_IO_IMPL_H

// #include "QromaCommSerialIo.h"
// #include "QromaCommSerialIoConfig.h"
// #include "../commBuffer/QromaCommMemBuffer.h"
// #include "../commBuffer/TQromaCommMemBuffer.h"
// #include "../pipeline/QromaMessageProcessingPipeline.h"
// // #include "../serial/QromaSerialRx.h"
// // #include "../serial/QromaSerialTx.h"


// template<
//   uint32_t bufferSize, 
//   typename DefaultNewDataProcessor, 
//   HardwareSerial * serial
// >
// class xQromaCommSerialIoImpl: public QromaCommSerialIo<DefaultNewDataProcessor> {
//   public:
//     QromaCommSerialIoImpl() {
//       // _implQromaCommMemBuffer = new QromaCommMemBuffer(_bufferMemory, bufferSize);
//     }

//     // QromaCommMemBuffer * getQromaCommMemBuffer() { return _implQromaCommMemBuffer; }
//     QromaCommMemBuffer * getQromaCommMemBuffer() { return &_tQromaCommMemBuffer; }

//     HardwareSerial * getSerial() { return serial; }

//     QromaNewDataProcessor * getQromaNewDataProcessor() { return &_implDefaultNewDataProcessor; }

//     void serialTxBytes(const uint8_t * bytes, uint32_t byteCount) { serial->write(bytes, byteCount); }

//     void serialPrint(const char * message) { serial->print(message); }

//     void serialPrintln(const char * message) { serial->println(message); }


//   private:
//     // uint8_t _bufferMemory[bufferSize];
//     // QromaCommMemBuffer * _implQromaCommMemBuffer;
//     TQromaCommMemBuffer<bufferSize> _tQromaCommMemBuffer;
//     DefaultNewDataProcessor _implDefaultNewDataProcessor;
// };


// #endif
