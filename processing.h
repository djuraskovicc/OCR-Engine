#ifndef PROCESSING_H
#define PROCESSING_H
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/core.hpp>

class Processing{
    public:
        Processing();

        void erode(cv::Mat &picture, cv::Mat &result);
        void dilate(cv::Mat &picture, cv::Mat &result);
        void sobel(cv::Mat &picture, cv::Mat &result);
        
        ~Processing();
};

#endif