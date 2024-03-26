#include "QromaSerialCommApp.h"
#include <qroma/util/qroma-persist.h>


QromaSerialCommApp * _gQromaSerialCommApp;

QromaSerialCommApp * getQromaSerialCommApp() {
  return _gQromaSerialCommApp;
}


void setQromaSerialCommApp(QromaSerialCommApp * qromaApp) {
  _gQromaSerialCommApp = qromaApp;
}


void QromaSerialCommApp::startupQroma() {
  setQromaApp(this);
  setQromaSerialCommApp(this);
  init();
  _nextHeartbeatSendTimeInMs = 0;
  _numHeartbeatTicks = 0;
}


bool QromaSerialCommApp::tick() {
  
  bool waitedConfiguredDelay = false;
  
  if (_qromaCoreConfig.has_managementConfig && _qromaCoreConfig.managementConfig.projectLoopDelayInMs >= 10) {
    // logInfoUintWithDescription("QROMA APP PRE-DELAY - ", _qromaCoreConfig.managementConfig.projectLoopDelayInMs);
    delay(_qromaCoreConfig.managementConfig.projectLoopDelayInMs);
    // logInfo("QROMA APP POST-DELAY");
    waitedConfiguredDelay = true;
  } else {
    delay(100);
    logInfo("QROMA APP UNABLE TO SUCCESSFULLY TICK - DELAYING 100 MS");
  }

  // I would think calling the parent class version of tick() would just work, but it doesn't - core panic instead. Meh... :|
  //   - causes Guru Meditation Error: Core  0 panic'ed (Load access fault). Exception was unhandled.
  // QromaApp::tick();

  _doTickStuff();

  return waitedConfiguredDelay;
}


void QromaSerialCommApp::_doTickStuff() {
  if (_qromaCoreConfig.has_managementConfig) {

    if (_qromaCoreConfig.managementConfig.has_heartbeatConfiguration) {
      switch (_qromaCoreConfig.managementConfig.heartbeatConfiguration.heartbeatType) {
        case HeartbeatType_HeartbeatType_Interval:
          _sendHeartbeatResponse();
          break;
        default:
          // nothing to do
          break;
      }
    }
  }
}


void QromaSerialCommApp::_sendHeartbeatResponse() {
  uint32_t now = millis();

  if ( now < _nextHeartbeatSendTimeInMs) {
    return;
  }

  _numHeartbeatTicks++;

  QromaCoreResponse response = QromaCoreResponse_init_zero;
  response.which_response = QromaCoreResponse_heartbeat_tag;

  response.response.heartbeat.uptimeInMs = now;
  response.response.heartbeat.heartbeatTicks = _numHeartbeatTicks;

  _qromaCommSerialIo.sendQromaCoreResponse(&response);

  _nextHeartbeatSendTimeInMs = now + _qromaCoreConfig.managementConfig.heartbeatConfiguration.heartbeatIntervalInMs;
}


bool QromaSerialCommApp::saveDefaultQromaCoreConfig() {
  if (!doesFileExist(QROMA_CORE_CONFIG_FILENAME)) {
    bool saved = saveQromaCoreConfig();
    return saved;
  }
  return true;
}


bool QromaSerialCommApp::saveQromaCoreConfig() {
  bool saved = savePbToPersistence(&_qromaCoreConfig, QROMA_CORE_CONFIG_FILENAME, QromaCoreConfig_fields);
  return saved;
}
