임베디드 소프트웨어 수업
=
수업에서 배운 내용
-
### GPIO
* 다용도 입출력(general-purpose input/output) : 입력이나 출력을 포함한 동작이 런타임 시에 사용자에 의해 제어될 수 있는, 집적 회로나 전기 회로 기판의 디지털 신호 핀
* ( 즉, 입력이나 출력같은 동작이 실행 시에 사용자에 의해 제어 될 수 있는 디지털 신호 핀 ) 

### PWM
* 펄스 폭 변조(Pulse Width Modulation) : 디지털 출력으로 아날로그 회로를 제어 하는 기술

### ADC
* 아날로그-디지털 변환회로(Analog-to-digital converter) : 아날로그 신호를 디지털 전기 신호로 변환하는 것
* ( 연속적인 analog신호를 0과 1로 구성된 digital신호로 변환하는 것 )

### EXTI
* 외부 인터럽트(External Interrupt) : 스위치를 누르는 것과 같이 외부에서 인터럽트를 발생시키는 것
* ( Timer를 이용하여 인터럽트를 발생시키는 것은 내부 인터럽트라고 한다. )
* ( 인터럽트 : 동작을 수행하기 우이해 주는 신호 )

### TIMER
* 정확한 시간을 재기 위해 사용
* 정확한 시간지연이 필요한 경우 타이머를 사용
* MCU나 CPU에는 Timer가 3개 이상 들어 있다.
* 외부에서 들어오는 신호의 주기 또는 주파수를 측정하거나, Delay함수를 만들거나, 외부로 PWM 펄스를 내보낼 때, 주로 사용
* ( 주기 : 0과 1이 번갈아 한번 나타나는 시간. / 주파수 : 1초 당 0과 1이 변화된 횟수 )

### SysTick
* Cortex-M 코어에만 지원하는 24bit 타이머이다.
* SysTick은 시스템 클럭를 그대로 사용하거나 8분주한 클럭을 소스로 사용할 수 있다.

### UART
* 범용 비동기화 송수신기(Universal asynchronous receiver/transmitter) : 병렬 데이터의 형태를 직렬 방식으로 전환하여 데이터를 전송하는 것
* PIN : RX / TX

### I2C
* 아이스퀘어드시(Inter-Integrated Circuit) : 필립스에서 개발한 직렬 버스이다.
* 2개의 선을 이용하는 통신 방식이다.
* 하나의 Master에 여러 개의 Slave 기기가 연결 될 수 있다.
* 클럭 신호를 사용하는 동기식 통신 방식이기 때문에 시간에 자유롭다는 장점이 있다.
* 슬레이브 선택을 위해 항상 주소 데이터가 붙기 때문에 긴 데이터에는 부적합하다는 단점이 있다.
* charLCD를 제어할때, 사용했었다.
* PIN : SCL / CDA

### SPI
* 직렬 주변기기 인터페이스 버스(Serial Peripheral Interface Bus) : 동기화 직렬 데이터 연결 표준
* Master와 Slave로 통신한다.
* 1 : N의 통신을 지원하는 동기식 통신 방식
* 동시에 송수신이 가능함
* I2C에 비해 속도가 빠름
* 간단하게 배선이 가능
* 단순 센서, 메모리와 같은 칩과 칩 사이의 통신에 많이 사용
* RS-232, CAN버스보다 비교적 짧은 거리에서 동작
* 하나의 마스터 장치만 지원함. ( Master는 꼭 1개이다. / Slave는 여러개 가능 )
* PIN : SCLK / MOSI / MISO / SS


수업에서 사용했던 모듈
-
### LED

### Button

### Active Buzzer

### Passive Buzzer

### Servo Motor
* PWM을 구현할 때 많이 사용

### DC Motor

### Step Motor

### Joy Stick

### Ultrasonic Sensor (초음파 센서)

### Photo Resistor (조도 센서)

### charLCD (16x2)

### LCD (128x64)

### OLED (128x128)
* SPI 사용

### Bluetooth
* 우리가 수업에 사용하는 모듈 : HC-06 / HC-05

### WIFI
* 우리가 수업에 사용하는 모듈 : esp8266



