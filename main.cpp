#include <iostream>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/core.hpp>
#include <tesseract/baseapi.h>
#include <leptonica/allheaders.h>
#include <cstdlib>
#include "filters.h"
#include "processing.h"


int main(int argc, char *argv[])
{
    Filters filter;
    Processing processing;

    if(argc != 2){
        std::cout << "Usage: " << argv[0] << " + <image_path>" << std::endl;
        return -1;
    }

    cv::Mat img = cv::imread(argv[1], cv::IMREAD_COLOR);
    cv::Mat processedImage;

    if (img.empty()) {
        std::cerr << "Image not found or couldn't be loaded." << std::endl;
        return -1;
    }
    
    filter.addBilateralFilter(img, processedImage);
    filter.addWeight(processedImage, img, processedImage);
    filter.gaussianBlur(processedImage, processedImage);
    filter.scaleAbs(processedImage, processedImage);
    filter.threshold(processedImage, processedImage);

    processing.erode(processedImage, processedImage);
    filter.convertToGrayscale(processedImage, processedImage);
    processing.findContours(processedImage);

    processing.drawContours(processedImage);
    processing.filter2D(processedImage, processedImage);
    filter.convertToColor(processedImage, processedImage);

    tesseract::TessBaseAPI ocr;

    std::string tessdataPath = "/usr/share/tessdata/";
    setenv("TESSDATA_PREFIX", tessdataPath.c_str(), 1);

    if (ocr.Init(NULL, "eng+srp_latn")) {
        std::cerr << "Could not initialize Tesseract." << std::endl;
        return -1;
    }

    ocr.SetPageSegMode(tesseract::PSM_AUTO);

    ocr.SetImage(processedImage.data, processedImage.cols, processedImage.rows, 3, processedImage.step);
    ocr.Recognize(0);

    std::string extractedText = ocr.GetUTF8Text();
    std::cout << "\nExtracted text: \n" << extractedText << std::endl;

    cv::namedWindow("Contours", cv::WINDOW_NORMAL);
    cv::imshow("Contours", processedImage);
    cv::waitKey(0);

    return 0;
}

    /*while (1){
        int c = cv::waitKey(1);

        if((char) c == 'q'){
            std::cout << "Exit" << std::endl;
            break;
        } else if ((char) c == 'b'){
            std::cout << "Pressed B" << std::endl;
            processing.h += 2;
            std::cout << "h value: " << processing.h << std::endl;
            processing.removeNoise(processedImage, test);
        } else if ((char) c == 'c'){
            std::cout << "Pressed C" << std::endl;
            processing.h -= 2;
            std::cout << "h value: " << processing.h << std::endl;
            processing.removeNoise(processedImage, test);
        } else if ((char) c == 'd'){
            std::cout << "Pressed D" << std::endl;
            processing.teplateWindowSize += 1;
            std::cout << "teplateWindowSize value: " << processing.teplateWindowSize << std::endl;
            processing.removeNoise(processedImage, test);
        } else if ((char) c == 'e'){
            std::cout << "Pressed E" << std::endl;
            processing.teplateWindowSize -= 1;
            std::cout << "teplateWindowSize value: " << processing.teplateWindowSize << std::endl;
            processing.removeNoise(processedImage, test);
        } else if ((char) c == 'f'){
            std::cout << "Pressed D" << std::endl;
            processing.searchWindowSize += 1;
            std::cout << "searchWindowSize value: " << processing.searchWindowSize << std::endl;
            processing.removeNoise(processedImage, test);
        } else if ((char) c == 'g'){
            std::cout << "Pressed E" << std::endl;
            processing.searchWindowSize -= 1;
            std::cout << "searchWindowSize value: " << processing.searchWindowSize << std::endl;
            processing.removeNoise(processedImage, test);
        }

        cv::namedWindow("Before", cv::WINDOW_NORMAL);
        cv::imshow("Before", processedImage);

        cv::namedWindow("Filter", cv::WINDOW_NORMAL);
        cv::imshow("Filter", test);
    }*/