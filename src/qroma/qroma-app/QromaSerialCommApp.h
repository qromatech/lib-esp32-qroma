#ifndef QROMA_SERIAL_COMM_APP_H
#define QROMA_SERIAL_COMM_APP_H

#include "QromaSerialCommAppBase.h"
#include "../qroma-comm/processors/QromaPb64NewLineDelimitedProcessor.h"
// #include "../qroma-comm/processors/Qroma2BytesWithLengthAndPbProcessor.h"


class QromaSerialCommApp: public QromaSerialCommAppBase<1000, QromaPb64NewLineDelimitedProcessor, &Serial>
// class QromaSerialCommApp: public QromaSerialCommAppBase<1000, Qroma2BytesWithLengthAndPbProcessor, &Serial>
{
};


#endif
