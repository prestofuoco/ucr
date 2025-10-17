/* Your Name & E-mail: Andre Winkel, awink002@ucr.edu
Discussion Section: 024
Assignment: Lab #3 Exercise #1
Exercise Description: reads potentiometer and outputs to serial
I acknowledge all content contained herein, excluding template or example code, is my own original work.
Demo Link: YOUR_YOUTUBE_LINK_HERE
*/

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "timerISR.h"
#include "serialATmega.h"

void ADC_init() {
    // ADMUX: Set REFS0=1 for AVCC reference voltage. 0b01000000
    ADMUX = 0x40;
    // ADCSRA: Set ADEN=1 to enable ADC, set ADPS2:0=111 for prescaler of 128. 0b10000111
    ADCSRA = 0x87;
    // ADCSRB: Leave as 0 for free-running mode. 0b00000000
    ADCSRB = 0x00;
  }
  
unsigned int ADC_read(unsigned char chnl){
    //                              ^^^^ unsigned char chnl selects which pin you're reading analog signal from
  
    ADMUX = (ADMUX & 0xF0) | (chnl & 0x0F);
    ADCSRA |= 0x40;
    
    while((ADCSRA >> 6) & 0x01) {}  // wait for adsc

    uint8_t low, high;

    // Must read ADCL first, then ADCH.
    low = ADCL;
    high = ADCH;

    return ((high << 8) | low) ;
}

void Tick() {
    unsigned int pot_value = ADC_read(0);
    serial_char(pot_value);
}

int main(void) {
    DDRC    = 0x00;
    PORTC   = 0x00;

    DDRB    = 0xFF;
    PORTB   = 0x00;

    DDRD    = 0xFF;
    PORTD   = 0x00;

    ADC_init();

    serial_init(9600);
    
    TimerSet(500);
    TimerOn();
    
    while (1) {
        Tick();
        while (!TimerFlag){}
        TimerFlag = 0;
    }

    return 0;
}