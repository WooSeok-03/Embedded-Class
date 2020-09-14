// Timer_Nomal

void setup() {
  TCCR2A = 0x00;  // Timer/Counter Control Register A
  TCCR2B = 0x02;  // Timer/Counter Control Register B // 8분주
  TCNT2 = 0x00;   // Timer/Counter Register
  TIMSK2 = 0x01;  // Timer/Counter2 Interrupt Mask Register
  Serial.begin(9600);
}

void loop() {

}

int count = 0;

SIGNAL(TIMER2_OVF_vect) {
  TCNT2 = 256 - 200;  // 56부터 시작 (총 200번 카운트 후 Interrupt)
  count++;

  if(count == 7812) {
    count = 0;
    Serial.println("hello");
  }
}
