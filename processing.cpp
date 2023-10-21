#include <iostream>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/core.hpp>
#include "processing.h"

Processing::Processing(){}

void Processing::erode(cv::Mat &picture, cv::Mat &result){
        cv::erode(picture, result, cv::getStructuringElement(cv::MORPH_RECT, 
                                cv::Size(3, 3), cv::Point(-1, -1)), cv::Point(-1, -1), 1);
}

void Processing::dilate(cv::Mat &picture, cv::Mat &result){
        cv::dilate(picture, result, cv::getStructuringElement(cv::MORPH_RECT, 
                                cv::Size(3, 3), cv::Point(-1, -1)), cv::Point(-1, -1), 1);
}

void Processing::sobel(cv::Mat &picture, cv::Mat &result){
        cv::Sobel(picture, result, CV_8UC1, 1, 1, 1);
}

Processing::~Processing(){}