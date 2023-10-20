#include "filters.h"
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/core.hpp>

Filters::Filters(){}

void Filters::addBilateralFilter(cv::Mat &picture, cv::Mat &result){
    cv::bilateralFilter(picture, result, 20, 150, 75);
}

void Filters::addWeight(cv::Mat &picture, cv::Mat &picture1, cv::Mat &result){
    cv::addWeighted(picture, 1.2, picture1, 0, 0, result);
}

void Filters::gaussianBlur(cv::Mat &picture, cv::Mat &result){
    cv::GaussianBlur(picture, result, cv::Size(3, 3), 0);
} 

void Filters::scaleAbs(cv::Mat &picture, cv::Mat &result){
    cv::convertScaleAbs(picture, result, 1.5, -0.5);
}

void Filters::threshold(cv::Mat &picture, cv::Mat &result){
    cv::threshold(picture, result, 190, 255, 0);
}

Filters::~Filters(){}