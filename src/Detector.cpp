#include "Detector.h"
#include "MessageQueue.h"

Detector::Detector(cv::String& model_pth, int camera_id) : _cam_id(camera_id)
{
    LoadModel(model_pth);
}

Detector::~Detector(){
    std::for_each(_futures.begin(), _futures.end(), [](std::future<void> &ftr) {
        ftr.wait();
    });
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

    std::unique_lock<std::mutex> uLock(_mtx);
    _is_running = true;
    uLock.unlock();

    std::cout << "Detection thread #" << std::this_thread::get_id() << "\n";
    _futures.emplace_back(std::async(std::launch::async, &Detector::Display, this));

    cv::Mat frame;
    while(1)
    {
        //std::unique_lock<std::mutex> uLock(_mtx);
        uLock.lock();
        if( !_is_running ) {break;}
        uLock.unlock();

        _capture.read(frame);
        if(frame.empty()) {
            std::cout << "No captured frame -- Break! \n";
            break;
        }

        // perform detection
        std::vector<cv::Rect> faces = Detect(frame);

        std::pair<cv::Mat, std::vector<cv::Rect>> img_rect_pair = std::make_pair(frame, faces);  
        _display_msg_queue.send( std::move(img_rect_pair) );
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

void Detector::Display(){
    std::cout << "Display worker thread #" << std::this_thread::get_id() << "\n";
    cv::namedWindow("Face detection Visualization");

    while (true)
    {
        //std::this_thread::sleep_for(std::chrono::milliseconds(1));
        std::pair<cv::Mat, std::vector<cv::Rect>> message = _display_msg_queue.receive();

        for (size_t i = 0; i < message.second.size(); i++) {
            cv::rectangle(message.first, message.second[i], cv::Scalar(0, 255, 0), 4);
        }

        // Visualize the detection
        cv::imshow("Face detection Visualization", message.first);

        if(cv::waitKey(1) == 27){
            std::unique_lock<std::mutex> uLock(_mtx);
            _is_running = false;
            uLock.unlock();
            break; // escape
        }
    }
}
