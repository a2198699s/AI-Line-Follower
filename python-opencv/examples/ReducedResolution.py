import cv2
from PIL import Image
import numpy as np

def nothing(x):
    pass

w_name = 'Reduced Resolution'
cv2.namedWindow(w_name)

capture = cv2.VideoCapture(0)

while(True):
    
    ret, frame = capture.read()
    
    width, height, _ = frame.shape
    
    # pixel dimensions
    w, h = (16,16)

    resize = cv2.resize(frame,(w,h),interpolation=cv2.INTER_AREA)
    resize = cv2.resize(resize, (width, height), interpolation=cv2.INTER_NEAREST)
    
    greyscale = cv2.cvtColor(resize,cv2.COLOR_BGR2GRAY)

    cv2.imshow('Original', frame)
    #cv2.imshow(w_name, resize)
    
    cv2.imshow('Greyscale',greyscale)
    if cv2.waitKey(1) == 27:
        break
