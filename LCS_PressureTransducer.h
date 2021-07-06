#ifndef LCS_PRESSURETRANSDUCER_LIB_H
#define LCS_PRESSURETRANSDUCER_LIB_H

#include <Arduino.h>

class LCS_PressureTransducer {
  public:
    LCS_PressureTransducer(int pin);
    void setMaxPSI(int maxPSI);
    int getMaxPSI();
    void setCalibration(int pressureZero, int pressureMax);
    float getPSI();

  private:
    int _inputPin;
    int _maxPSI;
    int _pressureZero;
    int _pressureMax;
    float _pressureValue;
};

#endif
