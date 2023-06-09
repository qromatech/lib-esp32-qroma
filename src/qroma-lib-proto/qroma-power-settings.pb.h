/* Automatically generated nanopb header */
/* Generated by nanopb-0.4.5 */

#ifndef PB_QROMA_POWER_SETTINGS_PB_H_INCLUDED
#define PB_QROMA_POWER_SETTINGS_PB_H_INCLUDED
#include <pb.h>

#if PB_PROTO_HEADER_VERSION != 40
#error Regenerate this file with the current version of nanopb generator.
#endif

/* Enum definitions */
typedef enum _QromaPower_PowerMode { 
    QromaPower_PowerMode_Qpm_NotSet = 0, 
    QromaPower_PowerMode_Qpm_WithoutBattery_NormalOpsVoltage = 1, 
    QromaPower_PowerMode_Qpm_WithBattery_Charging = 2, 
    QromaPower_PowerMode_Qpm_WithBattery_ChargingComplete = 3, 
    QromaPower_PowerMode_Qpm_WithBattery_NormalOpsVoltage = 4, 
    QromaPower_PowerMode_Qpm_WithBattery_LowBatteryVoltage = 5, 
    QromaPower_PowerMode_Qpm_WithBattery_LowBatteryVoltage_StopNormalOps = 6 
} QromaPower_PowerMode;

/* Struct definitions */
typedef struct _QromaPower_Config { 
    uint32_t powerCheckIntervalInMs; 
    float batteryIsChargedThresholdInVolts; 
    float lowBatteryVoltageInVolts; 
    float stopNormalOpsBatteryVoltageInVolts; 
    bool hasOnboardBattery; 
} QromaPower_Config;

typedef struct _QromaPower_DevPowerMode { 
    bool devPowerModeEnabled; 
    QromaPower_PowerMode devPowerMode; 
} QromaPower_DevPowerMode;

typedef struct _QromaPower_Status { 
    QromaPower_PowerMode powerMode; 
    float batteryVoltage; /* bool isBatteryCharging = 3;
 bool isPowerConnected = 4; */
} QromaPower_Status;

typedef struct _SetBatteryIsChargedThresholdInVoltsCommand { 
    float batteryIsChargedThresholdInVolts; 
} SetBatteryIsChargedThresholdInVoltsCommand;

typedef struct _SetHasOnboardBatteryCommand { 
    bool hasOnboardBattery; 
} SetHasOnboardBatteryCommand;

typedef struct _SetLowBatteryVoltageInVoltsCommand { 
    float lowBatteryVoltageInVolts; 
} SetLowBatteryVoltageInVoltsCommand;

typedef struct _SetPowerCheckIntervalInMsCommand { 
    uint32_t powerCheckIntervalInMs; 
} SetPowerCheckIntervalInMsCommand;

typedef struct _SetStopNormalOpsBatteryVoltageInVoltsCommand { 
    float stopNormalOpsBatteryVoltageInVolts; 
} SetStopNormalOpsBatteryVoltageInVoltsCommand;

typedef struct _SetPowerConfigurationCommand { 
    uint32_t powerCheckIntervalInMs; 
    float batteryIsChargedThresholdInVolts; 
    float lowBatteryVoltageInVolts; 
    float stopNormalOpsBatteryVoltageInVolts; 
    bool hasOnboardBattery; 
    bool has_devMode;
    QromaPower_DevPowerMode devMode; 
} SetPowerConfigurationCommand;

typedef struct _QromaPower_Command { 
    pb_size_t which_command;
    union {
        SetPowerConfigurationCommand setPowerConfiguration;
        SetPowerCheckIntervalInMsCommand setPowerCheckIntervalInMs;
        SetBatteryIsChargedThresholdInVoltsCommand setBatteryIsChargedThresholdInVolts;
        SetLowBatteryVoltageInVoltsCommand setLowBatteryVoltageInVolts;
        SetStopNormalOpsBatteryVoltageInVoltsCommand setStopNormalOpsBatteryVoltageInVolts;
        SetHasOnboardBatteryCommand setHasOnboardBattery;
        QromaPower_DevPowerMode setDevPowerMode;
    } command; 
} QromaPower_Command;


/* Helper constants for enums */
#define _QromaPower_PowerMode_MIN QromaPower_PowerMode_Qpm_NotSet
#define _QromaPower_PowerMode_MAX QromaPower_PowerMode_Qpm_WithBattery_LowBatteryVoltage_StopNormalOps
#define _QromaPower_PowerMode_ARRAYSIZE ((QromaPower_PowerMode)(QromaPower_PowerMode_Qpm_WithBattery_LowBatteryVoltage_StopNormalOps+1))


#ifdef __cplusplus
extern "C" {
#endif

/* Initializer values for message structs */
#define QromaPower_DevPowerMode_init_default     {0, _QromaPower_PowerMode_MIN}
#define QromaPower_Config_init_default           {0, 0, 0, 0, 0}
#define QromaPower_Status_init_default           {_QromaPower_PowerMode_MIN, 0}
#define SetPowerCheckIntervalInMsCommand_init_default {0}
#define SetBatteryIsChargedThresholdInVoltsCommand_init_default {0}
#define SetLowBatteryVoltageInVoltsCommand_init_default {0}
#define SetStopNormalOpsBatteryVoltageInVoltsCommand_init_default {0}
#define SetHasOnboardBatteryCommand_init_default {0}
#define SetPowerConfigurationCommand_init_default {0, 0, 0, 0, 0, false, QromaPower_DevPowerMode_init_default}
#define QromaPower_Command_init_default          {0, {SetPowerConfigurationCommand_init_default}}
#define QromaPower_DevPowerMode_init_zero        {0, _QromaPower_PowerMode_MIN}
#define QromaPower_Config_init_zero              {0, 0, 0, 0, 0}
#define QromaPower_Status_init_zero              {_QromaPower_PowerMode_MIN, 0}
#define SetPowerCheckIntervalInMsCommand_init_zero {0}
#define SetBatteryIsChargedThresholdInVoltsCommand_init_zero {0}
#define SetLowBatteryVoltageInVoltsCommand_init_zero {0}
#define SetStopNormalOpsBatteryVoltageInVoltsCommand_init_zero {0}
#define SetHasOnboardBatteryCommand_init_zero    {0}
#define SetPowerConfigurationCommand_init_zero   {0, 0, 0, 0, 0, false, QromaPower_DevPowerMode_init_zero}
#define QromaPower_Command_init_zero             {0, {SetPowerConfigurationCommand_init_zero}}

/* Field tags (for use in manual encoding/decoding) */
#define QromaPower_Config_powerCheckIntervalInMs_tag 1
#define QromaPower_Config_batteryIsChargedThresholdInVolts_tag 2
#define QromaPower_Config_lowBatteryVoltageInVolts_tag 3
#define QromaPower_Config_stopNormalOpsBatteryVoltageInVolts_tag 4
#define QromaPower_Config_hasOnboardBattery_tag  5
#define QromaPower_DevPowerMode_devPowerModeEnabled_tag 1
#define QromaPower_DevPowerMode_devPowerMode_tag 2
#define QromaPower_Status_powerMode_tag          1
#define QromaPower_Status_batteryVoltage_tag     2
#define SetBatteryIsChargedThresholdInVoltsCommand_batteryIsChargedThresholdInVolts_tag 1
#define SetHasOnboardBatteryCommand_hasOnboardBattery_tag 1
#define SetLowBatteryVoltageInVoltsCommand_lowBatteryVoltageInVolts_tag 1
#define SetPowerCheckIntervalInMsCommand_powerCheckIntervalInMs_tag 1
#define SetStopNormalOpsBatteryVoltageInVoltsCommand_stopNormalOpsBatteryVoltageInVolts_tag 1
#define SetPowerConfigurationCommand_powerCheckIntervalInMs_tag 1
#define SetPowerConfigurationCommand_batteryIsChargedThresholdInVolts_tag 2
#define SetPowerConfigurationCommand_lowBatteryVoltageInVolts_tag 3
#define SetPowerConfigurationCommand_stopNormalOpsBatteryVoltageInVolts_tag 4
#define SetPowerConfigurationCommand_hasOnboardBattery_tag 5
#define SetPowerConfigurationCommand_devMode_tag 11
#define QromaPower_Command_setPowerConfiguration_tag 1
#define QromaPower_Command_setPowerCheckIntervalInMs_tag 11
#define QromaPower_Command_setBatteryIsChargedThresholdInVolts_tag 12
#define QromaPower_Command_setLowBatteryVoltageInVolts_tag 13
#define QromaPower_Command_setStopNormalOpsBatteryVoltageInVolts_tag 14
#define QromaPower_Command_setHasOnboardBattery_tag 15
#define QromaPower_Command_setDevPowerMode_tag   20

/* Struct field encoding specification for nanopb */
#define QromaPower_DevPowerMode_FIELDLIST(X, a) \
X(a, STATIC,   SINGULAR, BOOL,     devPowerModeEnabled,   1) \
X(a, STATIC,   SINGULAR, UENUM,    devPowerMode,      2)
#define QromaPower_DevPowerMode_CALLBACK NULL
#define QromaPower_DevPowerMode_DEFAULT NULL

#define QromaPower_Config_FIELDLIST(X, a) \
X(a, STATIC,   SINGULAR, UINT32,   powerCheckIntervalInMs,   1) \
X(a, STATIC,   SINGULAR, FLOAT,    batteryIsChargedThresholdInVolts,   2) \
X(a, STATIC,   SINGULAR, FLOAT,    lowBatteryVoltageInVolts,   3) \
X(a, STATIC,   SINGULAR, FLOAT,    stopNormalOpsBatteryVoltageInVolts,   4) \
X(a, STATIC,   SINGULAR, BOOL,     hasOnboardBattery,   5)
#define QromaPower_Config_CALLBACK NULL
#define QromaPower_Config_DEFAULT NULL

#define QromaPower_Status_FIELDLIST(X, a) \
X(a, STATIC,   SINGULAR, UENUM,    powerMode,         1) \
X(a, STATIC,   SINGULAR, FLOAT,    batteryVoltage,    2)
#define QromaPower_Status_CALLBACK NULL
#define QromaPower_Status_DEFAULT NULL

#define SetPowerCheckIntervalInMsCommand_FIELDLIST(X, a) \
X(a, STATIC,   SINGULAR, UINT32,   powerCheckIntervalInMs,   1)
#define SetPowerCheckIntervalInMsCommand_CALLBACK NULL
#define SetPowerCheckIntervalInMsCommand_DEFAULT NULL

#define SetBatteryIsChargedThresholdInVoltsCommand_FIELDLIST(X, a) \
X(a, STATIC,   SINGULAR, FLOAT,    batteryIsChargedThresholdInVolts,   1)
#define SetBatteryIsChargedThresholdInVoltsCommand_CALLBACK NULL
#define SetBatteryIsChargedThresholdInVoltsCommand_DEFAULT NULL

#define SetLowBatteryVoltageInVoltsCommand_FIELDLIST(X, a) \
X(a, STATIC,   SINGULAR, FLOAT,    lowBatteryVoltageInVolts,   1)
#define SetLowBatteryVoltageInVoltsCommand_CALLBACK NULL
#define SetLowBatteryVoltageInVoltsCommand_DEFAULT NULL

#define SetStopNormalOpsBatteryVoltageInVoltsCommand_FIELDLIST(X, a) \
X(a, STATIC,   SINGULAR, FLOAT,    stopNormalOpsBatteryVoltageInVolts,   1)
#define SetStopNormalOpsBatteryVoltageInVoltsCommand_CALLBACK NULL
#define SetStopNormalOpsBatteryVoltageInVoltsCommand_DEFAULT NULL

#define SetHasOnboardBatteryCommand_FIELDLIST(X, a) \
X(a, STATIC,   SINGULAR, BOOL,     hasOnboardBattery,   1)
#define SetHasOnboardBatteryCommand_CALLBACK NULL
#define SetHasOnboardBatteryCommand_DEFAULT NULL

#define SetPowerConfigurationCommand_FIELDLIST(X, a) \
X(a, STATIC,   SINGULAR, UINT32,   powerCheckIntervalInMs,   1) \
X(a, STATIC,   SINGULAR, FLOAT,    batteryIsChargedThresholdInVolts,   2) \
X(a, STATIC,   SINGULAR, FLOAT,    lowBatteryVoltageInVolts,   3) \
X(a, STATIC,   SINGULAR, FLOAT,    stopNormalOpsBatteryVoltageInVolts,   4) \
X(a, STATIC,   SINGULAR, BOOL,     hasOnboardBattery,   5) \
X(a, STATIC,   OPTIONAL, MESSAGE,  devMode,          11)
#define SetPowerConfigurationCommand_CALLBACK NULL
#define SetPowerConfigurationCommand_DEFAULT NULL
#define SetPowerConfigurationCommand_devMode_MSGTYPE QromaPower_DevPowerMode

#define QromaPower_Command_FIELDLIST(X, a) \
X(a, STATIC,   ONEOF,    MESSAGE,  (command,setPowerConfiguration,command.setPowerConfiguration),   1) \
X(a, STATIC,   ONEOF,    MESSAGE,  (command,setPowerCheckIntervalInMs,command.setPowerCheckIntervalInMs),  11) \
X(a, STATIC,   ONEOF,    MESSAGE,  (command,setBatteryIsChargedThresholdInVolts,command.setBatteryIsChargedThresholdInVolts),  12) \
X(a, STATIC,   ONEOF,    MESSAGE,  (command,setLowBatteryVoltageInVolts,command.setLowBatteryVoltageInVolts),  13) \
X(a, STATIC,   ONEOF,    MESSAGE,  (command,setStopNormalOpsBatteryVoltageInVolts,command.setStopNormalOpsBatteryVoltageInVolts),  14) \
X(a, STATIC,   ONEOF,    MESSAGE,  (command,setHasOnboardBattery,command.setHasOnboardBattery),  15) \
X(a, STATIC,   ONEOF,    MESSAGE,  (command,setDevPowerMode,command.setDevPowerMode),  20)
#define QromaPower_Command_CALLBACK NULL
#define QromaPower_Command_DEFAULT NULL
#define QromaPower_Command_command_setPowerConfiguration_MSGTYPE SetPowerConfigurationCommand
#define QromaPower_Command_command_setPowerCheckIntervalInMs_MSGTYPE SetPowerCheckIntervalInMsCommand
#define QromaPower_Command_command_setBatteryIsChargedThresholdInVolts_MSGTYPE SetBatteryIsChargedThresholdInVoltsCommand
#define QromaPower_Command_command_setLowBatteryVoltageInVolts_MSGTYPE SetLowBatteryVoltageInVoltsCommand
#define QromaPower_Command_command_setStopNormalOpsBatteryVoltageInVolts_MSGTYPE SetStopNormalOpsBatteryVoltageInVoltsCommand
#define QromaPower_Command_command_setHasOnboardBattery_MSGTYPE SetHasOnboardBatteryCommand
#define QromaPower_Command_command_setDevPowerMode_MSGTYPE QromaPower_DevPowerMode

extern const pb_msgdesc_t QromaPower_DevPowerMode_msg;
extern const pb_msgdesc_t QromaPower_Config_msg;
extern const pb_msgdesc_t QromaPower_Status_msg;
extern const pb_msgdesc_t SetPowerCheckIntervalInMsCommand_msg;
extern const pb_msgdesc_t SetBatteryIsChargedThresholdInVoltsCommand_msg;
extern const pb_msgdesc_t SetLowBatteryVoltageInVoltsCommand_msg;
extern const pb_msgdesc_t SetStopNormalOpsBatteryVoltageInVoltsCommand_msg;
extern const pb_msgdesc_t SetHasOnboardBatteryCommand_msg;
extern const pb_msgdesc_t SetPowerConfigurationCommand_msg;
extern const pb_msgdesc_t QromaPower_Command_msg;

/* Defines for backwards compatibility with code written before nanopb-0.4.0 */
#define QromaPower_DevPowerMode_fields &QromaPower_DevPowerMode_msg
#define QromaPower_Config_fields &QromaPower_Config_msg
#define QromaPower_Status_fields &QromaPower_Status_msg
#define SetPowerCheckIntervalInMsCommand_fields &SetPowerCheckIntervalInMsCommand_msg
#define SetBatteryIsChargedThresholdInVoltsCommand_fields &SetBatteryIsChargedThresholdInVoltsCommand_msg
#define SetLowBatteryVoltageInVoltsCommand_fields &SetLowBatteryVoltageInVoltsCommand_msg
#define SetStopNormalOpsBatteryVoltageInVoltsCommand_fields &SetStopNormalOpsBatteryVoltageInVoltsCommand_msg
#define SetHasOnboardBatteryCommand_fields &SetHasOnboardBatteryCommand_msg
#define SetPowerConfigurationCommand_fields &SetPowerConfigurationCommand_msg
#define QromaPower_Command_fields &QromaPower_Command_msg

/* Maximum encoded size of messages (where known) */
#define QromaPower_Command_size                  31
#define QromaPower_Config_size                   23
#define QromaPower_DevPowerMode_size             4
#define QromaPower_Status_size                   7
#define SetBatteryIsChargedThresholdInVoltsCommand_size 5
#define SetHasOnboardBatteryCommand_size         2
#define SetLowBatteryVoltageInVoltsCommand_size  5
#define SetPowerCheckIntervalInMsCommand_size    6
#define SetPowerConfigurationCommand_size        29
#define SetStopNormalOpsBatteryVoltageInVoltsCommand_size 5

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif
