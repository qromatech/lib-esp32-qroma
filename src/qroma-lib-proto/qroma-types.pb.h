/* Automatically generated nanopb header */
/* Generated by nanopb-0.4.5 */

#ifndef PB_QROMA_TYPES_PB_H_INCLUDED
#define PB_QROMA_TYPES_PB_H_INCLUDED
#include <pb.h>

#if PB_PROTO_HEADER_VERSION != 40
#error Regenerate this file with the current version of nanopb generator.
#endif

/* Enum definitions */
typedef enum _Qroma_LogLevel { 
    Qroma_LogLevel_LogLevel_All = 0, 
    Qroma_LogLevel_LogLevel_Info = 10, 
    Qroma_LogLevel_LogLevel_Error = 100, 
    Qroma_LogLevel_LogLevel_Nothing = 255 
} Qroma_LogLevel;

typedef enum _Qroma_DebugCommMode { 
    Qroma_DebugCommMode_DebugCommMode_NotSet = 0, 
    Qroma_DebugCommMode_DebugCommMode_None = 1, 
    Qroma_DebugCommMode_DebugCommMode_SerialOnly = 2, 
    Qroma_DebugCommMode_DebugCommMode_BluetoothOnly = 3, 
    Qroma_DebugCommMode_DebugCommMode_SerialAndBluetooth = 4 
} Qroma_DebugCommMode;

/* Struct definitions */
typedef struct _FileData { 
    char filename[32]; 
    uint32_t filesize; 
    uint32_t checksum; 
} FileData;

typedef struct _Qroma_LogMessage { 
    uint32_t tick; 
    char message[60]; 
} Qroma_LogMessage;


/* Helper constants for enums */
#define _Qroma_LogLevel_MIN Qroma_LogLevel_LogLevel_All
#define _Qroma_LogLevel_MAX Qroma_LogLevel_LogLevel_Nothing
#define _Qroma_LogLevel_ARRAYSIZE ((Qroma_LogLevel)(Qroma_LogLevel_LogLevel_Nothing+1))

#define _Qroma_DebugCommMode_MIN Qroma_DebugCommMode_DebugCommMode_NotSet
#define _Qroma_DebugCommMode_MAX Qroma_DebugCommMode_DebugCommMode_SerialAndBluetooth
#define _Qroma_DebugCommMode_ARRAYSIZE ((Qroma_DebugCommMode)(Qroma_DebugCommMode_DebugCommMode_SerialAndBluetooth+1))


#ifdef __cplusplus
extern "C" {
#endif

/* Initializer values for message structs */
#define Qroma_LogMessage_init_default            {0, ""}
#define FileData_init_default                    {"", 0, 0}
#define Qroma_LogMessage_init_zero               {0, ""}
#define FileData_init_zero                       {"", 0, 0}

/* Field tags (for use in manual encoding/decoding) */
#define FileData_filename_tag                    1
#define FileData_filesize_tag                    2
#define FileData_checksum_tag                    3
#define Qroma_LogMessage_tick_tag                1
#define Qroma_LogMessage_message_tag             2

/* Struct field encoding specification for nanopb */
#define Qroma_LogMessage_FIELDLIST(X, a) \
X(a, STATIC,   SINGULAR, UINT32,   tick,              1) \
X(a, STATIC,   SINGULAR, STRING,   message,           2)
#define Qroma_LogMessage_CALLBACK NULL
#define Qroma_LogMessage_DEFAULT NULL

#define FileData_FIELDLIST(X, a) \
X(a, STATIC,   SINGULAR, STRING,   filename,          1) \
X(a, STATIC,   SINGULAR, UINT32,   filesize,          2) \
X(a, STATIC,   SINGULAR, UINT32,   checksum,          3)
#define FileData_CALLBACK NULL
#define FileData_DEFAULT NULL

extern const pb_msgdesc_t Qroma_LogMessage_msg;
extern const pb_msgdesc_t FileData_msg;

/* Defines for backwards compatibility with code written before nanopb-0.4.0 */
#define Qroma_LogMessage_fields &Qroma_LogMessage_msg
#define FileData_fields &FileData_msg

/* Maximum encoded size of messages (where known) */
#define FileData_size                            45
#define Qroma_LogMessage_size                    67

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif
