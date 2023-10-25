#ifndef FUNCTIONS_H
#define FUNCTIONS_H
#include <opencv2/highgui.hpp>

class Filters {
    public:
        Filters();

        void addBilateralFilter(cv::Mat &picture, cv::Mat &result);
        void addWeight(cv::Mat &picture, cv::Mat &picture1, cv::Mat &result);
        void gaussianBlur(cv::Mat &picture, cv::Mat &result);
        void scaleAbs(cv::Mat &picture, cv::Mat &result);
        void threshold(cv::Mat &picture, cv::Mat &result);
        void adaptiveThreshold(cv::Mat &picture, cv::Mat &result);
        void convertToGrayscale(cv::Mat &picture, cv::Mat &result);

        ~Filters();
};

#endif