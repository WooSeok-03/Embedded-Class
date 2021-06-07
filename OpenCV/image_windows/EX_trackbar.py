#!/usr/bin/env python
# -*- coding: utf-8 -*-
import numpy as np
import cv2

def on_control(pos):
    global img  # 전역변수 img 사용
    r = cv2.getTrackbarPos('R', 'img')
    g = cv2.getTrackbarPos('G', 'img')
    b = cv2.getTrackbarPos('B', 'img')
    # 지정된 색상값응로 이미지 값 설정
    img[:]=(b, g, r)
    # 새롭게 설정된 색상값으로 이미지 표시
    cv2.imshow('img', img)
    
img=np.zeros((512, 512, 3), np.uint8)
cv2.imshow('img', img)

cv2.createTrackbar('R', 'img', 0, 255, on_control)
cv2.createTrackbar('G', 'img', 0, 255, on_control)
cv2.createTrackbar('B', 'img', 0, 255, on_control)

cv2.setTrackbarPos('B', 'img', 255)

cv2.waitKey()
cv2.destroyAllWindows()
