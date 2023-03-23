#include "qroma_startup.h"
#include "../qroma-app/QromaApp.h"
#include "../qroma-app/QromaAppConfig.h"


// void startupQroma(QromaDeviceDefaults * deviceDefaults, QromaPointInitializer * qromaPointInitializers...) {
void _startupQroma(QromaAppConfig * appConfig, QromaCommMemBuffer * serialCommMemBuffer, QromaAppConfigFn * myQromaAppConfigFn) {

  initConfigWithDefaultValues(appConfig);

  appConfig->serialIoConfig.qromaCommMemBuffer = serialCommMemBuffer;

  if (myQromaAppConfigFn != NULL) {
    (*myQromaAppConfigFn)(appConfig);
  }

  bool isValidQromaAppConfig = appConfig->validate();
  if (!isValidQromaAppConfig) {
    handleInvalidQromaAppConfig(appConfig);
    return;
  }

  QromaApp * qromaApp = getQromaApp();
  qromaApp->init(appConfig);


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


void startupQroma(QromaCommMemBuffer * memBuffer) {
  QromaAppConfig * qromaAppConfig = getQromaAppConfig();
  _startupQroma(qromaAppConfig, memBuffer, NULL);
}


void startupQroma(QromaCommMemBuffer * memBuffer, QromaAppConfigFn myQromaAppConfigFn) {
  QromaAppConfig * qromaAppConfig = getQromaAppConfig();
  _startupQroma(qromaAppConfig, memBuffer, &myQromaAppConfigFn);
}
