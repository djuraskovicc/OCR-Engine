#ifndef FUNCTIONS_H
#define FUNCTIONS_H
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/core.hpp>

class Filters {
    public:
        Filters();

        void addBilateralFilter(cv::Mat &picture, cv::Mat &result);
        void addWeight(cv::Mat &picture, cv::Mat &picture1, cv::Mat &result);
        void gaussianBlur(cv::Mat &picture, cv::Mat &result);
        void scaleAbs(cv::Mat &picture, cv::Mat &result);
        void threshold(cv::Mat &picture, cv::Mat &result);
        void adaptiveThreshold(cv::Mat &picture, cv::Mat &result);

        ~Filters();
};

#endif