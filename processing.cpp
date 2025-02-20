#include <iostream>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/core.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/photo.hpp>
#include "processing.h"

Processing::Processing(){}

void Processing::erode(cv::Mat &picture, cv::Mat &result){
        cv::erode(picture, result, cv::getStructuringElement(cv::MORPH_RECT, 
                                cv::Size(5, 5), cv::Point(-1, -1)), cv::Point(-1, -1), 1);
}

void Processing::dilate(cv::Mat &picture, cv::Mat &result){
        cv::dilate(picture, result, cv::getStructuringElement(cv::MORPH_RECT, 
                                cv::Size(3, 3), cv::Point(-1, -1)), cv::Point(-1, -1), 1);
}

void Processing::findContours(cv::Mat &picture){
        cv::findContours(picture, Processing::contours, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);
}

void Processing::drawContours(cv::Mat &result){
        cv::drawContours(result, Processing::contours, -1, cv::Scalar(255, 255, 255), 2);
}

void Processing::filter2D(cv::Mat &picture, cv::Mat &result){
        cv::filter2D(picture, result, picture.depth(), Processing::kernel);
}

Processing::~Processing(){}