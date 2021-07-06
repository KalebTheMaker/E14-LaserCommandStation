#include <Arduino.h>
#include "LCS_PressureTransducer.h"

LCS_PressureTransducer::LCS_PressureTransducer(int pin) {
  _inputPin = pin;
  _pressureZero = 99.0;
  _pressureMax = 921.0;
  _maxPSI = 100;

}

void LCS_PressureTransducer::setMaxPSI(int maxPSI) {
  _maxPSI = maxPSI;
}

int LCS_PressureTransducer::getMaxPSI() {
  return _maxPSI;
}

void LCS_PressureTransducer::setCalibration(int pressureZero, int pressureMax) {
  _pressureZero = pressureZero;
  _pressureMax = pressureMax;
}

float LCS_PressureTransducer::getPSI() {
  _pressureValue = analogRead(_inputPin); //reads value from input pin and assigns to variable
  _pressureValue = ((_pressureValue-_pressureZero)*_maxPSI)/(_pressureMax-_pressureZero); //conversion equation to convert analog reading to psi
  return _pressureValue;
}
