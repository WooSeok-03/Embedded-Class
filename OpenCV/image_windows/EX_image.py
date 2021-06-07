#!/usr/bin/env python
# -*- coding: utf-8 -*-
import numpy as np
import cv2

def main(args):
    # 하얀색 배경 생성
    img=np.full((500, 500, 3), 255, dtype=np.uint8)
    cv2.imshow('[ IMAGE - WHITE ]', img)
    
    # 검은색 배경 생성 
    img2=np.full((500, 500, 3), 0, dtype=np.uint8)
    cv2.imshow('[ IMAGE - BLACk ]', img2)
    
    # 0으로 채워서 생성
    img3=np.zeros((500, 500, 3), dtype=np.uint8)
    cv2.imshow('[ IMAGE - ZEROS ]', img3)
    
    # 0으로 채운 뒤, 각 요소 255 더하기
    img4=np.zeros((500, 500, 3), np.uint8) + 255
    cv2.imshow('[ IMAGE - ZEROS WHITE ]', img4)
    
    cv2.waitKey()
    cv2.destroyAllWindows()
    return 0

if __name__ == '__main__':
    import sys
    sys.exit(main(sys.argv))
