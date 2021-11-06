#include "kernel.hpp"

cv::Mat Kernel::gaussianKernel(int kernelSizeX, int kernelSizeY, double sigma) {
    cv::Mat kernel(kernelSizeX, kernelSizeY, CV_32FC1, cv::Scalar(0));
    int mx = kernelSizeX / 2, my = kernelSizeY / 2;
    double sum = 0;
    for (int i = 0; i < kernelSizeX; ++i) {
        for (int j = 0; j < kernelSizeY; ++j) {
            int x = i - mx, y = j - my;
            kernel.at<float>(i, j) = exp(-(x * x + y * y) / (sigma * sigma * 2.0));
            sum += kernel.at<float>(i, j);
        }
    }
    for (int i = 0; i < kernelSizeX; ++i) {
        for (int j = 0; j < kernelSizeY; ++j) {
            kernel.at<float>(i, j) /= sum;
            std::cerr << std::fixed << std::setprecision(5) << kernel.at<float>(i, j) << " \n"[j + 1 == kernelSizeY];
        }
    }
    return kernel;
}

cv::Mat Kernel::averageKernel(int kernelSizeX, int kernelSizeY) {
    cv::Mat kernel(kernelSizeX, kernelSizeY, CV_32FC1, cv::Scalar(0));
    double val = 1. / kernelSizeX  / kernelSizeY;
    for (int i = 0; i < kernelSizeX; ++i) {
        for (int j = 0; j < kernelSizeY; ++j) {
            kernel.at<float>(i, j) = val;
        }
    }
    return kernel;
}