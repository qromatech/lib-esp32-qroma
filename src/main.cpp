/*
  LICENSE
  GNU General Public License v3 - see https://www.gnu.org/licenses/gpl-3.0.en.html

  Copyright (c) 2021  Albert Boehmler 
*/

#include <Arduino.h>
#include "qroma/qroma.h"

#define COMM_BUFFER_SIZE 100
uint8_t _commBuffer[COMM_BUFFER_SIZE];
QromaCommMemBuffer qcMemBuffer = QromaCommMemBuffer(_commBuffer, COMM_BUFFER_SIZE);


void setup() {
  startupQroma(&qcMemBuffer);
}

void loop() {
  delay(1000);
}
