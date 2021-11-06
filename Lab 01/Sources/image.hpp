#ifndef IMAGE_HPP
#define IMAGE_HPP

#include <string>
#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std ;

class Image {
public:
    // Variable
    Mat image, src, dst;
    string srcWindowName, destWindowName;
    // For grayscale 
    bool isGrayscale;
    // For Brightness and Contrast
    int iBrightness, iContrast;
    // For Avg filter and gauss filter
    int iKernelSize, iSigma;

    // 
    bool readImage(string imagePath);    
    void initImage(string imagePath);
    void getDestWindowName(CommandLineParser parser);
    void convertRGB2Grayscale();
    void changeBrightness();
    void changeContrast();
    void doAverageFilter();
    void doGaussianFilter();
    void showImage();
};

#endif // IMAGE_HPP