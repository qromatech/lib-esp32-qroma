// #ifndef xQROMA_COMM_SERIAL_IO_BASE_H
// #define xQROMA_COMM_SERIAL_IO_BASE_H

// #include "IQromaCommSerialIo.h"
// #include "QromaCommSerialIoConfig.h"
// #include "../commBuffer/QromaCommMemBuffer.h"
// #include "../pipeline/QromaMessageProcessingPipeline.h"
// // #include "../serial/QromaSerialRx.h"
// // #include "../serial/QromaSerialTx.h"


// class xQromaCommSerialIoBase: IQromaCommSerialIo {
//   public:
//     // QromaCommSerialIo();

//     void init(QromaCommSerialIoConfig * config);

//     // void onSerialReceive();
//     void serialRx();
//     bool processCommBuffer();

//     void serialTxBytes(const uint8_t * bytes, uint32_t byteCount);
//     void serialPrint(const char * message);
//     void serialPrintln(const char * message);

//     virtual QromaCommMemBuffer * getQromaCommMemBuffer();
//     virtual HardwareSerial * getSerial();

//   // private:
//   //   QromaCommMemBuffer * _qromaCommMemBuffer;
//   //   HardwareSerial * _serial;


//   //   DefaultNewDataProcessor _newDataProcessor;

//     // QromaSerialRx _qromaSerialRx;
//     // QromaSerialTx _qromaSerialTx;
// };


// #endif
