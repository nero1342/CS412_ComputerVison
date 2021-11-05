#include <opencv2/opencv.hpp>

#include "callback.hpp"
#include "functional.hpp"
#include "image.hpp"

void Callback::Brightness(int iValueForBrightness, void *userData) {
    Image image = *( static_cast<Image*>(userData) );
    int iValueForContrast = image.iContrast;
    
    //Calculating brightness and contrast value
    int iBrightness = iValueForBrightness - 50;
    double dContrast = iValueForContrast / 50.0;

    //Calculated contrast and brightness value
    cout << "Brightness : Contrast=" << dContrast << ", Brightness=" << iBrightness << endl;

    //adjust the brightness and contrast
    applyBrightnessAndContrast(image.image, image.dst, iBrightness, dContrast);
    //show the brightness and contrast adjusted image
    image.showImage();
}

void Callback::Contrast(int iValueForContrast, void *userData) {
    Image image = *( static_cast<Image*>(userData) );
    int iValueForBrightness = image.iContrast;
    
    //Calculating brightness and contrast value
    int iBrightness = iValueForBrightness - 50;
    double dContrast = iValueForContrast / 50.0;

    //Calculated contrast and brightness value
    cout << "Contrast : Contrast=" << dContrast << ", Brightness=" << iBrightness << endl;

    //adjust the brightness and contrast
    applyBrightnessAndContrast(image.image, image.dst, iBrightness, dContrast);
    //show the brightness and contrast adjusted image
    image.showImage();
}

void Callback::AverageFilter(int kernel_size, void *userData) {
    Image image = *( static_cast<Image*>(userData) );
    
    cout << "AverageFilter : KernelSize=" << kernel_size<< endl;

    applyMedianBlur(image.image, image.dst, kernel_size, kernel_size);

    //show the brightness and contrast adjusted image
    image.showImage();
}

void Callback::GaussianFilterKernelSize(int kernel_size, void *userData) {
    Image image = *( static_cast<Image*>(userData) );
    int iSigma = image.iSigma;
    double sigma = iSigma / 2.;

    cout << "GaussianFilterKernelSize : KernelSize=" << kernel_size<<  " sigma=" << sigma << endl;

    applyGaussianBlur(image.image, image.dst, kernel_size, kernel_size, sigma);

    //show the brightness and contrast adjusted image
    image.showImage();
}

void Callback::GaussianFilterSigma(int iSigma, void *userData) {
    Image image = *( static_cast<Image*>(userData) );
    int kernel_size = image.iKernelSize;
    double sigma = iSigma / 2.;

    cout << "GaussianFilterSigma : KernelSize=" << kernel_size<<  " sigma=" << sigma << endl;

    applyGaussianBlur(image.image, image.dst, kernel_size, kernel_size, sigma);

    //show the brightness and contrast adjusted image
    image.showImage();
}
