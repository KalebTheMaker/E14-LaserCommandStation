#include <Arduino.h>
#include "LCS_Relay.h"

LCS_Relay::LCS_Relay(Adafruit_NeoPixel& lights, int relay_pin, int switch_pin, int light_num) {
  _relay_pin  = relay_pin;
  _switch_pin = switch_pin;
  _light_num  = light_num;
  _lights     = lights;
  pinMode(_relay_pin, OUTPUT);
  pinMode(_switch_pin, INPUT_PULLUP);

}
void LCS_Relay::update() {
  if(digitalRead(_switch_pin) == 0) {
    digitalWrite(_relay_pin, HIGH);
    _lights.setPixelColor(_light_num, _lights.Color(0, 255, 0));
    _lights.show();
    _state = true;
  } else {
    digitalWrite(_relay_pin, LOW);
    _lights.setPixelColor(_light_num, _lights.Color(255, 0, 0));
    _lights.show();
    _state = false;
  }
}

void LCS_Relay::on() {
  digitalWrite(_relay_pin, HIGH);
  _state = getDigitalState();
}

void LCS_Relay::off() {
  digitalWrite(_relay_pin, LOW);
  _state = getDigitalState();
}

bool LCS_Relay::getState() {
  return getDigitalState();
}

int LCS_Relay::getDigitalState() {
  uint8_t bit = digitalPinToBitMask(_relay_pin);
  uint8_t port = digitalPinToPort(_relay_pin);
  if (port == NOT_A_PIN) {
    return LOW;
  }

  return (*portOutputRegister(port) & bit) ? HIGH : LOW;
}