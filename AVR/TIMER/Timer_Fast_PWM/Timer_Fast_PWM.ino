//Timer_Fast PWM

void setup() {
  TCCR2A = 0x03;  // 0x03 : Fast PWM Mode
  TCCR2B = 0x02;  // 8분주
  TCNT2 = 56; //100us    // Nomal
  OCR2A = 100; //500us   // CTC
  TIMSK2 = 0x03;
  //Output Compare Match A Interrupt Enable & Overflow Interrupt Enable
  //Nomal 과 CTC 동시 사용
  Serial.begin(9600);
}

void loop() {

}

int count_ovf = 0;
int count_comp = 0;

SIGNAL(TIMER2_OVF_vect) {   //Nomal
  TCNT2 = 256 - 200;
  count_ovf++;

  if(count_ovf == 10000) {
    count_ovf = 0;
    Serial.println("ovf");
  }
}

SIGNAL(TIMER2_COMPA_vect) {   // CTC
  count_comp++;

  if(count_comp == 5000) {
    count_comp = 0;
    Serial.println("comp");
  }
}
