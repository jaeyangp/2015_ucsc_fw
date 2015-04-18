//
// lpc1768_gpio.h
// LPC1768 GPIO definition for mbed
//

#ifndef LPC1768_GPIO_H
#define LPC1768_GPIO_H

#define GPIO0_FIO0DIR0	(*(volatile unsigned char *)(0x2009c000))
#define GPIO0_FIO0MASK0	(*(volatile unsigned char *)(0x2009c010))
#define GPIO0_FIO0PIN0	(*(volatile unsigned char *)(0x2009c014))
#define GPIO0_FIO0SET0	(*(volatile unsigned char *)(0x2009c018))
#define GPIO0_FIO0CLR0	(*(volatile unsigned char *)(0x2009c01c))

#define GPIO0_FIO0DIR1	(*(volatile unsigned char *)(0x2009c001))
#define GPIO0_FIO0MASK1	(*(volatile unsigned char *)(0x2009c011))
#define GPIO0_FIO0PIN1	(*(volatile unsigned char *)(0x2009c015))
#define GPIO0_FIO0SET1	(*(volatile unsigned char *)(0x2009c019))
#define GPIO0_FIO0CLR1	(*(volatile unsigned char *)(0x2009c01d))

#define GPIO0_FIO0DIR2	(*(volatile unsigned char *)(0x2009c002))
#define GPIO0_FIO0MASK2	(*(volatile unsigned char *)(0x2009c012))
#define GPIO0_FIO0PIN2	(*(volatile unsigned char *)(0x2009c016))
#define GPIO0_FIO0SET2	(*(volatile unsigned char *)(0x2009c01a))
#define GPIO0_FIO0CLR2	(*(volatile unsigned char *)(0x2009c01e))

#define GPIO0_FIO0DIR3	(*(volatile unsigned char *)(0x2009c003))
#define GPIO0_FIO0MASK3	(*(volatile unsigned char *)(0x2009c013))
#define GPIO0_FIO0PIN3	(*(volatile unsigned char *)(0x2009c017))
#define GPIO0_FIO0SET3	(*(volatile unsigned char *)(0x2009c01b))
#define GPIO0_FIO0CLR3	(*(volatile unsigned char *)(0x2009c01f))

#define GPIO2_FIO2DIR0	(*(volatile unsigned char *)(0x2009c040))
#define GPIO2_FIO2MASK0	(*(volatile unsigned char *)(0x2009c050))
#define GPIO2_FIO2PIN0	(*(volatile unsigned char *)(0x2009c054))
#define GPIO2_FIO2SET0	(*(volatile unsigned char *)(0x2009c058))
#define GPIO2_FIO2CLR0	(*(volatile unsigned char *)(0x2009c05c))

#define GPIO2_FIO2DIR1	(*(volatile unsigned char *)(0x2009c041))
#define GPIO2_FIO2MASK1	(*(volatile unsigned char *)(0x2009c051))
#define GPIO2_FIO2PIN1	(*(volatile unsigned char *)(0x2009c055))
#define GPIO2_FIO2SET1	(*(volatile unsigned char *)(0x2009c059))
#define GPIO2_FIO2CLR1	(*(volatile unsigned char *)(0x2009c05d))

#define GPIO2_FIO2DIR2	(*(volatile unsigned char *)(0x2009c042))
#define GPIO2_FIO2MASK2	(*(volatile unsigned char *)(0x2009c052))
#define GPIO2_FIO2PIN2	(*(volatile unsigned char *)(0x2009c056))
#define GPIO2_FIO2SET2	(*(volatile unsigned char *)(0x2009c05a))
#define GPIO2_FIO2CLR2	(*(volatile unsigned char *)(0x2009c05e))

#define GPIO2_FIO2DIR3	(*(volatile unsigned char *)(0x2009c043))
#define GPIO2_FIO2MASK3	(*(volatile unsigned char *)(0x2009c053))
#define GPIO2_FIO2PIN3	(*(volatile unsigned char *)(0x2009c057))
#define GPIO2_FIO2SET3	(*(volatile unsigned char *)(0x2009c05b))
#define GPIO2_FIO2CLR3	(*(volatile unsigned char *)(0x2009c05f))

#endif

