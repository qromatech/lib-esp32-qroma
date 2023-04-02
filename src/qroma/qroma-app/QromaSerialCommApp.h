#ifndef QROMA_SERIAL_COMM_APP_H
#define QROMA_SERIAL_COMM_APP_H

#include "QromaApp.h"
#include "QromaAppConfig.h"
#include "../qroma-comm/io/QromaCommSerialIo.h"
#include "../qroma-comm/pipeline/processors/QromaBase64BracketBoundedPbProcessor.h"
#include "../qroma-comm/pipeline/processors/QromaBase64NewLineDelimitedPbProcessor.h"
#include "../qroma-comm/pipeline/processors/QromaBytesPbProcessor.h"

#include "QromaSerialCommAppBase.h"


// class QromaSerialCommApp: public QromaApp, 
//                           public PbCommandsRegistry 
// {
//   public:
//     // QromaSerialCommApp();

//     // void init(QromaAppConfig * config);
//     void init();

//     QromaCommSerialIoConfig * getSerialIoConfigRef() { return &_serialIoConfig; }

//     // QromaCommSerialIo * getSerialCommIo();

//   private:
//     // QromaCommSerialIo<1000, QromaBase64BracketBoundedPbProcessor, &Serial> _qromaCommSerialIo;
//     QromaCommSerialIo<1000, QromaBase64NewLineDelimitedPbProcessor, &Serial> _qromaCommSerialIo;

//     QromaCommSerialIoConfig _serialIoConfig = {
//       .baudRate = 115200,
//       .rxBufferSize = 1000
//     };
    
//     // QromaCommSerialIo<1000, QromaBytesPbProcessor, &Serial> _qromaCommSerialIo;
// };


class QromaSerialCommApp: public QromaSerialCommAppBase<1000, QromaBase64NewLineDelimitedPbProcessor, &Serial>
{
  // public:
  //   // QromaSerialCommApp();

  //   // void init(QromaAppConfig * config);
  //   void init();

  //   QromaCommSerialIoConfig * getSerialIoConfigRef() { return &_serialIoConfig; }

  //   // QromaCommSerialIo * getSerialCommIo();

  // private:
  //   // QromaCommSerialIo<1000, QromaBase64BracketBoundedPbProcessor, &Serial> _qromaCommSerialIo;
  //   QromaCommSerialIo<1000, QromaBase64NewLineDelimitedPbProcessor, &Serial> _qromaCommSerialIo;

  //   QromaCommSerialIoConfig _serialIoConfig = {
  //     .baudRate = 115200,
  //     .rxBufferSize = 1000
  //   };
    
    // QromaCommSerialIo<1000, QromaBytesPbProcessor, &Serial> _qromaCommSerialIo;
};


#endif
