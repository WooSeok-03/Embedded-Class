// Timer_CTC

void setup() {
  TCCR2A = 0x02;  // 0x02 : CTC Mode
  TCCR2B = 0x02;  // 8분주
  TCNT2 = 0;      // 0부터 카운트
  OCR2A = 200;    // 200에서 Interrupt
  TIMSK2 = 0x02;  // Compare Match A Interrupt Enable //OCR2A에 매치되는 곳에서 Interrupt
  Serial.begin(9600);
}

void loop() {

}

int count = 0;

SIGNAL(TIMER2_COMPA_vect) {
  count++;

  if(count == 10000) {
    count = 0;
    Serial.println("hello");
  }
}
