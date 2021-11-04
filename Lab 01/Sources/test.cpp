#include <bits/stdc++.h>
#include <opencv2/opencv.hpp>
#include "functional.hpp"

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

Mat image;
string destWindowName;

void MyCallbackForBrightness(int iValueForBrightness, void *userData) {
    Mat dst;
    int iValueForContrast = *( static_cast<int*>(userData) );

    //Calculating brightness and contrast value
    int iBrightness = iValueForBrightness - 50;
    double dContrast = iValueForContrast / 50.0;

    //Calculated contrast and brightness value
    cout << "MyCallbackForBrightness : Contrast=" << dContrast << ", Brightness=" << iBrightness << endl;

    //adjust the brightness and contrast
    // image.convertTo(dst, -1, dContrast, iBrightness); 
    applyBrightnessAndContrast(image, dst, iBrightness, dContrast);
    //show the brightness and contrast adjusted image
    imshow(destWindowName, dst);
}

void MyCallbackForContrast(int iValueForContrast, void *userData) {
    Mat dst;
    int iValueForBrightness = *( static_cast<int*>(userData) );

    //Calculating brightness and contrast value
    int iBrightness = iValueForBrightness - 50;
    double dContrast = iValueForContrast / 50.0;

    //Calculated contrast and brightness value
    cout << "MyCallbackForContrast : Contrast=" << dContrast << ", Brightness=" << iBrightness << endl;

    //adjust the brightness and contrast
    // image.convertTo(dst, -1, dContrast, iBrightness); 
    applyBrightnessAndContrast(image, dst, iBrightness, dContrast);

    //show the brightness and contrast adjusted image
    imshow(destWindowName, dst);
}


void MyCallbackForAverageFilter(int kernel_size, void *temp) {
    Mat dst;
    cout << "MyCallbackForAverageFilter : KernelSize=" << kernel_size<< endl;

    applyMedianBlur(image, dst, kernel_size, kernel_size);

    //show the brightness and contrast adjusted image
    imshow(destWindowName, dst);
}

void MyCallbackForGaussianFilterKernelSize(int kernel_size, void *userData) {
    Mat dst;
    int iSigma = *( static_cast<int*>(userData) );
    double sigma = iSigma / 2.;

    cout << "MyCallbackForGaussianFilter : KernelSize=" << kernel_size<<  " sigma=" << sigma << endl;

    applyGaussianBlur(image, dst, kernel_size, kernel_size, sigma);

    //show the brightness and contrast adjusted image
    imshow(destWindowName, dst);
}

void MyCallbackForGaussianFilterSigma(int iSigma, void *userData) {
    Mat dst;
    int kernel_size = *( static_cast<int*>(userData) );
    double sigma = iSigma / 2.;

    cout << "MyCallbackForGaussianFilter : KernelSize=" << kernel_size<<  " sigma=" << sigma << endl;

    applyGaussianBlur(image, dst, kernel_size, kernel_size, sigma);

    //show the brightness and contrast adjusted image
    imshow(destWindowName, dst);
}



int main(int argc, char **argv)
{
    CommandLineParser parser(argc, argv, keys);
    parser.about("Application name v1.0.0");
    
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
    image = imread(imagePath);
    Mat src = image.clone();

    // Check for failure
    if (image.empty()) {
        cout << "Could not open or find the image" << endl;
        return -1;
    }
    // string sourceWindowName = "Source: " + imagePath; //Name of the window
    destWindowName = "Destination: " + imagePath; //Name of the window

    Mat dst = image.clone();
    if (parser.has("rgb2gray")) {
        destWindowName += " + GRAY";
        RGB2GRAY(dst);
        image = dst.clone();
    }
    namedWindow(destWindowName, 1);

    bool isGrayscale = dst.channels() == 1;
    
    if (parser.has("avg")) {
        destWindowName += " + Average Filter"; //Name of the window
        namedWindow(destWindowName, 1);

        int iKernelSize = 1;
        createTrackbar("Avg Kernel Size", destWindowName, &iKernelSize, 50, MyCallbackForAverageFilter, &iKernelSize);
    }
    else if (parser.has("gauss")) {
        destWindowName += " + Gaussian Filter"; //Name of the window
        namedWindow(destWindowName, 1);

        int iKernelSize = 1;
        int iSigma = 2;
        createTrackbar("Gaussian Kernel Size", destWindowName, &iKernelSize, 50, MyCallbackForGaussianFilterKernelSize, &iSigma);
        createTrackbar("Gaussian Sigma", destWindowName, &iSigma, 10, MyCallbackForGaussianFilterSigma, &iKernelSize);
    }
    else {
        int iValueForBrightness = 50;
        int iValueForContrast = 50;
        //Create track bar to change brightness
        if (parser.has("brightness") && !isGrayscale) {
            destWindowName += " + BRIGHTNESS"; //Name of the window
            namedWindow(destWindowName, 1);

            createTrackbar("Brightness", destWindowName, &iValueForBrightness, 100, MyCallbackForBrightness, &iValueForContrast);
        }
        //Create track bar to change contrast
        if (parser.has("contrast") && !isGrayscale) {
            destWindowName += " + CONTRAST"; //Name of the window
            namedWindow(destWindowName, 1);

            createTrackbar("Contrast", destWindowName, &iValueForContrast, 100, MyCallbackForContrast, &iValueForBrightness);
        }
    }


    

    imshow(destWindowName, dst); // Show our image inside the created window.
    waitKey(0); // Wait for any keystroke in the window
    destroyWindow(destWindowName); //destroy the created window
    return 0;
}
