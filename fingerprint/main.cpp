//
// UCSC ext.
// 2015 Embedded Firmware Essential
// Project
// Fingerprint Security Lock
// Jae-Yang Park
// jaeyangp@gmail.com
//
#include "mbed.h"
#include "GT511C3.hpp"
#include "C12832.h"
#include "finger.h"

int progress(int, char *);
void err_beep(void);
void good_beep(void);
void red_on(void);
void green_on(void);
void blue_on(void);
void rgb_off(void);
void init(void);
void disp_GT_info(void);
void chk_Enrolled(int);
void identify(int);
void disp_menu(void);
void enroll_id(int);

void joy_center_ISR(void);
void joy_right_ISR(void);
void joy_left_ISR(void);
void joy_up_ISR(void);
void joy_down_ISR(void);

int progress(int status, char *msg)
{
    debug.printf("%s", msg);
	LCD.cls();
	LCD.locate(0, 2);
    LCD.printf("%s", msg);
	good_beep();

	if (status >= 1 && status <= 100) {
		blue_on();
	}

    return 0;
}

void err_beep(void)
{
	SPEAKER.period(1.0 / 2000.0);
	SPEAKER = 0.5;
	wait(0.1);
	SPEAKER = 0.0;
}

void good_beep(void)
{
	SPEAKER.period(1.0 / 2000.0);
	SPEAKER = 0.8;
	wait(0.1);
	SPEAKER = 0.0;
}

void red_on(void)
{
	LEDR.period(0.001);
	LEDR = 0.8;
	LEDG = 1.0;
	LEDB = 1.0;
}

void green_on(void)
{
	LEDG.period(0.001);
	LEDR = 1.0;
	LEDG = 0.8;
	LEDB = 1.0;
}

void blue_on(void)
{
	LEDB.period(0.001);
	LEDR = 1.0;
	LEDG = 1.0;
	LEDB = 0.8;
}

void rgb_off(void)
{
	LEDR = 1.0;
	LEDG = 1.0;
	LEDB = 1.0;
}

void init(void)
{
    debug.format(8, Serial::None, 1);
    debug.baud(115200);
    debug.printf("Fingerprint reader module \"GT-511C3 / GT-511C31\" test program.\n");

	good_beep();
	rgb_off();

	debug.printf("Build: %s %s\n", __DATE__, __TIME__);
    debug.printf("Open\n");
}

void disp_GT_info(void)
{
    int i;

    debug.printf("FirmwareVersion = %lx\n", finger.FirmwareVersion);
    debug.printf("IsoAreaMaxSize = %ld\n", finger.IsoAreaMaxSize);
    debug.printf("DeviceSerialNumber = ");

    for (i = 0; i < sizeof(finger.DeviceSerialNumber); i++){
        debug.printf("%02X", finger.DeviceSerialNumber[i]);
    }

    debug.printf("\n");
}

void chk_Enrolled(int EnrollID)
{
	if (finger.CheckEnrolled(EnrollID) == 0) {
    	debug.printf("EnrollID(%d) is already enrolled.\nDelete!\n", EnrollID);
		
		LCD.cls();
        LCD.printf("EnrollID(%d) is already enrolled.\nDelete!\n", EnrollID);

        if (finger.DeleteID(EnrollID) == 0){
            debug.printf("Delete OK!\n");
            LCD.printf("Delete OK!\n");
        }
    }
}

void identify(int ID)
{
	debug.printf("Press finger for Identify\n");
	LCD.printf("Press finger for Identify\n");

	finger.WaitPress(1);

	if (finger.Capture(1) != 0) {
		debug.printf("Press finger for Identify\n");
		LCD.cls();
		LCD.printf("Press finger for Identify\n");
	}

	ID = finger.Identify();
	
	debug.printf("ID = %d\n", ID); 
	debug.printf("Remove finger\n");

	if (ID == -1) {
		err_beep();
		red_on();
		
		LCD.cls();
		LCD.locate(0, 2);
		LCD.printf("ID = %d, Not matched!\n", ID); 
	}
	else {
		good_beep();
		green_on();
		
		LCD.cls();
		LCD.locate(0, 2);
		LCD.printf("ID = %d, Matched!\n", ID); 
	}

	LCD.printf("Push [C] to menu\n");

    finger.WaitPress(0);
}

void disp_menu(void)
{
	LCD.cls();
	LCD.locate(0, 2);
	LCD.printf("Fingerprint System v1.0\n");
	LCD.printf("ER[U] VF[D] ID[L] DL[R]\n");
	LCD.printf("Push [C] to Menu\n");
   	finger.CmosLed(0);
}

void enroll_id(int EnrollID)
{
	int sts;
    sts = finger.Open();

	chk_Enrolled(EnrollID);
   	finger.Enroll(EnrollID, progress);
   	finger.CmosLed(1);
	LCD.printf("Push [C] to Menu\n");
}

void delete_id(void)
{
	int i = 0;
	for (i = 0; i < 20; i++) {
   		if (finger.DeleteID(i) == 0) {
			LCD.locate(0, 10);
			LCD.printf("%d deleted\n", i);
		}
		else {
			LCD.locate(0, 10);
			LCD.printf("%d is not found\n", i);
		}

		wait(0.5);
	}
	
	//LCD.printf("All deleted!\n");
	LCD.printf("Push [C] to Menu\n");
}

void joy_center_ISR(void)
{
	disp_menu();
	rgb_off();
   	finger.CmosLed(0);
}

void joy_right_ISR(void)
{
	LCD.cls();
	LCD.locate(0, 2);
	LCD.printf("Delete ID\n");
	delete_id();
}

void joy_left_ISR(void)
{
	LCD.cls();
	LCD.locate(0, 2);
	LCD.printf("Identify ID\n");
   	finger.CmosLed(1);
	identify(EnrollID);
}

void joy_up_ISR(void)
{
	LCD.cls();
	LCD.locate(0, 2);
	LCD.printf("Enroll ID\n");
	enroll_id(EnrollID);
	//identify(EnrollID);
}

void joy_down_ISR(void)
{
	LCD.cls();
	LCD.locate(0, 2);
	LCD.printf("Verify ID\n");
   	finger.CmosLed(1);
	identify(EnrollID);
}

void set_ISR(void)
{
	JOY_CENTER.rise(&joy_center_ISR);
	JOY_RIGHT.rise(&joy_right_ISR);
	JOY_LEFT.rise(&joy_left_ISR);
	JOY_UP.rise(&joy_up_ISR);
	JOY_DOWN.rise(&joy_down_ISR);
}

int main() 
{
    int sts = 0;
    int ID = 0;

	init();
	disp_menu();
	set_ISR();

    sts = finger.Open();
    debug.printf("sts = %d\n", sts);

    if (sts == 0) disp_GT_info();

	//chk_Enrolled(EnrollID);
}
