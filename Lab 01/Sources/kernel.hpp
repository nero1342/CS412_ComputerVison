#ifndef KERNEL_HPP
#define KERNEL_HPP 

#include <opencv2/opencv.hpp>

class Kernel{
public:
    static cv::Mat gaussianKernel(int kernelSizeX, int kernelSizeY, double sigma);
    static cv::Mat averageKernel(int kernelSizeX, int kernelSizeY);
};

#endif // KERNEL_HPP