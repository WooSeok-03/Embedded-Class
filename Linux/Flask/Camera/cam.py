#!/usr/bin/env python
# -*- coding: utf-8 -*-

import sys
import time
import picamera
from flask import Flask, render_template

app = Flask(__name__)

@app.route("/")
def home():
    return render_template("index.html")

# 엔트리 포인트 함수 선언 ---------------------------------------------------
@app.route('/picture')
def take_picture():
    # 초기화 - PiCamera 객체 생성
    cam = picamera.PiCamera()
    cam.resolution = (640, 480)
    cam.start_preview()
    time.sleep(1)   # 1sec
    
    cam.capture("/home/pi/myproject/Camera/static/cam.jpg")
    cam.stop_preview()
    print("-----END")
    cam.close()
    return "ok"


if __name__ == '__main__':
    app.run(host="0.0.0.0")
