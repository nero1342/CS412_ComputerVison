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
    ImageManipulation::applyBrightnessAndContrast(image.image, image.dst, iBrightness, dContrast);
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
    ImageManipulation::applyBrightnessAndContrast(image.image, image.dst, iBrightness, dContrast);
    //show the brightness and contrast adjusted image
    image.showImage();
}

void Callback::AverageFilter(int kernelSize, void *userData) {
    Image image = *( static_cast<Image*>(userData) );
    
    cout << "AverageFilter : KernelSize=" << kernelSize<< endl;

    ImageManipulation::applyAverageBlur(image.image, image.dst, kernelSize, kernelSize);

    //show the brightness and contrast adjusted image
    image.showImage();
}

void Callback::GaussianFilterKernelSize(int kernelSize, void *userData) {
    Image image = *( static_cast<Image*>(userData) );
    int iSigma = image.iSigma;
    double sigma = iSigma / 2.;

    cout << "GaussianFilterKernelSize : KernelSize=" << kernelSize<<  " sigma=" << sigma << endl;

    ImageManipulation::applyGaussianBlur(image.image, image.dst, kernelSize, kernelSize, sigma);

    //show the brightness and contrast adjusted image
    image.showImage();
}

void Callback::GaussianFilterSigma(int iSigma, void *userData) {
    Image image = *( static_cast<Image*>(userData) );
    int kernelSize = image.iKernelSize;
    double sigma = iSigma / 2.;

    cout << "GaussianFilterSigma : KernelSize=" << kernelSize<<  " sigma=" << sigma << endl;

    ImageManipulation::applyGaussianBlur(image.image, image.dst, kernelSize, kernelSize, sigma);

    //show the brightness and contrast adjusted image
    image.showImage();
}
