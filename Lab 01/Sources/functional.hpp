#ifndef FUNCTIONAL_HPP
#define FUNCTIONAL_HPP 
#include <opencv2/opencv.hpp>


class ImageManipulation {
public:
    // Clip pixel p into range [0, 255]
    static int pixelClip(int p);
    // Convert pixel with [b,g,r] into grayscale 
    static int pixelRGB2GRAY(int b, int g, int r);
    // Convert color image (src) into gray scale (dst)
    static void RGB2GRAY(cv::Mat & src, cv::Mat &dst);
    // Apply brightness and contrast value for the image (src) and save results in image (dst)
    static void applyBrightnessAndContrast(cv::Mat &src, cv::Mat&dst, int brightness, double contrast);
    // Do an convolution 2D between image (src) and kernel, save results in image (dst) 
    static void convolution(cv::Mat &src, cv::Mat&dst, cv::Mat& kernel);
    // Apply average filter with kernel(kernelSize, kernelSize) for image (src), save results in image (dst)
    static void applyAverageBlur(cv::Mat &src, cv::Mat&dst, int kernelSize);
    // Apply average filter with kernel(kernelSizeX, kernelSizeY) for image (src), save results in image (dst)
    static void applyAverageBlur(cv::Mat &src, cv::Mat&dst, int kernelSizeX, int kernelSizeY);
    // Apply gaussian filter with kernel(kernelSize, kernelSize) and sigma for image (src), save results in image (dst)
    static void applyGaussianBlur(cv::Mat &src, cv::Mat&dst, int kernel_size, double sigma);
    // Apply gaussian filter with kernel(kernelSizeX, kernelSizeY) and sigma for image (src), save results in image (dst)
    static void applyGaussianBlur(cv::Mat &src, cv::Mat&dst, int kernelSizeX, int kernelSizeY, double sigma);
};


#endif // FUNCTIONAL_HPP