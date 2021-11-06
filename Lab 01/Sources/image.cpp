#include "image.hpp"
#include "functional.hpp"
#include "callback.hpp"

bool Image::readImage(string imagePath) {
    image = imread(imagePath);

    // Check for failure
    if (image.empty()) {
        cout << "Could not open or find the image" << endl;
        return -1;
    }
    initImage(imagePath);
    return 0;
}

void Image::initImage(string imagePath) {
    src = image.clone();
    dst = src.clone();
    
    srcWindowName = "Input: " + imagePath; //Name of the window
    destWindowName = "Output: " + imagePath; //Name of the window
    
    // real brightness = iBrightness - 50
    // real contrast = iContrast / 50 
    iBrightness = iContrast = 50;

    // Kernel size for avg or gaussian filter 
    iKernelSize = 1;

    // Sigma for gaussian filter; real sigma = iSigma / 2 
    iSigma = 2;

    // Gray scale 
    isGrayscale = false;
}

void Image::convertRGB2Grayscale() {
    ImageManipulation::RGB2GRAY(src, dst);
    image = dst.clone();
    isGrayscale = true;
}

void Image::changeBrightness() {
    namedWindow(destWindowName, 1);
    createTrackbar("Brightness", destWindowName, &iBrightness, 100, Callback::Brightness, this);
}

void Image::changeContrast() {
    namedWindow(destWindowName, 1);
    createTrackbar("Contrast", destWindowName, &iContrast, 100, Callback::Contrast, this);
}

void Image::doAverageFilter() {
    namedWindow(destWindowName, 1);
    createTrackbar("Avg Kernel Size", destWindowName, &iKernelSize, 50, Callback::AverageFilter, this);
}

void Image::doGaussianFilter() {
    namedWindow(destWindowName, 1);
    createTrackbar("Gaussian Kernel Size", destWindowName, &iKernelSize, 50, Callback::GaussianFilterKernelSize, this);
    createTrackbar("Gaussian Sigma", destWindowName, &iSigma, 10, Callback::GaussianFilterSigma, this);
}
    
void Image::showImage() {
    namedWindow(srcWindowName, 1);
    imshow(srcWindowName, src);
    namedWindow(destWindowName, 1);
    imshow(destWindowName, dst);
    // waitKey(0);
}

void Image::getDestWindowName(CommandLineParser parser) {
    if (parser.has("rgb2gray")) {
        destWindowName += " + GRAY";
    }
    if (parser.has("avg")) {
        destWindowName += " + Average Filter";
    }
    else if (parser.has("gauss")) {
        destWindowName += " + Gaussian Filter";
    }
    else {
        if (parser.has("brightness") && !parser.has("rgb2gray")) {
            destWindowName += " + BRIGHTNESS";
        }
        if (parser.has("contrast") && !parser.has("rgb2gray")) {
            destWindowName += " + CONTRAST";
        }
    }
}