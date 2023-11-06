#ifndef QROMA_PB64_NEWLINE_DELIMITED_PROCESSOR_H
#define QROMA_PB64_NEWLINE_DELIMITED_PROCESSOR_H

#include <pb.h>
#include "IQromaNewBytesProcessor.h"
#include <qroma-lib-proto/qroma-comm.pb.h>
#include <qroma/util/logger.h>
#include <qroma/util/qbase64.h>
#include <pb_decode.h>
#include <pb_encode.h>
#include "QromaFsCommandProcessor.h"
#include "QromaCommConfigProcessor.h"
#include "IAppCommandProcessor.h"
#include "QromaCommFileReader.h"


enum QromaCommProcessingMode {
  QromaCommProcessingMode_NotSet,
  QromaCommProcessingMode_QromaCommands,
  QromaCommProcessingMode_FileReader
};


class QromaCommProcessor: public IQromaNewBytesProcessor, 
                                 IQromaFsCommandProcessorListener 
{
  public:
    void init(IAppCommandProcessor * appCommandProcessor);
      
    void reset();

    uint32_t processBytes(const uint8_t * bytes, uint32_t byteCount, std::function<void(const uint8_t*, uint32_t)> txFn);

    uint32_t handleQromaCommCommand(uint8_t * bytes, uint32_t bytesLength, std::function<void(uint8_t*, uint32_t)> txFn);

    void startFileReadingMode(uint32_t silenceDelayTimeoutInMs, FileData * fileData);
    
    void endFileReadingMode();

    bool sendQromaCommResponse(QromaCommResponse * qromaCommResponse, std::function<void(uint8_t*, uint32_t)> txFn);

    template<typename PbMessage, const pb_msgdesc_t *PbMessageFields>
    bool sendQromaAppResponse(PbMessage * qromaAppResponse, std::function<void(uint8_t*, uint32_t)> txFn) {
      QromaCommResponse qcResponse = QromaCommResponse_init_zero;

      pb_ostream_t ostream = pb_ostream_from_buffer(
        qcResponse.response.appResponseBytes.bytes,
        sizeof(qcResponse.response.appResponseBytes.bytes)
      );

      bool encoded = pb_encode(&ostream, PbMessageFields, qromaAppResponse);
      if (!encoded) {
        logError("ERROR sendQromaAppResponse - handleBytes/encode");
        return false;
      }

      qcResponse.response.appResponseBytes.size = ostream.bytes_written;
      qcResponse.which_response = QromaCommResponse_appResponseBytes_tag;

      bool success = sendQromaCommResponse(&qcResponse, txFn);

      logInfo("QromaCommProcessor::sendQromaAppResponse() complete");

      return success;
    }


  private:
    QromaCommProcessingMode _processingMode;

    IAppCommandProcessor * _appCommandProcessor;
    QromaFsCommandProcessor _qromaFsCommandProcessor;
    QromaCommConfigProcessor _qromaCommConfigProcessor;
    QromaCommFileReader _qromaCommFileReader;
   
    unsigned char _base64DecodeBuffer[10000];
    unsigned char _base64EncodeBuffer[10000];
};

#endif
