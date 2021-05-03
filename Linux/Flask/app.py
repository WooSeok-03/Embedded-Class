#-*- coding:utf-8 -*-
# 모듈 로딩 ------------------------
from flask import Flask
import RPi.GPIO as GPIO
import time

# Flask 객체 생성
# __name__ => python file name
app = Flask(__name__)

# LED Settings
LED = 17
TRIG = 19
ECHO = 26

GPIO.setmode(GPIO.BCM)      # Pin 명명법 - BCM
GPIO.setup(LED, GPIO.OUT)    # Pin 동작모드 설정 - Output ( LED )
GPIO.setup(TRIG, GPIO.OUT)    # Pin 동작모드 설정 - Input ( TRIG )
GPIO.setup(ECHO, GPIO.IN)     # Pin 동작모드 설정 - Output ( ECHO )

# http://localhost:5000/
@app.route("/")
def helloworld():
    # 반드시 return에 결과가 들어가야함.
    return "Hello World!"
    
@app.route("/led/on")
def led_on():
    GPIO.output(LED, GPIO.HIGH)  # LED ON
    return "LED : ON"
    
@app.route("/led/off")
def led_off():
    GPIO.output(LED, GPIO.LOW)   # LED OFF
    return "LED : OFF"

@app.route("/ultrasonic")
def ultrasonic():
    GPIO.output(TRIG, GPIO.LOW)
    time.sleep(0.1)
    GPIO.output(TRIG, GPIO.HIGH)
    time.sleep(0.0002)
    GPIO.output(TRIG, GPIO.LOW)
    
    while GPIO.input(ECHO) == GPIO.LOW:
        start_time = time.time()
        
    while GPIO.input(ECHO) == GPIO.HIGH:
        end_time = time.time()
        
    duration = end_time - start_time
    distance = duration * 17000
    distance = round(distance, 2)
    
    result = "Distance : " + str(distance)
    return result

# python 파일이 실행되는 경우 if문 아래 코드 실행
if __name__ == '__main__':
    # Flask Server Run
    app.run(host="0.0.0.0")
    GPIO.cleanup()  # Pin 사용 헤제 
    exit(0)
