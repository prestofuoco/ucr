/*        
Your Name & E-mail: Andre Winkel, awink002@ucr.edu
Discussion Section: 024
Assignment: Lab #2  Exercise #1
Exercise Description: moving leds left and right
I acknowledge all content contained herein, excluding template or example code, is my own original work.
Demo Link: <URL>
*/

#include <avr/io.h>
#include <avr/iom328p.h>

unsigned char SetBit(unsigned char x, unsigned char k, unsigned char b) {
   return (b ?  (x | (0x01 << k))  :  (x & ~(0x01 << k)) );
}

unsigned char GetBit(unsigned char x, unsigned char k) {
   return ((x & (0x01 << k)) != 0);
}

// the index is also the digit it represents
// eg: nums[0]="0", nums[9]="9", nums[15]="f"
// bits layout:   gfedcba   (REVERSE ORDER!)
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
    PORTD = num << 2;
}

enum states {hold, left, right, wait} state; //sm enum

void Tick() {
    //static vars

    //state transitions
    switch(state) {
        case hold:
            if ((PINC & 0x01)) {state = right;}
            else if ((PINC & 0x02)) {state = left;}
            else {state = hold;}
            break;
        case wait:
            if ((!(PINC & 0x01)) && (!(PINC & 0x02))) {state = hold;} 
            else {state = wait;}
            break;
        case left:
            state = wait;
            break;
        case right:
            state = wait;
            break;
        default: 
            break;
    }

    //state actions
    switch(state) {
        case hold:
            break;
        case wait:
            break;
        case left:
            if ((PORTD != 0x20)) {PORTD=PORTD<<1;}
            break;
        case right:
            if ((PORTD != 0x04)) {PORTD=PORTD>>1;}
            break;
        default: 
            break;
    }
}

int main(void) {
    //io initialization
    DDRB = 0xFF; PORTB = 0x00; //outputs
    DDRC = 0x00; PORTC = 0xFF; //inputs
    DDRD = 0xFF; PORTD = 0x04; //outputs

  	//state initialization
    state = hold;

    while (1) {
        Tick();
    }
}