/**************************************************************************
 * Distance measurement sample code using US-100 ultrasonic 
 * distance sensor trigger and echo mode with STM32F103C8 
 * In this sample,the HardwareTimer is being used. Timer1 channel 1 captures
 * the count at the rising edge of echo pin. Timer1 channel 2 capture the
 * count at the falling edge. The difference between 2 counts is the round 
 * trip time in microseconds.
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

#define TRIGGER_PIN PA9
#define ECHO_PIN    PA8

HardwareTimer timer1(TIM1);

uint32_t cnt;
bool isOverflow;

void echoRisingEvent()
{
    cnt=timer1.getCaptureCompare(1);
}

void echoFallingEvent()
{
    cnt=timer1.getCaptureCompare(2)-cnt;
    timer1.pause();
    Serial.print("Distance:");
    if (isOverflow) {
        Serial.println("Overflow");
    } else {
        // cnt => round trip time in microsecond
        // distance = (cnt / 2) * (speed of sound) / 1000000
        //          = cnt * (speed of sound / 2000000)    ; speed of sound = 340000 mm/s
        //          = cnt * (340000/2000000) = cnt * 17/100   
        uint32_t distance = cnt * 17/100;     
        Serial.print(distance);
        Serial.println("mm");    
    }
}

void overflowEvent()
{
    isOverflow=true;
}

void setup() {
    pinMode(TRIGGER_PIN,OUTPUT);
    digitalWrite(TRIGGER_PIN,LOW);
    Serial.begin(115200);
    while (!Serial) {
        ; // wait for serial port to connect. Needed for native USB
    }
    Serial.println("Start");
    Serial.flush();
    timer1.pause();
    uint32_t clkFreq = timer1.getTimerClkFreq();    
    timer1.setPrescaleFactor(clkFreq/1000000); // set each count to 1 microsecond
    timer1.setMode(1,TIMER_INPUT_CAPTURE_RISING,ECHO_PIN);
    timer1.setMode(2,TIMER_INPUT_CAPTURE_FALLING,NC);
    timer1.attachInterrupt(1,echoRisingEvent);
    timer1.attachInterrupt(2,echoFallingEvent);
    timer1.attachInterrupt(overflowEvent);
    TIM_IC_InitTypeDef config;
    config.ICPolarity=TIM_INPUTCHANNELPOLARITY_FALLING;
    config.ICSelection=TIM_ICSELECTION_INDIRECTTI;
    config.ICPrescaler = TIM_ICPSC_DIV1;
    config.ICFilter=0;
    HAL_TIM_IC_ConfigChannel(timer1.getHandle(), &config, TIM_CHANNEL_2);
    timer1.refresh();
}

void loop() {
    timer1.setCount(0);
    timer1.refresh();
    digitalWrite(TRIGGER_PIN,HIGH);
    delayMicroseconds(10);
    digitalWrite(TRIGGER_PIN,LOW);
    isOverflow=false;   
    timer1.resume();
    delay(500);
}
