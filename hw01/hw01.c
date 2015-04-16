// HW01
// Assigned Dip pin# 29
// port 0, pin 5

#define FIO0DIR0 	(*(volatile unsigned int *)(0x2009c000))
#define FIO0PIN0 	(*(volatile unsigned int *)(0x2009c014))
#define PIN5_H		((unsigned char)(1 << 5))
#define PIN5_L		((unsigned char)(~(1 << 5)))
#define DIR_OUT		((unsigned char)(~0))

int main()
{
	FIO0DIR0 = DIR_OUT;				// set port 0 output mode

	register unsigned char h, l;
	h = FIO0PIN0 | PIN5_H;
	l = FIO0PIN0 & PIN5_L;

	while (1) {
		FIO0PIN0 = h;	// output 1
		FIO0PIN0 = l;	// output 0
	}
}

