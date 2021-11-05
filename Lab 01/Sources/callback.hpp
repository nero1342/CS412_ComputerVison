#ifndef CALLBACK_HPP
#define CALLBACK_HPP 

namespace Callback {
    void Brightness(int iValueForBrightness, void *userData);
    void Contrast(int iValueForContrast, void *userData);
    void AverageFilter(int kernel_size, void *temp);
    void GaussianFilterKernelSize(int kernel_size, void *userData);
    void GaussianFilterSigma(int iSigma, void *userData);
};

#endif // CALLBACK_HPP 
