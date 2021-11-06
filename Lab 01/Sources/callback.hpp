#ifndef CALLBACK_HPP
#define CALLBACK_HPP 

class Callback {
public:
    static void Brightness(int iValueForBrightness, void *userData);
    static void Contrast(int iValueForContrast, void *userData);
    static void AverageFilter(int kernelSize, void *temp);
    static void GaussianFilterKernelSize(int kernelSize, void *userData);
    static void GaussianFilterSigma(int iSigma, void *userData);
};

#endif // CALLBACK_HPP 
