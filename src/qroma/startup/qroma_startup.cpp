// #include <stdarg.h>
// #include "qroma_startup.h"
// #include "qroma/qroma.h"
// #include "../bluetooth/bluetooth.h"
// #include "../util/logger.h"
// #include "../util/fs.h"
// #include "../qroma-point/QromaDevice.h"
// #include "../QromaManager.h"
#include "../qroma-app/QromaApp.h"


QromaApp qromaApp = QromaApp();

// void startupQroma(QromaDeviceDefaults * deviceDefaults, QromaPointInitializer * qromaPointInitializers...) {
void startupQroma() {

  QromaSerial * qromaSerial = qromaApp.initSerial();
  // qromaApp.initLogger(qromaSerial);

  
  // initLogger();
  // initFileSystem();

  // va_list argptr;
  // va_start(argptr, qromaPointInitializers);
  // bool initSuccess = getQromaManager()->init(deviceDefaults, argptr, qromaPointInitializers);
  // va_end(argptr);

  // if (!initSuccess) {
  //   logError("UNABLE TO INITIALIZE QROMA DEVICE :(");
  //   return;
  // }

  // NimBLEServer * server = initBluetoothServer(getQromaManager()->getDeviceName());
  // getQromaManager()->persistQromaDeviceManifestAndConfigIfNotAlreadyPersisted();
  // getQromaManager()->loadPersistedQromaDeviceConfigs();
  // getQromaManager()->startupQromaDevice(server);
  // getQromaManager()->startupQromaPoints(server);

  // startBluetoothServer(server);

  // getQromaManager()->doPostStartupWork();

  // logInfo("QROMA STARTUP COMPLETE");
}
