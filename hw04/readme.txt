Debug with CMSIS-DAP

What is CMSIS-DAP?
“CMSIS-DAP provides a standardized way to access the Coresight Debug Access Port (DAP) of an ARM Cortex microcontroller via USB. CMSIS-DAP is generally implemented as an on-board interface chip, providing direct USB connection from a development board to a debugger running on a host computer on one side, and over JTAG (Joint Test Action Group) or SWD (Serial Wire Debug) to the target device to access the Coresight DAP on the other.”
ref: http://developer.mbed.org/handbook/CMSIS-DAP

Goal: Pick one method to debug your mbed program. https://github.com/Shengliang/e4357/blob/master/fall2014/quiz/Q4.txt
(Hint: use debugger to find out the quiz.4.question.5 answers.)

Method 1: Keil MDK
http://developer.mbed.org/handbook/CMSIS-DAP-MDK
http://www.keil.com/appnotes/files/apnt207.pdf

Method 2: pyOCD
https://github.com/mbedmicro/pyOCD

Reading: An Embedded Software Primer Chapter 5
http://en.wikibooks.org/wiki/Embedded_Systems

