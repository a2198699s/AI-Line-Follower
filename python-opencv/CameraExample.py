import cv2
import numpy as np
 
capture = cv2.VideoCapture(0)
 
# convelution
kernel = np.ones((10,10),np.float32)/25

while(True):
     
    ret, frame = capture.read()
     
    # apply convelution
    conv = cv2.filter2D(frame, -1, kernel)
    blur = cv2.blur(frame,(15,15)) 

    cv2.imshow('video', frame)
    cv2.imshow('blurred video', blur)
    cv2.imshow('conveluted video', conv) 
    if cv2.waitKey(1) == 27:
        break
 
capture.release()
cv2.destroyAllWindows()
