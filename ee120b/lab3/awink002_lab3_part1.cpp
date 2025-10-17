/* Your Name & E-mail: Andre Winkel, awink002@ucr.edu
Discussion Section: 024
Assignment: Lab #3 Exercise #1
Exercise Description: reads potentiometer and outputs to serial
I acknowledge all content contained herein, excluding template or example code, is my own original work.
Demo Link: https://youtu.be/2thaSs0Q-LE
*/

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "timerISR.h"
#include "serialATmega.h"

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

void Tick() {
    unsigned int val = ADC_read(0);
    serial_println(val);
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