#ifndef EFFECTS_H
#define EFFECTS_H

#include "Arduino.h"

void setupLeds();
void setupButton();
void checkButtonPress();
void switchEffect();
void turnOff();
void setLedsIntensity(int intensity);
void intercalateLed();
void fadeLeds();

#endif