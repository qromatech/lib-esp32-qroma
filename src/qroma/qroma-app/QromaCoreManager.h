#ifndef QROMA_CORE_MANAGER_H
#define QROMA_CORE_MANAGER_H

#include <qroma/util/logger.h>
#include <qroma-lib-proto/qroma-core.pb.h>


class QromaCoreManager {
  public:
    void initQromaCoreConfigDefaults(QromaCoreConfig * config);

    void applyQromaCoreConfig(QromaCoreConfig * config);
    void populateQromaCoreConfig(QromaCoreConfig * dstConfig, QromaCoreConfig * srcConfig);

  private:
    // QromaCoreConfig _coreConfig;
  
};


// const QromaCoreManager * getQromaCoreManager();

#endif
