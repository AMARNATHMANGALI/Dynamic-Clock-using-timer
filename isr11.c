/*
 * File:   isr11.c
 * Author: amarm
 *
 * Created on 18 July, 2024, 7:54 AM
 */


#include"header11.h"
extern int hours,mins,sec;

void __interrupt() isr(void) {
    static unsigned int count;
    if (TMR0IF) {
        if (++count == 20000) {
            count = 0;
            if (++sec == 60) {
                sec = 0;
                mins++;
                if (mins > 59) {
                    mins = 0;
                    hours++;
                    if (hours > 23) {
                        hours = 0;
                    }
                }
            }
        }
        TMR0IF = 0;
    }
}