# US-100-trigger-echo-mode-hwtimer-test

US-100 is an ultrasonic distance sensor which can be used to measure distance between 2cm to 450cm. 
In this example, Trigger Echo mode of US-100 is used.

The program sends a high pulse on the trigger pin, US-100 measures the distance and returns a 
high pulse on the echo pin where the pulse width is proportional to the distance measured. The pulse 
width is measured by a hardware timer of STM32.

In the rising edge of the echo pin, the program captures the count of the timer. In the falling 
edge of the echo pin, the program captures the count of the timer again. The difference between 
2 counts is the pulse width in microsecond. The distance in precision of mm is calculated from the count.

