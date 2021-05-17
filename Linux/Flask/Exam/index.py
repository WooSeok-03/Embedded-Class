#!/usr/bin/env python3
# -*- coding: utf-8 -*-

from bluetooth import *
from flask import Flask, request, render_template
import RPi.GPIO as GPIO
import time

socket = BluetoothSocket( RFCOMM )
socket.connect(("98:D3:91:FD:F6:EA", 1))

app = Flask(__name__)

# RGB LED Pin
R = 21
G = 20
B = 16

# Ultra Sonic Pin
TRIG = 19
ECHO = 26

#GPIO.setmode(GPIO.BOARD) #BOARD는 커넥터 pin번호 사용
GPIO.setmode(GPIO.BCM)
GPIO.setup(R, GPIO.OUT, initial=GPIO.LOW) # R-LED Settings
GPIO.setup(G, GPIO.OUT, initial=GPIO.LOW) # G-LED Settings
GPIO.setup(B, GPIO.OUT, initial=GPIO.LOW) # B-LED Settings

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
    
    if distance <= 10:
        GPIO.output(24, GPIO.HIGH)
    else:
        GPIO.output(24, GPIO.LOW)
    
    result = str(distance)
    return result

@app.route("/")
def home():
    return render_template("index.html")

@app.route("/rgb/<state>/on")
def rgb_led_on(state):
    if state == "r":
        GPIO.output(R, GPIO.HIGH)
        return "RED-LED : ON"
    elif state == "g":
        GPIO.output(G, GPIO.HIGH)
        return "GREEN-LED : ON"
    elif state == "b":
        GPIO.output(B, GPIO.HIGH)
        return "BLUE-LED : ON"
    else:
        return "잘못된 state입니다."
        
        
@app.route("/rgb/<state>/off")
def rgb_led_off(state):
    if state == "r":
        GPIO.output(R, GPIO.LOW)
        return "RED-LED : OFF"
    elif state == "g":
        GPIO.output(G, GPIO.LOW)
        return "GREEN-LED : OFF"
    elif state == "b":
        GPIO.output(B, GPIO.LOW)
        return "BLUE-LED : OFF"
    else:
        return "잘못된 state입니다."


@app.route("/rgb/all/on")
def rgb_all_on():
    try:
        GPIO.output(R, GPIO.HIGH)
        GPIO.output(G, GPIO.HIGH)
        GPIO.output(B, GPIO.HIGH)
        return "ok"
    except expression as identifier:
        return "fail"

@app.route("/rgb/all/off")
def rgb_all_off():
    try:
        GPIO.output(R, GPIO.LOW)
        GPIO.output(G, GPIO.LOW)
        GPIO.output(B, GPIO.LOW)
        return "ok"
    except expression as identifier:
        return "fail"
        
@app.route("/distance")
def ultrasonic():
    try:
        return get_distance()
    except expression as identifier:
        return "fail"

@app.route("/dht/<state>")
def dht(state):
    past_str = ""
    if state == "on":
        data = socket.recv(1024)
        str1 = data.decode()
        
        if "TEMP" in str1:
            return str1[(len(str1)- 21):len(str1)]
        else:
            return "read_data wait"
    else:
        return "잘못된 state입니다."

if __name__ == "__main__":
    app.run(host="0.0.0.0")
