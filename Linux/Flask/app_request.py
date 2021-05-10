#-*- coding:utf-8 -*-
# 모듈 로딩 ------------------------
from flask import Flask, request
import RPi.GPIO as GPIO
import time

# Flask 객체 생성
# __name__ => python file name
app = Flask(__name__)

# LED Settings
LED = 17

GPIO.setmode(GPIO.BCM)      # Pin 명명법 - BCM
GPIO.setup(LED, GPIO.OUT)    # Pin 동작모드 설정 - Output ( LED )

# http://localhost:5000/ -----------------------------------------------
@app.route("/")
def helloworld():
    return "Hello World!"
    
    
# http://localhost:5000/led?state=on -----------------------------------
@app.route("/led")
def led_state():
    #state = request.args.get("state")           # args에서 받음.
    state = request.values.get("state", "error") # value에서 받음.
    if state == "on":
        GPIO.output(LED, GPIO.HIGH)  # LED ON
        return "LED : ON"
    elif state == "off":
        GPIO.output(LED, GPIO.LOW)   # LED OFF
        return "LED : OFF"
    elif state == "error":
        return "state가 전달되지 않았습니다."
    else:
        return "잘못된 state가 전달되었습니다."
    

# python 파일이 실행되는 경우 if문 아래 코드 실행
if __name__ == '__main__':
    # Flask Server Run
    app.run(host="0.0.0.0")
    GPIO.cleanup()  # Pin 사용 헤제 
    exit(0)
