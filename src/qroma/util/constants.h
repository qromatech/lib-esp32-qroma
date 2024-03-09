#ifndef QROMA_CONSTANTS_H
#define QROMA_CONSTANTS_H


#define MS_1 1 / portTICK_PERIOD_MS   //vTaskDelay
#define MS_5 5 / portTICK_PERIOD_MS   //vTaskDelay
#define MS_10 10 / portTICK_PERIOD_MS   //vTaskDelay
#define MS_20 20 / portTICK_PERIOD_MS   //vTaskDelay
#define MS_25 25 / portTICK_PERIOD_MS   //vTaskDelay
#define MS_50 50 / portTICK_PERIOD_MS   //vTaskDelay
#define MS_100 100 / portTICK_PERIOD_MS   //vTaskDelay
#define MS_1000 1000 / portTICK_PERIOD_MS   //vTaskDelay

#define QROMA_COMM_SERVICE_UUID                   "211f838d-7c01-4798-a456-da93a2c5f469"

#define PB_SERIAL_TX_CHARACTERISTIC_UUID          "774806b9-763d-4530-a060-c24b74b3d07c"
#define PB_SERIAL_RX_CHARACTERISTIC_UUID          "89603a42-457d-45e5-bc6d-1a27a6a3bda1"

#define DEFAULT_QC_TX_INTERVAL_IN_MS 25
#define DEFAULT_QC_TX_MAX_MESSAGE_SIZE_IN_BYTES 20



#endif