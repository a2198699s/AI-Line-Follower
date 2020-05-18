## Camera Feed Modification

This folder contains an OpenCV program, written in Python, which modifies the HD camera output of the Raspberry Pi Camera and makes it suitable for direct input into the neural network.

### Pixel Reduction

By setting the variables *w* and *h*, the width and height can be altered as required. OpenCV creates an image of the given resolution by taking an average of the pixel area. Different interpolation methods are possible.

### Grey-scale Transformation

The camera feed is converted to grey-scale using a built-in OpenCV method. 

### Resulting Video Data

The resulting video data is an array of integers of size *w*x*h*. Each integer is a representation of how dark the grey-scale image is.

### Image Reproduction

The processed image is then displayed in a window using OpenCV so the pixelated, grey-scale video stream can be seen. The original feed is displayed in a seperate window to allow for comparisons.

The example below shows three video streams: the original stream, reduced resolution (16x16) and a grey-scale conversion.

![Example Image](https://github.com/a2198699s/AI-Line-Follower/blob/master/physical_robot/Camera/python-opencv/PythonOpenCVExample.jpg)
