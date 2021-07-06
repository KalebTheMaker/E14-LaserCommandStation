#ifndef LCS_RELAY_LIB_H
#define LCS_RELAY_LIB_H

#include <Arduino.h>
#include <Adafruit_NeoPixel.h>

class LCS_Relay {
  public:
    LCS_Relay(Adafruit_NeoPixel& lights, int relay_pin, int switch_pin, int light_num);
    void update();
    void on();
    void off();
    bool getState();
  private:
    int _relay_pin;
    int _switch_pin;
    int _light_num;
    Adafruit_NeoPixel _lights;
    bool _state;
    int getDigitalState();
};

#endif