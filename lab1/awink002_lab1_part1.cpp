#include <avr/io.h>
int main(void)
{
  DDRB = 0xFF; PORTB = 0x00; //Turns all of port D into inputs
  DDRD = 0x00; PORTD = 0xFF; //Turns all of port B into outputs
  PORTB = 0x04; //start with rightmost led on

  while (1) {    
    if ((PIND & 0x80) && PORTB != 0x20) {
      PORTB = PORTB<<1;
    }
    
    if (PIND & 0x40 && PORTB != 0x04) {
      PORTB = PORTB>>1;
    }
    
    _delay_ms(500);
  }
  return 0;
}