#ifndef PROCESSING_H
#define PROCESSING_H
#include <opencv2/highgui.hpp>

class Processing{
    public:
        Processing();

        void erode(cv::Mat &picture, cv::Mat &result);
        void dilate(cv::Mat &picture, cv::Mat &result);
        
        ~Processing();
};

#endif