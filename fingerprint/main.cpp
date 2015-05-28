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
void disp_menu(void);
void chk_Enrolled(int);
void enroll_id(void);
void verify_id(void);
void identify_id(void);
void delete_id(void);
void select_id(void);

void joy_center_ISR(void);
void joy_right_ISR(void);
void joy_left_ISR(void);
void joy_up_ISR(void);
void joy_down_ISR(void);

int EnrollID = 0;
int current = 0;

#define MENU_SZ 6
#define MAX_ID 20

char *menu[] = {"[0] Menu              >>",
			    "[1] Select ID      << >>", 
			    "[2] Enroll ID      << >>",
			    "[3] Verify ID      << >>", 
			    "[4] Identify ID    << >>", 
			    "[5] Delete ID      <<   "};

void (*ptr_func[MENU_SZ])(void) = {disp_menu, select_id, enroll_id, identify_id, identify_id, delete_id};

/////////////////////

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

///////////////////

int progress(int status, char *msg)
{
    debug.printf("%s", msg);

	LCD.cls();
	LCD.locate(0, 1);
    LCD.printf("%s", msg);

	good_beep();

	if (status >= 1 && status <= 100) {
		blue_on();
	}

    return 0;
}

void disp_menu(void)
{
	LCD.cls();
	LCD.locate(0, 1);
	//          1234567890123456789012345
	LCD.printf("Fingerprint System v2.0  \n");
	LCD.locate(0, 10);
	LCD.printf("%s\n", menu[current]);
	LCD.printf("   << MENU >>  * RUN     \n");
   	finger.CmosLed(0);
	rgb_off();
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

void select_id(void)
{
	LCD.locate(0, 10);
	LCD.printf("ID = %d                \n", EnrollID);
	LCD.printf("   << MENU >>  * CHANGE\n");
}

void enroll_id(void)
{
    finger.Open();

	chk_Enrolled(EnrollID);
   	finger.Enroll(EnrollID, progress);
   	finger.CmosLed(1);

	LCD.locate(0, 10);
	LCD.printf("                        ");
	LCD.locate(0, 10);
	LCD.printf("%s\n", menu[current]);
	LCD.printf("   << MENU >>  * RUN     \n");
}

void verify_id(void)
{
	LCD.locate(0, 10);
	LCD.printf("%s\n", menu[current]);
	//          1234567890123456789012345
	LCD.printf("   << MENU >>  * RUN     \n");
}

void identify_id(void)
{
	int id;

   	finger.CmosLed(1);

	debug.printf("Press finger for Identify\n");
	LCD.locate(0, 20);
	LCD.printf("Press finger for Identify\n");

	finger.WaitPress(1);

	if (finger.Capture(1) != 0) {
		debug.printf("Press finger for Identify\n");
		LCD.cls();
		LCD.locate(0, 20);
		//          1234567890123456789012345
		LCD.printf("Press finger for Identify\n");
	}

	id = finger.Identify();
	
	debug.printf("ID = %d\n", id); 
	debug.printf("Remove finger\n");

	if (id == -1) {
		err_beep();
		red_on();
		
		LCD.cls();
		LCD.locate(0, 1);
		LCD.printf("ID = %d, Not matched!\n", id); 
	}
	else {
		good_beep();
		green_on();
		
		LCD.cls();
		LCD.locate(0, 1);
		LCD.printf("ID = %d, Matched!\n", id); 
	}

	LCD.locate(0, 10);
	LCD.printf("%s\n", menu[current]);
	LCD.printf("   << MENU >>  * RUN     \n");

    finger.WaitPress(0);
   	finger.CmosLed(0);
}

void delete_id(void)
{
   	if (finger.DeleteID(EnrollID) == 0) {
		LCD.locate(0, 1);
		//          1234567890123456789012345
		LCD.printf("%d deleted               \n", EnrollID);
	}
	else {
		LCD.locate(0, 1);
		LCD.printf("%d is not found          \n", EnrollID);
	}

	wait(0.5);

	LCD.locate(0, 10);
	LCD.printf("%s\n", menu[current]);
	LCD.printf("   << MENU >>  * RUN     \n");
}

void joy_center_ISR1(void)
{

	ptr_func[current]();
}

void joy_right_ISR(void)
{
	current++;
	if (current > MENU_SZ - 1)
		current = 0;

	LCD.locate(0, 10);
	LCD.printf("                        ");
	LCD.locate(0, 10);
	LCD.printf("%s\n", menu[current]);
	LCD.printf("   << MENU >>  * RUN     \n");

	debounce.reset();
}

void joy_left_ISR(void)
{
	current--;
	if (current < 0)
		current = MENU_SZ - 1;

	LCD.locate(0, 10);
	LCD.printf("                        ");
	LCD.locate(0, 10);
	LCD.printf("%s\n", menu[current]);
	LCD.printf("   << MENU >>  * RUN     \n");

	debounce.reset();
}

void joy_up_ISR(void)
{
	EnrollID++;
	if (EnrollID > (MAX_ID - 1))
		EnrollID = 0;

	debounce.reset();
}

void joy_down_ISR(void)
{
	EnrollID--;
	if (EnrollID < 0)
		EnrollID = MAX_ID - 1;

	debounce.reset();
}

void set_ISR(void)
{
	debounce.start();
	JOY_CENTER.rise(&joy_center_ISR1);
	JOY_RIGHT.rise(&joy_right_ISR);
	JOY_LEFT.rise(&joy_left_ISR);
	JOY_UP.rise(&joy_up_ISR);
	JOY_DOWN.rise(&joy_down_ISR);
}

int main() 
{
    int sts = 0;

	init();
	disp_menu();
	set_ISR();

    sts = finger.Open();
    debug.printf("sts = %d\n", sts);

    if (sts == 0) disp_GT_info();
}
