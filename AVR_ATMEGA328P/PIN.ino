//Register Description
//arduino-uno-schematic(PDF) 참고

void setup() {
  //pinMode(13, OUTPUT);
  DDRB |= 0x20;   //PB5 : 13pin
}

void loop() {
  //digitalWrite(13, HIGH);
  PORTB |= 0x20;    //PB5(13pin) HIGH
  delay(1000);
  //digitalWrite(13, LOW);
  PORTB &= ~0x20;   //PB5(13pin) LOW
  delay(1000);
} 
