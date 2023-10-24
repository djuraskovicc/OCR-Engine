#include <iostream>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/core.hpp>
#include <tesseract/baseapi.h>
#include <tesseract/ocrclass.h>
#include <leptonica/allheaders.h>
#include <cstdlib>
#include "filters.h"
#include "processing.h"


int main(void)
{
    Filters filter;
    Processing processing;
    std::string path;
    
    std::cout << "Enter file path: ";
    std::cin >> path;

    cv::Mat img = cv::imread(path, cv::IMREAD_COLOR);
    cv::Mat addedFilter, processedImage, erode;

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

    processing.erode(addedFilter, processedImage);
    processing.~Processing();

    tesseract::TessBaseAPI ocr;

    std::string tessdataPath = "/usr/share/tessdata/";
    setenv("TESSDATA_PREFIX", tessdataPath.c_str(), 1);

    if (ocr.Init(NULL, "eng+srp_latn")) {
        std::cerr << "Could not initialize Tesseract." << std::endl;
        return -1;
    }

    ocr.SetPageSegMode(tesseract::PSM_SINGLE_BLOCK);

    ocr.SetImage(processedImage.data, processedImage.cols, processedImage.rows, 3, processedImage.step);
    ocr.Recognize(0);

    std::string extractedText = ocr.GetUTF8Text();
    std::cout << "\nExtracted text: \n" << extractedText << std::endl;

    cv::namedWindow("Filter", cv::WINDOW_NORMAL);
    cv::imshow("Filter", processedImage);

    cv::waitKey(0);

    return 0;
}


    /*while (1){
        int c = cv::waitKey(1);

        if((char) c == 'q'){
            break;
        } else if ((char) c == 'b'){
            std::cout << "Pressed B" << std::endl;
            processing.ksize += 2;
            std::cout << "ksize value: " << processing.ksize << std::endl;
            processing.erode(addedFilter, processedImage);
        } else if ((char) c == 'c'){
            std::cout << "Pressed C" << std::endl;
            processing.ksize -= 2;
            std::cout << "ksize value: " << processing.ksize << std::endl;
            processing.erode(addedFilter, processedImage);
        } else if ((char) c == 'd'){
            std::cout << "Pressed D" << std::endl;
            processing.point += 1;
            std::cout << "point value: " << processing.point << std::endl;
            processing.erode(addedFilter, processedImage);
        } else if ((char) c == 'e'){
            std::cout << "Pressed E" << std::endl;
            processing.point -= 1;
            std::cout << "point value: " << processing.point << std::endl;
            processing.erode(addedFilter, processedImage);
        } else if ((char) c == 'f'){
            std::cout << "Pressed D" << std::endl;
            processing.ksize += 1;
            std::cout << "ksize value: " << processing.ksize << std::endl;
            processing.sobel(processedImage, sobel);
        } else if ((char) c == 'g'){
            std::cout << "Pressed E" << std::endl;
            processing.ksize -= 1;
            std::cout << "ksize value: " << processing.ksize << std::endl;
            processing.sobel(processedImage, sobel);
        }

        cv::namedWindow("Filter", cv::WINDOW_NORMAL);
        cv::imshow("Filter", processedImage);
    }*/
