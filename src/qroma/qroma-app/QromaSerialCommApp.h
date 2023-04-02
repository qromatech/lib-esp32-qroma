#ifndef QROMA_SERIAL_COMM_APP_H
#define QROMA_SERIAL_COMM_APP_H

// #include "QromaApp.h"
// #include "QromaAppConfig.h"
// #include "../qroma-comm/io/QromaCommSerialIo.h"
// #include "../qroma-comm/pipeline/processors/QromaBytesPbProcessor.h"
#include "QromaSerialCommAppBase.h"
#include "../qroma-comm/pipeline/processors/QromaBase64NewLineDelimitedPbProcessor.h"



class QromaSerialCommApp: public QromaSerialCommAppBase<1000, QromaBase64NewLineDelimitedPbProcessor, &Serial>
{
};


#endif
