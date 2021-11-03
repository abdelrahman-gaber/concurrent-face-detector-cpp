# Concurrent Face Detector in C++

This is my final Project for the [Udacity C++ Nanodegree Program](https://www.udacity.com/course/c-plus-plus-nanodegree--nd213). 

This project captures video stream from a webcam, detect faces, and visualize the detection as bounding boxes around the faces in each frame.
The main idea is to use concurrency to allow for real-time detection. 
There are three main threads running in paralell:
1. Video capturing and image preprocessing, then adding the image to a frame buffer (message queue).
2. Reading from the frame buffer once an image is available, and apply face detection with OpenCV [Multi-scale Face Detector](https://docs.opencv.org/3.4/db/d28/tutorial_cascade_classifier.html), then add the results to a display buffer (another message queue). 
3. Reading from the display buffer once a detection is available, and visualize the detection bounding boxes on the frame. 



## Dependencies for Running Locally
* cmake >= 2.8
  * All OSes: [click here for installation instructions](https://cmake.org/install/)
* make >= 4.1 (Linux, Mac), 3.81 (Windows)
  * Linux: make is installed by default on most Linux distros
  * Mac: [install Xcode command line tools to get make](https://developer.apple.com/xcode/features/)
  * Windows: [Click here for installation instructions](http://gnuwin32.sourceforge.net/packages/make.htm)
* OpenCV >= 4.1
  * The OpenCV 4.1.0 source code can be found [here](https://github.com/opencv/opencv/tree/4.1.0)
* gcc/g++ >= 5.4
  * Linux: gcc / g++ is installed by default on most Linux distros
  * Mac: same deal as make - [install Xcode command line tools](https://developer.apple.com/xcode/features/)
  * Windows: recommend using [MinGW](http://www.mingw.org/)

Note: This application is tested on Ubuntu 18.04 and OpenCV versions 4.1.0 and 3.2.0 

## Basic Build Instructions

1. Clone this repo.
2. Make a build directory in the top level directory: `mkdir build && cd build`
3. Compile: `cmake .. && make`
4. Connect your webcam and run the application specifying your camera id: `./face_detection --camera={YOUR_CAMERA_ID}`, for example `./face_detection --camera=0`.
5. To stop the application, press Esc 

