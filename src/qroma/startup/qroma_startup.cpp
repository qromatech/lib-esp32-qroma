#include "qroma_startup.h"
#include "../qroma-app/QromaApp.h"
#include "../qroma-app/QromaSerialCommApp.h"
#include "../qroma-app/QromaAppConfig.h"


// void startupQroma(QromaDeviceDefaults * deviceDefaults, QromaPointInitializer * qromaPointInitializers...) {
// void _startupQroma(QromaAppConfig * appConfig, QromaCommMemBuffer * serialCommMemBuffer, QromaAppConfigFn * myQromaAppConfigFn) {
// void _startupQroma(QromaAppConfig * appConfig, QromaAppConfigFn * myQromaAppConfigFn) {
void _startupQroma(QromaApp * qromaApp) {
  // Serial.println("_startupQroma");

  // initConfigWithDefaultValues(appConfig);

  // appConfig->serialIoConfig.qromaCommMemBuffer = serialCommMemBuffer;

  // if (myQromaAppConfigFn != NULL) {
  //   (*myQromaAppConfigFn)(appConfig);
  // }

  // bool isValidQromaAppConfig = appConfig->validate();
  // if (!isValidQromaAppConfig) {
  //   handleInvalidQromaAppConfig(appConfig);
  //   return;
  // }

  setQromaApp(qromaApp);
  // QromaApp * qromaApp = getQromaApp();
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


// void startupQroma(QromaCommMemBuffer * memBuffer) {
//   QromaAppConfig * qromaAppConfig = getQromaAppConfig();
//   // _startupQroma(qromaAppConfig, memBuffer, NULL);
//   _startupQroma(qromaAppConfig, NULL);
// }


// void startupQroma(QromaCommMemBuffer * memBuffer, QromaAppConfigFn myQromaAppConfigFn) {
//   QromaAppConfig * qromaAppConfig = getQromaAppConfig();
//   // _startupQroma(qromaAppConfig, memBuffer, &myQromaAppConfigFn);
//   _startupQroma(qromaAppConfig, &myQromaAppConfigFn);
// }


// void startupQroma(QromaSerialCommApp * app, QromaAppConfigFn myQromaAppConfigFn) {
//   setQromaApp(app);

//   QromaAppConfig * qromaAppConfig = getQromaAppConfig();
//   _startupQroma(qromaAppConfig, &myQromaAppConfigFn);
// }


void startupQroma(QromaSerialCommApp * app) {
  _startupQroma(app);

  // QromaAppConfig * qromaAppConfig = getQromaAppConfig();
  // _startupQroma(qromaAppConfig, &myQromaAppConfigFn);
}
