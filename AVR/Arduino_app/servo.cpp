#include"servo.h"

// 50us 주기, 0.7 ~ 2.3 duty, 1단계 : 32us, 총 50 단계(20ms)

char servo_port = 0;
unsigned long servo_p_micros = 0;
unsigned int servo_count = 0;

void servo_init(char port)
{
  servo_port = port;
  pinMode(servo_port, OUTPUT); 
}

void servo_position(unsigned char degrre)
{
  if (degrre > 180) degrre = 180;
  if (degrre < 0) degrre = 0;

  int duty = 700 + (int)(((float)(180 - degrre) / 180.0) * 1600);
  
  digitalWrite(servo_port, HIGH);
  delayMicroseconds(duty);
  digitalWrite(servo_port, LOW);
  //delayMicroseconds(19300); //delayMicroseconds에 16000을 넣으면 작동 X
  delay(17);
  delayMicroseconds(3000 - duty);

}


void servo_position_micros(unsigned char degree, unsigned long c_micros)
{
  if (degree > 72) degree = 72;
  if (degree < 22) degree = 22;
  int duty = degree;
  
  if(c_micros - servo_p_micros > 32)
  {
    servo_p_micros = c_micros;

    if(servo_count == 625)
    {
      digitalWrite(servo_port, HIGH);
      servo_count = 0;
    }
    else if(servo_count == duty)
    {
      digitalWrite(servo_port, LOW);
    }

    servo_count++;
  }
  
  digitalWrite(servo_port, HIGH);
  delayMicroseconds(duty);
  digitalWrite(servo_port, LOW);
  //delayMicroseconds(19300); //delayMicroseconds�� 16000�� �Ѿ�� �۵� X
  delay(17);
  delayMicroseconds(3000 - duty);

}
