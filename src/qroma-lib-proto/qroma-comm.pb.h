/* Automatically generated nanopb header */
/* Generated by nanopb-0.4.5 */

#ifndef PB_QROMA_COMM_PB_H_INCLUDED
#define PB_QROMA_COMM_PB_H_INCLUDED
#include <pb.h>
#include "file-system-commands.pb.h"

#if PB_PROTO_HEADER_VERSION != 40
#error Regenerate this file with the current version of nanopb generator.
#endif

/* Struct definitions */
typedef struct _ClearToSendQuery { 
    uint32_t ctsRandomValue; 
} ClearToSendQuery;

typedef struct _ClearToSendResponse { 
    uint32_t ctsRandomValue; 
} ClearToSendResponse;

typedef struct _QromaCommHeader { 
    int32_t messageSize; 
} QromaCommHeader;

typedef struct _QromaCommCommand { 
    pb_size_t which_command;
    union {
        FileSystemCommand fsCommand;
        ClearToSendQuery clearToSendQuery;
    } command; 
} QromaCommCommand;

typedef struct _QromaCommResponse { 
    pb_size_t which_response;
    union {
        FileSystemResponse fsResponse;
        ClearToSendResponse clearToSendResponse;
    } response; 
} QromaCommResponse;


#ifdef __cplusplus
extern "C" {
#endif

/* Initializer values for message structs */
#define ClearToSendQuery_init_default            {0}
#define ClearToSendResponse_init_default         {0}
#define QromaCommCommand_init_default            {0, {FileSystemCommand_init_default}}
#define QromaCommResponse_init_default           {0, {FileSystemResponse_init_default}}
#define QromaCommHeader_init_default             {0}
#define ClearToSendQuery_init_zero               {0}
#define ClearToSendResponse_init_zero            {0}
#define QromaCommCommand_init_zero               {0, {FileSystemCommand_init_zero}}
#define QromaCommResponse_init_zero              {0, {FileSystemResponse_init_zero}}
#define QromaCommHeader_init_zero                {0}

/* Field tags (for use in manual encoding/decoding) */
#define ClearToSendQuery_ctsRandomValue_tag      1
#define ClearToSendResponse_ctsRandomValue_tag   1
#define QromaCommHeader_messageSize_tag          1
#define QromaCommCommand_fsCommand_tag           1
#define QromaCommCommand_clearToSendQuery_tag    5
#define QromaCommResponse_fsResponse_tag         1
#define QromaCommResponse_clearToSendResponse_tag 4

/* Struct field encoding specification for nanopb */
#define ClearToSendQuery_FIELDLIST(X, a) \
X(a, STATIC,   SINGULAR, UINT32,   ctsRandomValue,    1)
#define ClearToSendQuery_CALLBACK NULL
#define ClearToSendQuery_DEFAULT NULL

#define ClearToSendResponse_FIELDLIST(X, a) \
X(a, STATIC,   SINGULAR, UINT32,   ctsRandomValue,    1)
#define ClearToSendResponse_CALLBACK NULL
#define ClearToSendResponse_DEFAULT NULL

#define QromaCommCommand_FIELDLIST(X, a) \
X(a, STATIC,   ONEOF,    MESSAGE,  (command,fsCommand,command.fsCommand),   1) \
X(a, STATIC,   ONEOF,    MESSAGE,  (command,clearToSendQuery,command.clearToSendQuery),   5)
#define QromaCommCommand_CALLBACK NULL
#define QromaCommCommand_DEFAULT NULL
#define QromaCommCommand_command_fsCommand_MSGTYPE FileSystemCommand
#define QromaCommCommand_command_clearToSendQuery_MSGTYPE ClearToSendQuery

#define QromaCommResponse_FIELDLIST(X, a) \
X(a, STATIC,   ONEOF,    MESSAGE,  (response,fsResponse,response.fsResponse),   1) \
X(a, STATIC,   ONEOF,    MESSAGE,  (response,clearToSendResponse,response.clearToSendResponse),   4)
#define QromaCommResponse_CALLBACK NULL
#define QromaCommResponse_DEFAULT NULL
#define QromaCommResponse_response_fsResponse_MSGTYPE FileSystemResponse
#define QromaCommResponse_response_clearToSendResponse_MSGTYPE ClearToSendResponse

#define QromaCommHeader_FIELDLIST(X, a) \
X(a, STATIC,   SINGULAR, INT32,    messageSize,       1)
#define QromaCommHeader_CALLBACK NULL
#define QromaCommHeader_DEFAULT NULL

extern const pb_msgdesc_t ClearToSendQuery_msg;
extern const pb_msgdesc_t ClearToSendResponse_msg;
extern const pb_msgdesc_t QromaCommCommand_msg;
extern const pb_msgdesc_t QromaCommResponse_msg;
extern const pb_msgdesc_t QromaCommHeader_msg;

/* Defines for backwards compatibility with code written before nanopb-0.4.0 */
#define ClearToSendQuery_fields &ClearToSendQuery_msg
#define ClearToSendResponse_fields &ClearToSendResponse_msg
#define QromaCommCommand_fields &QromaCommCommand_msg
#define QromaCommResponse_fields &QromaCommResponse_msg
#define QromaCommHeader_fields &QromaCommHeader_msg

/* Maximum encoded size of messages (where known) */
#define ClearToSendQuery_size                    6
#define ClearToSendResponse_size                 6
#define QromaCommCommand_size                    51
#define QromaCommHeader_size                     11
#if defined(FileSystemResponse_size)
#define QromaCommResponse_size                   (0 + sizeof(union QromaCommResponse_response_size_union))
union QromaCommResponse_response_size_union {char f0[8]; char f1[(6 + FileSystemResponse_size)];};
#endif

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif
