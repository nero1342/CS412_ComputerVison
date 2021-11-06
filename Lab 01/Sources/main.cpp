#include <bits/stdc++.h>
#include <opencv2/opencv.hpp>
#include "image.hpp"

using namespace cv;
using namespace std;

const string keys = {
        "{help h usage ? |      | print this message   }"
        "{rgb2gray      |      | convert rgb image to grayscale image   }"
        "{brightness    |      | add trackbar to modify brightness  }"
        "{contrast      |      | add trackbar to modify contrast               }"
        "{avg           |      | average filter operator  }"
        "{gauss         |      | gaussian filter operator  }"
        "{@FileNameInput |<none>| path to input image   }"
};


int main(int argc, char **argv)
{
    CommandLineParser parser(argc, argv, keys);
    parser.about("CS412 - Computer Vision - Lab 01 - Image Manipulation");
    
    if (!parser.check()) {
        parser.printErrors();
        return 0;
    }
    
    if (parser.has("help")) {
        parser.printMessage();
        return 0;
    }

    string imagePath = parser.get<string>("@FileNameInput");
    // Read the image file
    
    Image image;
    if (image.readImage(imagePath)) {
        return 0;
    }

    image.getDestWindowName(parser);

    if (parser.has("rgb2gray")) {
        image.convertRGB2Grayscale();
    }

    if (parser.has("avg")) {
        image.doAverageFilter();
    }
    else if (parser.has("gauss")) {
        image.doGaussianFilter();   
    }
    else {
        //Create track bar to change brightness
        if (parser.has("brightness") && !image.isGrayscale) {
            image.changeBrightness();
        }
        //Create track bar to change contrast
        if (parser.has("contrast") && !image.isGrayscale) {
            image.changeContrast();
        }
    }

    image.showImage();
    waitKey(0);
    return 0;
}
