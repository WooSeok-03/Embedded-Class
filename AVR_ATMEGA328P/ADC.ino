void setup() {
  Serial.begin(9600);
  ADMUX = 0x40;
  ADCSRA = 0x87;
}

void loop() {
  unsigned int adc_value_x = 0;
  unsigned int adc_value_y = 0;

  ADMUX = 0x40;
  //int adc_value = analogRead(14);
  ADCSRA |= 0x40;
  delay(1);

  adc_value_x = ADC;

  Serial.println("x : " + String(adc_value_x));

  ADMUX = 0x41;
  ADCSRA |= 0X40;
  delay(1);

  adc_value_y = ADC;

  Serial.println("y : " + String(adc_value_y));
  Serial.println();

  delay(100);
}
