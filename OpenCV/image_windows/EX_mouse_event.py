#!/usr/bin/env python
# -*- coding: utf-8 -*-
import numpy as np
import cv2

img=np.full((512, 512, 3), 255, dtype=np.uint8)

def on_mouse(event, x, y, flags, param):
    if event == cv2.EVENT_LBUTTONDOWN:  # 왼쪽 클릭
        # 왼쪽 클릭시 파란색 사각형 그리기
        cv2.rectangle(img, (x-50, y-50), (x+50, y+50), (255, 0, 0), -1)
        print("LBTN Click", param[0], x, y) # 좌표 출력
    elif event == cv2.EVENT_RBUTTONDOWN:    # 오른쪽 클릭
        # 오른쪽 클릭시 노란색 원 그리기
        cv2.circle(img, (x, y), 50, (0, 255, 255), -1)
        print("RBTN Click")
    elif event == cv2.EVENT_LBUTTONDBLCLK:  # 왼쪽 더블 클릭
        # 왼쪽 더블 클릭시 검은색으로 배경 채우기
        cv2.rectangle(img, (0, 0), (512, 512), (0, 0, 0), -1)
        print("L Double Click")
    elif event == cv2.EVENT_RBUTTONDBLCLK:  # 오른족 더블 클릭
        # 오른쪽 더블 클릭시 하얀색으로 배경 채우기
        cv2.rectangle(img, (0, 0), (512, 512), (255, 255, 255), -1)
        print("R Double Click")

while True:
    cv2.imshow('img', img)
    cv2.setMouseCallback('img', on_mouse, [img])
    
    key=cv2.waitKey(1000)
    print(key)
    if key == 0x1B:
        print("EXIT")
        break

cv2.destroyAllWindows()
