/*
 * File:   ssd.c
 * Author: amarm
 *
 * Created on 17 July, 2024, 7:13 PM
 */


#include"header11.h"
void init_ssd_control(void)
{
	/* Setting PORTB as output for Data Lines */
	TRISD = 0x00;
	/* Setting SSD Enable lines as output */
	TRISA = TRISA & 0xF0;

	/* Switching OFF all the SSDs to start with */
	SSD_CNT_PORT = SSD_CNT_PORT & 0xF0;
}
void display(unsigned char data[])
{
	unsigned int wait;
	unsigned char data_bit;
	unsigned char digit;

	for (digit = 0; digit < MAX_SSD_CNT; digit++)
	{
		SSD_DATA_PORT = data[digit];
		SSD_CNT_PORT = (SSD_CNT_PORT & 0xF0) | (0x01 << digit);

		for (wait = 1000; wait--; );
	}
}
