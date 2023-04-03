#include "qroma-comm.h"


void qromaAppSerialPrint(const char * message, IQromaSerialCommApp * app) {
  app->getSerialTx()->print(message);
}

void qromaAppSerialPrintln(const char * message, IQromaSerialCommApp * app) {
  app->getSerialTx()->println(message);
}
