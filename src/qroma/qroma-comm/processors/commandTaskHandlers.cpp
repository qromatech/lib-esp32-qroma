#include "commandTaskHandlers.h"


void taskHandlePbCommandProcessorCommand(void * pvParameters)
{
  QromaBytesProcessor * qbp = (QromaBytesProcessor*)pvParameters;

  qbp->executeHandler();

  vTaskDelete(NULL);
}

