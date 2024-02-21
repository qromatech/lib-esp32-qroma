#ifndef QROMA_COMM_STREAM_RX_HANDLER_H
#define QROMA_COMM_STREAM_RX_HANDLER_H


class IQromaCommStreamRxHandler {
  public:
    virtual void startStreamReadingMode() = 0;
    virtual void endStreamReadingMode() = 0;
    virtual bool sendQromaCommResponse(QromaCommResponse * qromaCommResponse, std::function<void(uint8_t*, uint32_t)> txFn);
};

#endif
