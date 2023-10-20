#include <iostream>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/core.hpp>
#include <tesseract/baseapi.h>
#include <leptonica/allheaders.h>
#include "filters.h"
#include "processing.h"


int main(void)
{
    Filters filter;
    Processing processing;
    std::string path;
    
    std::cout << "Enter file path: ";
    std::cin >> path;

    cv::Mat img = cv::imread(path, cv::IMREAD_GRAYSCALE);
    cv::Mat addedFilter, processedImage;

    if (img.empty()) {
        std::cerr << "Image not found or couldn't be loaded." << std::endl;
        return -1;
    }

    filter.addBilateralFilter(img, addedFilter);
    filter.addWeight(addedFilter, img, addedFilter);
    filter.gaussianBlur(addedFilter, addedFilter);
    filter.scaleAbs(addedFilter, addedFilter);
    filter.threshold(addedFilter, addedFilter);
    filter.~Filters();

    processing.dilate(addedFilter, processedImage);
    processing.~Processing();

    tesseract::TessBaseAPI ocr;

    if (ocr.Init(NULL, "eng")) {
        std::cerr << "Could not initialize Tesseract." << std::endl;
        return -1;
    }

    ocr.SetImage(processedImage.data, processedImage.cols, processedImage.rows, 3, processedImage.step);
    ocr.Recognize(0);

    std::string extractedText = ocr.GetUTF8Text();
    std::cout << "\nExtracted text: \n" << extractedText << std::endl;

    cv::namedWindow("Filter", cv::WINDOW_NORMAL);
    cv::imshow("Filter", processedImage);

    cv::waitKey(0);

    return 0;
}