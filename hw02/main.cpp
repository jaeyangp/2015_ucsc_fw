//
// HW#02
// Jae Yang Park
//
// Input: Pin# 12 (P0.17)
// Output: Pin# 29 (P0.5)
//

#include "mbed.h"
#include "lpc1768_gpio.h"

#define P0_5_OUT	(unsigned char)(1 << 5)
#define P0_17_IN	(unsigned char)(1 << 1)
#define BIT2_H		(unsigned char)(1 << 1)
#define BIT5_H		(unsigned char)(1 << 5)

Serial pc(USBTX, USBRX);

unsigned char buffer[1024];

void toggle(void)
{
	GPIO0_FIO0DIR0 = P0_5_OUT;	// set P0.5 to output

	while (1) {
		GPIO0_FIO0SET0 |= BIT5_H;
		wait_ms(50);
		GPIO0_FIO0CLR0 |= BIT5_H;
		wait_ms(50);
	}
}

void sampling(unsigned char *buf)
{
	register unsigned char r0, r1, r2, r3, r4, r5, r6, r7;

	GPIO0_FIO0DIR2 = 0x00;

	r0 = GPIO0_FIO0PIN2;
	r1 = GPIO0_FIO0PIN2;
	r2 = GPIO0_FIO0PIN2;
	r3 = GPIO0_FIO0PIN2;
	r4 = GPIO0_FIO0PIN2;
	r5 = GPIO0_FIO0PIN2;
	r6 = GPIO0_FIO0PIN2;
	r7 = GPIO0_FIO0PIN2;

	buf[0] = r0;
	buf[1] = r1;
	buf[2] = r2;
	buf[3] = r3;
	buf[4] = r4;
	buf[5] = r5;
	buf[6] = r6;
	buf[7] = r7;
}

void serial_prt(unsigned char *buf)
{
	int i;
	for (i = 0; i < 1024; i++) {
		if (buffer[i] == 0xfd)
			pc.printf("0");
		else
			pc.printf("1");

		if ((i > 0) && (i % 128) == 0) pc.printf("\n\r");
	}

	pc.printf("\n\r");
	pc.printf("done\n\r");
}

int main(void)
{
	//toggle();

	unsigned char *p = buffer;

	while (p < &buffer[1023]) {
		sampling(p);
		p += 8;
	}

	serial_prt(buffer);

	return 0;
}


