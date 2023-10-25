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
        void filter2D(cv::Mat &picture, cv::Mat &result);
        
        ~Processing();
    
    private:
        std::vector<std::vector<cv::Point>> contours;
        cv::Mat kernel = (cv::Mat_<float>(3, 3) << 0, -1, 0, -1, 5, -1, 0, -1, 0);
};

#endif