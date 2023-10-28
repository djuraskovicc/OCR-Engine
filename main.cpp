#include <iostream>
#include <fstream>
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
    Filters *filter = new Filters();
    Processing *processing = new Processing();

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
    
    filter->addBilateralFilter(img, processedImage);
    filter->addWeight(processedImage, img, processedImage);
    filter->gaussianBlur(processedImage, processedImage);
    filter->scaleAbs(processedImage, processedImage);
    filter->threshold(processedImage, processedImage);

    processing->erode(processedImage, processedImage);
    filter->convertToGrayscale(processedImage, processedImage);
    processing->findContours(processedImage);

    processing->drawContours(processedImage);
    processing->filter2D(processedImage, processedImage);
    filter->convertToColor(processedImage, processedImage);
    filter->~Filters();
    processing->~Processing();

    tesseract::TessBaseAPI *ocr = new tesseract::TessBaseAPI();

    std::string tessdataPath = "/usr/share/tessdata/";
    setenv("TESSDATA_PREFIX", tessdataPath.c_str(), 1);

    if (ocr->Init(NULL, "eng+srp_latn", tesseract::OEM_LSTM_ONLY)) {
        std::cerr << "Could not initialize Tesseract." << std::endl;
        return -1;
    }

    ocr->SetPageSegMode(tesseract::PSM_SINGLE_BLOCK);

    ocr->SetImage(processedImage.data, processedImage.cols, processedImage.rows, 3, processedImage.step);
    ocr->Recognize(0);

    std::string extractedText = ocr->GetUTF8Text();
    std::ofstream outputFile("output.txt");

    if (!outputFile) {
        std::cerr << "Could not open the output file." << std::endl;
        return -1;
    }
    
    outputFile << extractedText;
    outputFile.close();
    ocr->End();

    cv::namedWindow("Contours", cv::WINDOW_NORMAL);
    cv::imshow("Contours", processedImage);
    cv::waitKey(0);

    return 0;
}