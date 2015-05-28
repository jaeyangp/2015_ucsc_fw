//
// UCSC ext.
// 2015 Embedded Firmware Essential
// Project
// Fingerprint Security Lock
// Jae-Yang Park
// jaeyangp@gmail.com
//

#ifndef FINGER_H
#define FINGER_H

Serial debug(USBTX,USBRX);
DigitalOut myled(LED1);

GT511C3 finger(p9,p10);
C12832 LCD(p5, p7, p6, p8, p11);

InterruptIn JOY_CENTER(p14);	
InterruptIn JOY_UP(p15);	
InterruptIn JOY_DOWN(p12);	
InterruptIn JOY_LEFT(p13);	
InterruptIn JOY_RIGHT(p16);	

PwmOut SPEAKER(p26);
PwmOut LEDR(p23);
PwmOut LEDG(p24);
PwmOut LEDB(p25);

Timer debounce;

#endif

