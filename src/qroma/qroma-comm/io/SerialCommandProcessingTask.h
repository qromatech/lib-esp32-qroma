#ifndef SERIAL_COMMAND_PROCESSING_TASK_H
#define SERIAL_COMMAND_PROCESSING_TASK_H

#include <cstdint>

void _doSerialCommandProcessingTask(void *pvParameters);

bool setMsDelayInProcessingLoop(uint32_t msDelay);
uint32_t getMsDelayInProcessingLoop();


#endif
