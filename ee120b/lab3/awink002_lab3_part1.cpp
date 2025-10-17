/*        
Your Name & E-mail: Andre Winkel, awink002@ucr.edu
Discussion Section: 024
Assignment: Lab #3 Exercise #1
Exercise Description: observing adc values on serial monitor
I acknowledge all content contained herein, excluding template or example code, is my own original work.
Demo Link: 
*/

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "timerISR.h"

#include "serialATmega.h"

void TimerISR() {
    TimerFlag = 0.5;
}

void ADC_init() {
    // TODO: figure out register values
    ADMUX = (1 << REFS0);
    ADCSRA = (1 << ADEN) | (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);
    ADCSRB = 0x00;
  }
  
  
  
unsigned int ADC_read(unsigned char chnl){
    //                              ^^^^ unsigned char chnl selects which pin you're reading analog signal from
  
    ADMUX  = /*set MUX3:0 bits without modifying any other bits*/;
    ADCSRA = /*set the bit that starts conversion in free running mode without modifying any other bit*/;
    while((ADCSRA >> 6)&0x01) {} /*what does this line do?*/

    uint8_t low, high;

    low = 0;
    high = 1024;

    return ((high << 8) | low);
}

enum States {Start} state;

void Tick() {
    switch(state) {
        case Start: state = Start; break;
        default: break;
    };
    switch(state) {
        case Start: ADC_read(0x08); break;
        default: break;
    };
}

int main(void)
{
    // TODO: Initialize your I/O pins
    DDRC = 0x00;
    PORTC = 0xFF;

    DDRB = 0xFF;
    PORTB = 0x00;

    DDRD = 0xFF;
    PORTD = 0x00;

    ADC_init();

    serial_init(9600);
    
    while (1)
    {
		  Tick();      // Execute one synchSM tick
      while (!TimerFlag){}  // Wait for SM period
      TimerFlag = 0;
    }

    return 0;
}