#include "Detector.h"

Detector::Detector(cv::String& model_pth, int camera_id) : _cam_id(camera_id)
{
    LoadModel(model_pth);
}

void Detector::LoadModel(cv::String& model_pth){
    _face_cascade.load(model_pth);
}

void Detector::Run(){
    //Read the video stream
    _capture.open(_cam_id);
    if ( ! _capture.isOpened() )
    {
        std::cout << "Error opening video capture \n";
        return;
    }

    cv::Mat frame;
    while ( _capture.read(frame) )
    {
        if(frame.empty()) {
            std::cout << "No captured frame -- Break! \n";
            break;
        }

        std::vector<cv::Rect> faces = Detect(frame);
        Display(frame, faces);

        if(cv::waitKey(10) == 27){
            break; // escape
        }
    }
}

std::vector<cv::Rect> Detector::Detect(const cv::Mat& frame){
    cv::Mat frame_gray;
    cvtColor(frame, frame_gray, cv::COLOR_BGR2GRAY);
    equalizeHist(frame_gray, frame_gray);

    // Detect faces
    std::vector<cv::Rect> faces;
    _face_cascade.detectMultiScale(frame_gray, faces);

    return faces;
}

void Detector::Display(const cv::Mat& frame, const std::vector<cv::Rect>& faces){
    cv::Mat display = frame.clone();
    for (size_t i = 0; i < faces.size(); i++)
    {
        cv::rectangle(display, faces[i], cv::Scalar(0, 255, 0), 4);
    }

    // Visualize the detection
    imshow("Face detection Visualization", display);
}

