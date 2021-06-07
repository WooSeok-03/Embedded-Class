#!/usr/bin/env python
# -*- coding: utf-8 -*-
import numpy as np
import cv2

x_position = 300
y_position = 300

img = np.full((512, 512, 3), 255, dtype=np.uint8)

# 방향키 입력 처리 -------------------------------------
while True:
    
    key=cv2.waitKey(1000) # 1s
    print(key)
    if key == 0x1B:         # ESC : 27
        print("EXIT")
        break
    elif key == 0x51:   # 왼쪽 방향키
        # 도형 왼쪽으로 옮기기
        cv2.circle(img, (x_position, y_position), 50, (255, 255, 255), -1)
        x_position -= 5
        if x_position < 50: x_position = 50 
        cv2.circle(img, (x_position, y_position), 50, (255, 255, 0), -1)
        print("L")
    elif key == 0x52:   # 위쪽 방향키
        # 도형 위로 옮기기
        cv2.circle(img, (x_position, y_position), 50, (255, 255, 255), -1)
        y_position -= 5
        if y_position < 50: y_position = 50 
        cv2.circle(img, (x_position, y_position), 50, (255, 255, 0), -1)
        print("U")
    elif key == 0x54:   # 아래쪽 방향키
        # 도형 아래로 옮기기
        cv2.circle(img, (x_position, y_position), 50, (255, 255, 255), -1)
        y_position += 5
        if y_position > 462: y_position = 462 
        cv2.circle(img, (x_position, y_position), 50, (255, 255, 0), -1)
        print("D")
    elif key == 0x53:   # 오른쪽 방향키
        # 도형 오른쪽으로 옮기기
        cv2.circle(img, (x_position, y_position), 50, (255, 255, 255), -1)
        x_position += 5
        if x_position > 462: x_position = 462 
        cv2.circle(img, (x_position, y_position), 50, (255, 255, 0), -1)
        print("R")
        
    cv2.imshow('img', img)
    
    
cv2.destroyAllWindows()
