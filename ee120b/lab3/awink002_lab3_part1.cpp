/*        
Your Name & E-mail: Andre Winkel, awink002@ucr.edu
Discussion Section: 024
Assignment: Lab #3 Exercise #1
Exercise Description: 
I acknowledge all content contained herein, excluding template or example code, is my own original work.
Demo Link: 
*/

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "timerISR.h"

#include "serialATmega.h"

void ADC_init() {
    // TODO: figure out register values
    ADMUX = /*insert your value for ADMUX*/;
    ADCSRA = /*insert your value for ADCSRA*/;
    ADCSRB = /*insert your value for ADCSRB*/;
  }
  
  
  
unsigned int ADC_read(unsigned char chnl){
    //                              ^^^^ unsigned char chnl selects which pin you're reading analog signal from
  
    ADMUX  = /*set MUX3:0 bits without modifying any other bits*/;
    ADCSRA = /*set the bit that starts conversion in free running mode without modifying any other bit*/;
    while((ADCSRA >> 6)&0x01) {} /*what does this line do?*/

    uint8_t low, high;

    low = /*what should this get assigned with?*/;
    high = /*what should this get assigned with?*/;

    return ((high << 8) | low) ;
}

void Tick() {
    // TODO: Implement your Tick Function
}

int main(void)
{
    // TODO: Initialize your I/O pins
    DDRC    = ;
    PORTC   = ;

    DDRB     = ;
    PORTB    = ;

    DDRD   = ;
    PORTD  = ;

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