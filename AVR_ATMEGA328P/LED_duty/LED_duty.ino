//LED_duty (가변)

unsigned long c_micros = 0;
unsigned long p_micros = 0;
unsigned long c_millis = 0;
unsigned long p_millis = 0;
int count = 0;
int duty = 1;

void setup() {
  DDRB |= 0x20;   //PB5(13pin)
}

void loop() {
  c_micros = micros();
  c_millis = millis();

  if(c_micros - p_micros > 20) {
    p_micros = c_micros;

    if(count == 100) {
      PORTB |= 0x20;
      count = 0;
    } else if(count == duty) {
      PORTB &= ~0x20;
    }

    count++;
  }

  if(c_millis - p_millis > 10) {
    p_millis = c_millis;

    duty++;

    if(duty == 99) {
      duty = 1;
    }
  }
}
