#include "filters.h"
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/core.hpp>

Filters::Filters(){}

void Filters::addBilateralFilter(cv::Mat &picture, cv::Mat &result){
    cv::bilateralFilter(picture, result, 10, 90, 35);
}

void Filters::addWeight(cv::Mat &picture, cv::Mat &picture1, cv::Mat &result){
    cv::addWeighted(picture, 1.4, picture1, 0, 10, result);
}

void Filters::gaussianBlur(cv::Mat &picture, cv::Mat &result){
    cv::GaussianBlur(picture, result, cv::Size(1, 1), 3);
}

void Filters::scaleAbs(cv::Mat &picture, cv::Mat &result){
    cv::convertScaleAbs(picture, result, 1.1, -2);
}

void Filters::threshold(cv::Mat &picture, cv::Mat &result){
    cv::threshold(picture, result, 155, 255, 0);
}

void Filters::adaptiveThreshold(cv::Mat &picture, cv::Mat &result){
    cv::adaptiveThreshold(picture, result, 255, 
                                cv::ADAPTIVE_THRESH_GAUSSIAN_C, cv::THRESH_BINARY, 35, 10);
}

void Filters::convertToGrayscale(cv::Mat &picture, cv::Mat &result){
    cv::cvtColor(picture, result, cv::COLOR_BGR2GRAY);
}

void Filters::convertToColor(cv::Mat &picture, cv::Mat &result){
    cv::cvtColor(picture, result, cv::COLOR_RGB2BGR);
}

Filters::~Filters(){}