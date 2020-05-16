import cv2
import numpy as np
 
def nothing(x):
    pass

capture = cv2.VideoCapture(0)
 
# convelution
kernel = np.ones((10,10),np.float32)/25

# modifying parameters
cv2.createTrackbar('Bluriness', 'blurred', 5, 25, nothing)
#cv2.setTrackbarPos('Bluriness', 'blurred', 10)
track_pos = 5

while(True):
     
    ret, frame = capture.read()
     
    # apply convelution
    conv = cv2.filter2D(frame, -1, kernel)
    #track_pos = cv2.getTrackbarPos('Bluriness', 'blurred')
    print ("Trackbar pos: ", track_pos)
    blur = cv2.blur(frame,(track_pos,track_pos))
    cv2.imshow('video', frame)
    cv2.imshow('blurred', blur)
    #cv2.imshow('conveluted video', conv)

    if cv2.waitKey(1) == 27:
        break
 
capture.release()
cv2.destroyAllWindows()
