/*
  LICENSE
  GNU General Public License v3 - see https://www.gnu.org/licenses/gpl-3.0.en.html

  Copyright (c) 2021  Albert Boehmler 
*/

#include <Arduino.h>
#include "qroma/qroma.h"


QromaAppConfig qromaAppConfig = {

};

void setup() {
  startupQroma(&qromaAppConfig);
}

void loop() {
  delay(1000);
}
