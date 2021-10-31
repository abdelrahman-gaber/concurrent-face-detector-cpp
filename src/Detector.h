#include "opencv2/objdetect.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/videoio.hpp"
#include <vector>
#include <iostream>

/*
This class is adapted from the code in https://docs.opencv.org/3.4/db/d28/tutorial_cascade_classifier.html
*/

class Detector
{
public:
    Detector(cv::String&, int);
    void Run();
    std::vector<cv::Rect> Detect(const cv::Mat&);
    void Display(const cv::Mat& , const std::vector<cv::Rect>&);

private:
    cv::CascadeClassifier _face_cascade;
    cv::VideoCapture _capture;
    int _cam_id;

    void LoadModel(cv::String&);
};

