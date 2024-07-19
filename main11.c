/*
 * File:   main11.c
 * Author: amar
 *
 * Created on 17 July, 2024, 7:03 PM
 */


#include "header11.h"
static unsigned char ssd[MAX_SSD_CNT];
static unsigned char digit[] = {ZERO, ONE, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE};
int hours, mins, sec;

void main(void) {
    int key, flag = 0, select_flag = 0;
    unsigned int delay = 0, wait = 0;
    init_config();
    while (1) {
        key = read_digital_keypad(STATE_CHANGE);
        if (key == SWITCH4) {
            TMR0ON = !TMR0ON;
            flag = !flag;
            wait=0;
        }
        if (flag == 1) {
            if (key == SWITCH3) {
                select_flag = !select_flag;
                wait=0;
                sec=0;
            }
            if (select_flag == 0) {
                ssd[0] = digit[hours / 10];
                ssd[1] = digit[hours % 10];
                
                if (wait++ == 100) {
                    ssd[2] = digit[mins / 10];
                    ssd[3] = digit[mins % 10];
                } else if (wait == 200) {
                    wait = 0;
                    ssd[2] = 0x40;
                    ssd[3] = 0x40;
                }
                if (key == SWITCH1) {
                    mins++;
                    if (mins > 59) {
                        mins = 0;
                    }

                } else if (key == SWITCH2) {
                    mins--;
                    if (mins < 0) {
                        mins = 59;
                    }
                }
            } else if (select_flag == 1) {
                ssd[2] = digit[mins / 10];
                ssd[3] = digit[mins % 10];
                if(wait++ == 100)
                {
                   ssd[0] = digit[hours / 10]; 
                   ssd[1] = digit[(hours % 10)];
                }
                else if(wait == 200)
                {
                    wait=0;
                    ssd[0] = 0x40;
                    ssd[1] = 0x40 ;
                }
                if (key == SWITCH1) {
                    hours++;
                    if (hours > 23) {
                        hours = 0;
                    }
                } else if (key == SWITCH2) {
                    hours--;
                    if (hours < 0) {
                        hours = 23;
                    }
                }
            }
        } else {
            if (sec % 2 == 0) {
                delay = 0;
                ssd[1] = digit[(hours % 10)] | DOT;
            } else {
                ssd[1] = digit[hours % 10];
            }
            ssd[0] = digit[hours / 10];
            ssd[2] = digit[mins / 10];
            ssd[3] = digit[mins % 10];
        }
        display(ssd);
    }
}

void init_config() {
    init_digital_keypad();
    init_ssd_control();
    init_timer0();
}

void init_timer0() {
    PEIE = 1;
    ADCON1 = 0x0F;
    T08BIT = 1;

    /* Selecting internal clock source */
    T0CS = 0;

    /* Enabling timer0*/
    TMR0ON = 1;

    /* disabling prescaler*/
    PSA = 1;

    TMR0 = 6;

    /* Clearing timer0 overflow interrupt flag bit */
    TMR0IF = 0;

    /* Enabling timer0 overflow interrupt */
    TMR0IE = 1;
    GIE = 1;
}


