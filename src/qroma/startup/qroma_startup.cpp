#include "qroma_startup.h"
#include "../qroma-app/QromaApp.h"
#include "../qroma-app/QromaSerialCommApp.h"
#include "../qroma-app/QromaAppConfig.h"


void _startupQroma(QromaApp * qromaApp) {

  setQromaApp(qromaApp);
  qromaApp->init();


  // QromaSerial * qromaSerial = qromaApp->initSerial();
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


void startupQroma(QromaSerialCommApp * app) {
  _startupQroma(app);
}
