/* Your Name & E-mail: Andre Winkel, awink002@ucr.edu
Discussion Section: 024
Assignment: Lab #3 Exercise #2
Exercise Description: am and fm to 7seg
I acknowledge all content contained herein, excluding template or example code, is my own original work.
Demo Link: YOUR_YOUTUBE_LINK_HERE
*/

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "timerISR.h"

unsigned char SetBit(unsigned char x, unsigned char k, unsigned char b) {
    return (b ?  (x | (0x01 << k))  :  (x & ~(0x01 << k)) );
                //   Set bit to 1           Set bit to 0
}

unsigned char GetBit(unsigned char x, unsigned char k) {
    return ((x & (0x01 << k)) != 0);
}

int nums[16] = {0b0111111, // 0
                0b0000110, // 1
                0b1011011, // 2
                0b1001111, // 3
                0b1100110, // 4
                0b1101101, // 5
                0b1111101, // 6
                0b0000111, // 7
                0b1111111, // 8
                0b1101111, // 9
                0b1110111, // A
                0b1111100, // b
                0b0111001, // C
                0b1011110, // d
                0b1111001, // E
                0b1110001  // F
                };

//TODO: complete outNum()
void outNum(int num) {
    PORTB = (nums[num] & 0x1F);
    PORTD = ((nums[num] & 0x60) << 1);
}

void ADC_init() {
    ADMUX = 0x40;
    ADCSRA = 0x87;
    ADCSRB = 0x00;
}

unsigned int ADC_read(unsigned char chnl){
    //                              ^^^^ unsigned char chnl selects which pin you're reading analog signal from

    ADMUX = (ADMUX & 0xF0) | (chnl & 0x0F);
    ADCSRA |= 0x40;

    while((ADCSRA >> 6) & 0x01) {}  // wait for adsc

    uint8_t low, high;

    // adcl then adch
    low = ADCL;
    high = ADCH;

    return ((high << 8) | low) ;
}

// Provided map()
long map(long x, long in_min, long in_max, long out_min, long out_max) {
    return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

enum states {start, AM_PR, AM_REL, FM_PR, FM_REL} state; //TODO: finish the enum for the SM

void Tick() {
    unsigned int val = ADC_read(0);
    unsigned int am = map(val, 0, 1023, 0, 9);
    unsigned int fm = map(val, 0, 1023, 10, 15);

    // State Transistions
    switch (state) {
        case start:
            state = AM_REL;
            break;
        case AM_PR:
            if ((PINC & 0x02)) {state = AM_PR;}
            else if (!(PINC & 0x02)) {state = AM_REL;}
            break;
        case AM_REL:
            if ((PINC & 0x02)) {state = FM_PR;}
            else if (!(PINC & 0x02)) {state = AM_REL;}
            break;
        case FM_PR:
            if ((PINC & 0x02)) {state = FM_PR;}
            else if (!(PINC & 0x02)) {state = FM_REL;}
            break;
        case FM_REL:
            if ((PINC & 0x02)) {state = AM_PR;}
            else if (!(PINC & 0x02)) {state = FM_REL;}
            break;
        default:
            break;
    }

    // State Actions
    switch (state) {
        case start:
            break;
        case AM_PR:
            outNum(am);
            break;
        case AM_REL:
            outNum(am);
            break;
        case FM_PR:
            outNum(fm);
            break;
        case FM_REL:
            outNum(fm);
            break;
        default:
            break;
    }
}

int main(void) {
    DDRC    = 0x00;
    PORTC   = 0x00;

    DDRB    = 0xFF;
    PORTB   = 0x00;

    DDRD    = 0xFF;
    PORTD   = 0x00;

    ADC_init();
    TimerSet(500);
    TimerOn();

    while (1) { 
        Tick();      // Execute one synchSM tick
        while (!TimerFlag){}  // Wait for SM period
        TimerFlag = 0;        // Lower flag
    }

    return 0;
}