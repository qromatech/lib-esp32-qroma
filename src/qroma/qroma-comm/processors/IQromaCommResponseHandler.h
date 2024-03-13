#ifndef QROMA_COMM_RESPONSE_HANDLER_H
#define QROMA_COMM_RESPONSE_HANDLER_H


class IQromaCommResponseHandler {
  public:
    virtual bool sendQromaCommResponse(QromaCommResponse * qromaCommResponse, std::function<void(uint8_t*, uint32_t)> txFn);
};

#endif
