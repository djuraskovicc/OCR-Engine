#ifndef PROCESSING_H
#define PROCESSING_H
#include <opencv2/highgui.hpp>
#include <vector>

class Processing {
    public:
        Processing();

        void erode(cv::Mat &picture, cv::Mat &result);
        void dilate(cv::Mat &picture, cv::Mat &result);
        void findContours(cv::Mat &picture);
        void drawContours(cv::Mat &result);
        
        ~Processing();
    
    private:
        std::vector<std::vector<cv::Point>> contours;
};

#endif