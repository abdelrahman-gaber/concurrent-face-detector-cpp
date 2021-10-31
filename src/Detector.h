#ifndef DETECTOR_H
#define DETECTOR_H

#include "opencv2/objdetect.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/videoio.hpp"
#include <vector>
#include <utility>
#include <algorithm>
#include <iostream>
#include <thread>
#include <future>
#include "MessageQueue.h"

/*
This class is adapted from the code in https://docs.opencv.org/3.4/db/d28/tutorial_cascade_classifier.html
*/
class Detector
{
public:
    Detector(cv::String&, int);
    ~Detector();
    void Run();
    std::vector<cv::Rect> Detect(const cv::Mat&);
    void Display();

private:
    cv::CascadeClassifier _face_cascade;
    cv::VideoCapture _capture;
    int _cam_id;
    bool _is_running;
    MessageQueue< std::pair<cv::Mat, std::vector<cv::Rect>> > _display_msg_queue;
    std::vector<std::future<void>> _futures;
    std::mutex _mtx;

    void LoadModel(cv::String&);
};

#endif