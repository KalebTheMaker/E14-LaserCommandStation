/*
###############################################################################
## File: LaserControlSystem.ino
## Desc: Main Arduino program for Laser Control System
## Project: LaserControlSystem for Element14 Presents
## License: 
##
## By: Kaleb Clark (KalebTheMaker)
###############################################################################
*/
#include <Adafruit_NeoPixel.h>
#include "LCS_PressureTransducer.h"
#include "LCS_Relay.h"

#ifdef __AVR__
  #include <avr/power.h>
#endif

// Defines
#define LED_PIN   40
#define LED_CNT   10
#define FLOW_PIN  2
#define AIR_PIN   A2

// Instantiations
Adafruit_NeoPixel lights(LED_CNT, LED_PIN, NEO_GRB + NEO_KHZ800);
LCS_PressureTransducer airflow(AIR_PIN);
LCS_Relay relay_machine(lights,     29, 32, 7); // Machine Power
LCS_Relay relay_chiller(lights,     25, 33, 6); // Water Chiller
LCS_Relay relay_air_assist(lights,  27, 37, 1); // Air Assist
LCS_Relay relay_exhaust(lights,     28, 35, 4); // Exhaust Fan
LCS_Relay relay_computer(lights,    24, 36, 0); // Computer
LCS_Relay relay_aux0(lights,        23, 34, 5); // Aux 01
LCS_Relay relay_aux1(lights,        22, 38, 2); // Aux 02
LCS_Relay relay_aux2(lights,        26, 39, 3); // Aux 03


// Global Variables
unsigned long prev_time;
int main_loop_delay = 250;
int flow_threshold = 4;
float air_threshold = 1.0;
volatile byte pulse_count;
float psi;

void setup() {
  Serial.begin(115200);

  // Lights Setup
  lights.begin();
  lights.show();
  lights.setBrightness(255);

  // Flow Sensor Setup
  pinMode(FLOW_PIN, INPUT_PULLUP);
  digitalWrite(FLOW_PIN, HIGH);
  pulse_count = 0;
  prev_time = 0;
  attachInterrupt(digitalPinToInterrupt(FLOW_PIN), pulseCounter, RISING);
  
  Serial.println("Boot Sequence Complete");
}

void loop() {
  // Water Flow Timer
  if((millis() - prev_time) > main_loop_delay) {
    detachInterrupt(digitalPinToInterrupt(FLOW_PIN));
    Serial.print("PulseCount: ");
    Serial.println(pulse_count);


    // Change light color if pulse_count is greater than
    // the threshold value. 
    if(pulse_count == 0) {
      lights.setPixelColor(8, lights.Color(255, 0, 0));
      lights.show();
    } else if(pulse_count > flow_threshold) {
      lights.setPixelColor(8, lights.Color(0, 255, 0));
      lights.show();
    }

    prev_time = millis();
    pulse_count = 0;
    attachInterrupt(digitalPinToInterrupt(FLOW_PIN), pulseCounter, RISING);
  }

  // Check Air Pressure
  psi = airflow.getPSI();
  if(psi < 1) {
    lights.setPixelColor(9, lights.Color(255,0,0));
    lights.show();
  } else if(psi > air_threshold) {
    lights.setPixelColor(9, lights.Color(0, 255, 0));
    lights.show();
  }

  // Switch/Relay Updates
  relay_machine.update();
  relay_chiller.update();
  relay_air_assist.update();
  relay_exhaust.update();
  relay_computer.update();
  relay_aux0.update();
  relay_aux1.update();
  relay_aux2.update();
}

void pulseCounter()
{
  pulse_count++;
}
