import cv2

def nothing(x):
    pass

w_name = 'Blurred'
t_name = 'Blur'
cv2.namedWindow(w_name)

cv2.createTrackbar(t_name, w_name, 1, 100, nothing)

capture = cv2.VideoCapture(0)

while(True):
     
    ret, frame = capture.read()
    
    track_pos = cv2.getTrackbarPos(t_name, w_name)
    if (track_pos == 0):
        track_pos = 1
    print ("Trackbar pos: ", track_pos)
    blur = cv2.blur(frame,(track_pos,track_pos))
    
    #cv2.imshow('video', frame)
    cv2.imshow(w_name, blur)
    
    if cv2.waitKey(1) == 27:
        break
