#!/usr/bin/env python
# -*- coding: utf-8 -*-
import numpy as np
import cv2 

pre_x = pre_y = -1  # 이전 마우스 좌표
r = g = b = -1      # 색상
t = 1               # 두께

def on_mouse(event, x, y, flags, param):
    global pre_x, pre_y
    
    if event == cv2.EVENT_LBUTTONDOWN:
        pre_x, pre_y = x, y
        # 클릭 했을 경우 점을 찍어준다.
        cv2.circle(img, (x, y), t/2 , (b, g, r), -1)
        cv2.imshow('img', img)
    elif event == cv2.EVENT_MOUSEMOVE:
        if flags & cv2.EVENT_FLAG_LBUTTON:
            # 마우스가 움직였을 때 라인을 그려준다.
            cv2.line(img, (pre_x, pre_y), (x, y), (b, g, r), t)
            cv2.imshow('img', img)
            pre_x, pre_y = x, y

def on_control(pos):
    global r, g, b, t
    r = cv2.getTrackbarPos('R', 'img')
    g = cv2.getTrackbarPos('G', 'img')
    b = cv2.getTrackbarPos('B', 'img')
    t = cv2.getTrackbarPos('thickness', 'img')


img=np.zeros((512, 512, 3), np.uint8) + 255
cv2.imshow('img', img)

cv2.createTrackbar('R', 'img', 0, 255, on_control)
cv2.createTrackbar('G', 'img', 0, 255, on_control)
cv2.createTrackbar('B', 'img', 0, 255, on_control)
cv2.createTrackbar('thickness', 'img', 1, 50, on_control)

while True:
    cv2.setMouseCallback('img', on_mouse, [img])
    
    key=cv2.waitKey(1000)
    if key == 0x1B:
        print("EXIT")
        break


cv2.destroyAllWindows()
