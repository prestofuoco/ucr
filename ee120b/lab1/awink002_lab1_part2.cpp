#include <avr/io.h>
int main(void)
{
  DDRB = 0xFF; PORTB = 0x00; //Turns all of port D into inputs
  DDRD = 0x00; PORTD = 0xFF; //Turns all of port B into outputs
  int cnt = 0; //counter variable

  while (1) {
    if ((PIND & 0x80) && cnt < 15) {
      cnt = cnt + 1;
      PORTB = (cnt) << 2;
    }
    
    if (PIND & 0x40 && cnt > 0) {
      cnt = cnt - 1;
      PORTB = (cnt) << 2;
    }
    
    _delay_ms(500);
  }
  return 0;
}