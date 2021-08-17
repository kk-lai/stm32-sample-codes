/**************************************************************************
 * Distance measurement sample code using US-100 ultrasonic 
 * distance sensor trigger and echo mode with STM32F103C8 
 * In this sample, library NewPing is being used. NewPing can be found at 
 * https://bitbucket.org/teckel12/arduino-new-ping/wiki/Home
 * 
 * Written by K.K. Lai 
 * https://my3dev.blogspot.com/
 * 
 * Developed in Arduino IDE 1.8.15 with stm32duino 2.0.0
 * (https://github.com/stm32duino/Arduino_Core_STM32)
 * 
**************************************************************************/

/*
  US-100 pin assignments
  ======================
  +---------------+
  | /-\       /-\ |
  | | |       | | |
  | \-/       \-/ |
  |T    12345    R|                      
  +-----+++++-----+
        |||\\_ GND
        ||\___ Echo / Rx
        |\____ Trig / Tx
        \_____ Vcc 


  Connections
  ===========
  US-100              STM32F103C8
  ======              ===========
  VCC     -----------  3V3
  Trig/Tx -----------  A9
  Echo/Rx -----------  A8
  GND     -----------  G
        
 */
#include <NewPing.h>

#define TRIGGER_PIN  PA9   // any digital pins can be used
#define ECHO_PIN     PA8   // any digital pins can be used
#define MAX_DISTANCE 200   // maximum distance in centimeters

NewPing sensor(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE); // NewPing setup of pins and maximum distance.

void setup() {
    Serial.begin(115200);
    while (!Serial) {
        ; // wait for serial port to connect. Needed for native USB
    }    
    Serial.println("Start");
}

void loop() {
    Serial.print("Distance: ");
    Serial.print(sensor.ping_cm());  
    Serial.println("cm");    
    delay(50);
}
