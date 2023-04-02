// #ifndef xIQROMA_COMM_SERIAL_IO_H
// #define xIQROMA_COMM_SERIAL_IO_H

// #include "QromaCommSerialIoConfig.h"
// #include "../commBuffer/QromaCommMemBuffer.h"
// #include "../pipeline/QromaMessageProcessingPipeline.h"
// // #include "../serial/QromaSerialRx.h"
// // #include "../serial/QromaSerialTx.h"
// #include "../pipeline/QromaCommSerialRxProcessor.h"


// // template<
// //   typename NewDataProcessor
// // >
// class xQromaCommSerialIo {
//   public:
//     // QromaCommSerialIo();

//     void init(QromaCommSerialIoConfig * config, PbCommandsRegistry * pbCommandsRegistry);

//     // void onSerialReceive();
//     void serialRx();
//     bool processCommBuffer();

//     // void serialTxBytes(const uint8_t * bytes, uint32_t byteCount);
//     // void serialPrint(const char * message);
//     // void serialPrintln(const char * message);

//     virtual QromaCommMemBuffer * getQromaCommMemBuffer();
//     virtual HardwareSerial * getSerial();
//     virtual QromaNewDataProcessor * getQromaNewDataProcessor();

//   private:
//     QromaCommMemBuffer * _qromaCommMemBuffer;
//     HardwareSerial * _serial;
//     // QromaNewDataProcessor * _newDataProcessor;
//     QromaCommSerialRxProcessor<NewDataProcessor> _serialRxProcessor;

//     PbCommandsRegistry * _pbCommandsRegistry;

//     // DefaultNewDataProcessor _newDataProcessor;


//   //   DefaultNewDataProcessor _newDataProcessor;

//     // QromaSerialRx _qromaSerialRx;
//     // QromaSerialTx _qromaSerialTx;
// };


// #endif
