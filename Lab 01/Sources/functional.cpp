#include "functional.hpp"
#include "kernel.hpp"

int ImageManipulation::pixelClip(int p) { return std::max(0, std::min(255, p)); }

int ImageManipulation::pixelRGB2GRAY(int b, int g, int r) {
    int gray = 0.2126 * r + 0.7152 * g + 0.0722 * b;
    gray = pixelClip(gray);
    return gray;
}

void ImageManipulation::RGB2GRAY(cv::Mat &src, cv::Mat &dst) {
    if (src.channels() == 1) return;
    int height = src.rows;  
    int width = src.cols;  

    dst = cv::Mat(height, width, CV_8UC1);
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            cv::Vec3b& pixel = src.at<cv::Vec3b>(i, j);
            dst.at<uchar>(i, j) = pixelRGB2GRAY(pixel[0], pixel[1], pixel[2]);
        }
    }
}

void ImageManipulation::applyBrightnessAndContrast(cv::Mat &src, cv::Mat &dst, int brightness, double contrast) {
    int height = src.rows;  
    int width = src.cols;
    dst = cv::Mat(height, width, CV_8UC3, cv::Scalar(0));
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            cv::Vec3b& pixel_src = src.at<cv::Vec3b>(i, j);
            cv::Vec3b& pixel_dst = dst.at<cv::Vec3b>(i, j);
            for (int k = 0; k < 3; ++k)
                pixel_dst[k] = pixelClip(contrast * pixel_src[k] + brightness);
        }
    }
}

void ImageManipulation::convolution(cv::Mat &src, cv::Mat&dst, cv::Mat& kernel) {
    int height = src.rows, width = src.cols;  
    int kernelSizeX = kernel.rows, kernelSizeY = kernel.cols;
    dst = cv::Mat(height, width, src.channels() == 3 ? CV_8UC3 : CV_8UC1, cv::Scalar(0));
    bool isGrayscale = src.channels() == 1;
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            double pixel[3] = {};
            for (int kx = -kernelSizeX / 2; kx <= (kernelSizeX - 1) / 2; ++kx) {
                for (int ky = -kernelSizeY / 2; ky <= (kernelSizeY - 1) / 2; ++ky) {
                    int ki = i + kx, kj = j + ky;
                    if (0 <= ki && ki < height && 0 <= kj && kj < width) {
                        if (isGrayscale) pixel[0] += src.at<uchar>(ki, kj) * kernel.at<float>(kx + kernelSizeX / 2, ky + kernelSizeY / 2);
                        else {
                            cv::Vec3b& pixel_src = src.at<cv::Vec3b>(ki, kj);
                            for (int k = 0; k < 3; ++k) {
                                pixel[k] += pixel_src[k] * kernel.at<float>(kx + kernelSizeX / 2, ky + kernelSizeY / 2);
                            }
                        }    
                    }
                }    
            }
            if (isGrayscale) {
                dst.at<uchar>(i, j) = pixel[0];
            } else {
                cv::Vec3b& pixel_dst = dst.at<cv::Vec3b>(i, j);
                for (int k = 0; k < 3; ++k) pixel_dst[k] = pixel[k];
            }
        }
    }   
}

void ImageManipulation::applyAverageBlur(cv::Mat &src, cv::Mat&dst, int kernelSize) {
    applyAverageBlur(src, dst, kernelSize, kernelSize);
}

void ImageManipulation::applyAverageBlur(cv::Mat &src, cv::Mat&dst, int kernelSizeX, int kernelSizeY) {
    if (!kernelSizeX || !kernelSizeY) return;
    cv::Mat kernel = Kernel::averageKernel(kernelSizeX, kernelSizeY);
    convolution(src, dst, kernel);
}

void ImageManipulation::applyGaussianBlur(cv::Mat &src, cv::Mat&dst, int kernelSize, double sigma) {
    applyGaussianBlur(src, dst, kernelSize, kernelSize, sigma);
}

void ImageManipulation::applyGaussianBlur(cv::Mat &src, cv::Mat&dst, int kernelSizeX, int kernelSizeY, double sigma) {
    if (!kernelSizeX || !kernelSizeY) return;
    cv::Mat kernel = Kernel::gaussianKernel(kernelSizeX, kernelSizeY, sigma);
    convolution(src, dst, kernel);
}