#include "effects.h"

void setup() {
  setupLeds();
  setupButton();

  // salida Serial para debug
  Serial.begin(9600);
}

void loop() {
  checkButtonPress();
  switchEffect();
  //delay(50);
}
