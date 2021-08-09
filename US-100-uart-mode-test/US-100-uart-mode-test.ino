/**************************************************************************
 * Distance measurement sample code using US-100 ultrasonic 
 * distance sensor communicate with STM32F103C8 UART interface
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
  Echo/Rx -----------  A10
  GND     -----------  G

  Arduino IDE Board Settings
  ==========================
  Board: Generic STM32F1 series
  Board part number: BluePill F103C8
  U(S)ART support: Enabled (generic Serial)
  USB support: CDC (generic Serial supersede U(S)ART)
  
 */
#define sensor Serial1

void setup() {
    // uncomment below lines to use B6,B7 for TX1, RX1
    /*
    sensor.setTx(PB6);
    sensor.setRx(PB7);
    */
    // uncomment below lines to use A2, A3 as TX, RX
    /*
    sensor.setTx(PA2);
    sensor.setRx(PA3);
    */
    // uncomment below lines to use B10, B11 as TX, RX
    /*
    sensor.setTx(PB10);
    sensor.setRx(PB11);     
    */
    sensor.begin(9600);
    Serial.begin(115200);    
    Serial.println("Start");    

}

void loop() {  
    // send 0x55 to start distance measurement
    sensor.write(0x55);    
    // Max measureable distance = 450cm
    // round trip time = (450cm * 2)/(speed of sound) = 9/343 = 0.02624 sec (26.24ms)
    // time required for transmitting 2 bytes result => 2*(1 start bit + 8 data bits + 1 stop bits)/9600bps = 20/9600 = 2.083ms
    // time required for US-100 to response = 26.24+2.083 = 28.323 ms  
    delay(50); // add additional time for sensor to process
    if (sensor.available()>=2) {
        int len=0;
        len=len | (sensor.read() << 8);
        len=len | sensor.read();
        Serial.print("Distance:");
        Serial.print(len,DEC);
        Serial.println("mm");        
    }    
}
