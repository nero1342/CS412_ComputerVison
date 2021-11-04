#ifndef FUNCTIONAL_HPP
#define FUNCTIONAL_HPP 

#include <opencv2/opencv.hpp>

void RGB2GRAY(cv::Mat & image);
void applyBrightnessAndContrast(cv::Mat &image, cv::Mat&dst, int brightness, double contrast);

void applyMedianBlur(cv::Mat &src, cv::Mat&dst, int kernel_size);
void applyMedianBlur(cv::Mat &src, cv::Mat&dst, int kernel_size_x, int kernel_size_y);

void applyGaussianBlur(cv::Mat &src, cv::Mat&dst, int kernel_size, double sigma);
void applyGaussianBlur(cv::Mat &src, cv::Mat&dst, int kernel_size_x, int kernel_size_y, double sigma);


#endif // FUNCTIONAL_HPP