from flask import Flask, request
from flask import render_template
import RPi.GPIO as GPIO
import time

app = Flask(__name__)

TRIG = 19
ECHO = 26

#GPIO.setmode(GPIO.BOARD) #BOARD는 커넥터 pin번호 사용
GPIO.setmode(GPIO.BCM)
GPIO.setup(17, GPIO.OUT, initial=GPIO.LOW) # LED Settings
GPIO.setup(21, GPIO.OUT, initial=GPIO.LOW) # BUZZER Settings
GPIO.setup(TRIG, GPIO.OUT)    # Pin 동작모드 설정 - Input ( TRIG )
GPIO.setup(ECHO, GPIO.IN)     # Pin 동작모드 설정 - Output ( ECHO )

def get_distance():
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

@app.route("/")
def home():
    return render_template("index.html", distance=get_distance())

@app.route("/led/on")
def led_on():
    try:
        GPIO.output(17, GPIO.HIGH)
        return "ok"
    except expression as identifier:
        return "fail"

@app.route("/led/off")
def led_off():
    try:
        GPIO.output(17, GPIO.LOW)
        return "ok"
    except expression as identifier:
        return "fail"
        
@app.route("/buzzer/on")
def buzzer_on():
    try:
        GPIO.output(21, GPIO.HIGH)
        return "ok"
    except expression as identifier:
        return "fail"

@app.route("/buzzer/off")
def buzzer_off():
    try:
        GPIO.output(21, GPIO.LOW)
        return "ok"
    except expression as identifier:
        return "fail"
        

if __name__ == "__main__":
    app.run(host="0.0.0.0")
