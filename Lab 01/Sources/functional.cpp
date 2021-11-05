#include <opencv2/opencv.hpp>

#include "functional.hpp"

int pixelClip(int p) { return std::max(0, std::min(255, p)); }

int pixelRGB2GRAY(int b, int g, int r) {
    int gray = 0.2126 * r + 0.7152 * g + 0.0722 * b;
    gray = pixelClip(gray);
    return gray;
}

void RGB2GRAY(cv::Mat &image) {
    if (image.channels() == 1) return;
    int height = image.rows;  
    int width = image.cols;  

    cv::Mat gray = cv::Mat(height, width, CV_8UC1);
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            cv::Vec3b& pixel = image.at<cv::Vec3b>(i, j);
            gray.at<uchar>(i, j) = pixelRGB2GRAY(pixel[0], pixel[1], pixel[2]);
        }
    }
    // std::cout << "Hello\n";
    swap(image, gray); 
}

void applyBrightnessAndContrast(cv::Mat &src, cv::Mat &dst, int brightness, double contrast) {
    // if (image.channels() == 1) return;
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

void applyMedianBlur(cv::Mat &src, cv::Mat&dst, int kernel_size) {
    applyMedianBlur(src, dst, kernel_size, kernel_size);
}

// cv::Mat convolution(cv::Mat &src, cv::Mat &kernel) {
//     int height = src.rows, width = src.cols;  
//     int kernel_size_x = kernel.rows, kernel_size_y = kernel.cols;
//     cv::Mat dst = cv::Mat(height, width, src.channels() == 3 ? CV_8UC3 : CV_8UC1, cv::Scalar(0));

//     for (int i = 0; i < height; ++i) {
//         for (int j = 0; j < width; ++j) {
//             double pixel[3] = {};
//             for (int kx = -kernel_size_x / 2; kx <= (kernel_size_x - 1) / 2; ++kx) {
//                 for (int ky = -kernel_size_y / 2; ky <= (kernel_size_y - 1) / 2; ++ky) {
//                     int ki = i + kx, kj = j + ky;
//                     if (0 <= ki && ki < height && 0 <= kj && kj < width) {
//                         if (isGrayscale) pixel[0] += src.at<uchar>(ki, kj) * kernel[kx + kernel_size_x / 2][ky + kernel_size_y / 2];
//                         else {
//                             cv::Vec3b& pixel_src = src.at<cv::Vec3b>(ki, kj);
//                             for (int k = 0; k < 3; ++k) {
//                                 pixel[k] += pixel_src[k] * kernel[kx + kernel_size_x / 2][ky + kernel_size_y / 2];;
//                             }
//                         }    
//                     }
//                 }    
//             }
//             if (isGrayscale) {
//                 dst.at<uchar>(i, j) = pixel[0];
//             } else {
//                 cv::Vec3b& pixel_dst = dst.at<cv::Vec3b>(i, j);
//                 for (int k = 0; k < 3; ++k)
//                     pixel_dst[k] = pixel[k];
//             }
//         }
//     }   
// }

void applyMedianBlur(cv::Mat &src, cv::Mat&dst, int kernel_size_x, int kernel_size_y) {
    int height = src.rows;  
    int width = src.cols;  
    dst = cv::Mat(height, width, src.channels() == 3 ? CV_8UC3 : CV_8UC1, cv::Scalar(0));
    if (!kernel_size_x || !kernel_size_y) return;
    bool isGrayscale = src.channels() == 1;
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            int pixel[3] = {};
            for (int kx = -kernel_size_x / 2; kx <= (kernel_size_x - 1) / 2; ++kx) {
                for (int ky = -kernel_size_y / 2; ky <= (kernel_size_y - 1) / 2; ++ky) {
                    int ki = i + kx, kj = j + ky;
                    if (0 <= ki && ki < height && 0 <= kj && kj < width) {
                        if (isGrayscale) pixel[0] += src.at<uchar>(ki, kj);
                        else {
                            cv::Vec3b& pixel_src = src.at<cv::Vec3b>(ki, kj);
                            for (int k = 0; k < 3; ++k) {
                                pixel[k] += pixel_src[k];
                            }
                        }    
                    }
                }    
            }
            if (isGrayscale) {
                dst.at<uchar>(i, j) = pixel[0] / (kernel_size_x * kernel_size_y);
            } else {
                cv::Vec3b& pixel_dst = dst.at<cv::Vec3b>(i, j);
                for (int k = 0; k < 3; ++k)
                    pixel_dst[k] = pixel[k] / (kernel_size_x * kernel_size_y);
            }
        }
    }
}

std::vector< std::vector< double> > gaussianKernel(int kernel_size_x, int kernel_size_y, double sigma) {
    std::vector< std::vector<double> > kernel(kernel_size_x, std::vector<double> (kernel_size_y));
    int mx = kernel_size_x / 2, my = kernel_size_y / 2;
    double sum = 0;
    for (int i = 0; i < kernel_size_x; ++i) {
        for (int j = 0; j < kernel_size_y; ++j) {
            int x = i - mx, y = j - my;
            kernel[i][j] = exp(-(x * x + y * y) / (sigma * sigma * 2.0));
            sum += kernel[i][j];
        }
    }
    for (int i = 0; i < kernel_size_x; ++i) {
        for (int j = 0; j < kernel_size_y; ++j) {
            kernel[i][j] /= sum;
            std::cerr << std::fixed << std::setprecision(5) << kernel[i][j] << " \n"[j + 1 == kernel_size_y];
        }
    }
    return kernel;
}


void applyGaussianBlur(cv::Mat &src, cv::Mat&dst, int kernel_size, double sigma) {
    applyGaussianBlur(src, dst, kernel_size, kernel_size, sigma);
}

void applyGaussianBlur(cv::Mat &src, cv::Mat&dst, int kernel_size_x, int kernel_size_y, double sigma) {
    int height = src.rows;  
    int width = src.cols;  
    dst = cv::Mat(height, width, src.channels() == 3 ? CV_8UC3 : CV_8UC1, cv::Scalar(0));
    if (!kernel_size_x || !kernel_size_y) return;
    bool isGrayscale = src.channels() == 1;
    std::vector< std::vector< double > > kernel = gaussianKernel(kernel_size_x, kernel_size_y, sigma);

    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            double pixel[3] = {};
            for (int kx = -kernel_size_x / 2; kx <= (kernel_size_x - 1) / 2; ++kx) {
                for (int ky = -kernel_size_y / 2; ky <= (kernel_size_y - 1) / 2; ++ky) {
                    int ki = i + kx, kj = j + ky;
                    if (0 <= ki && ki < height && 0 <= kj && kj < width) {
                        if (isGrayscale) pixel[0] += src.at<uchar>(ki, kj) * kernel[kx + kernel_size_x / 2][ky + kernel_size_y / 2];
                        else {
                            cv::Vec3b& pixel_src = src.at<cv::Vec3b>(ki, kj);
                            for (int k = 0; k < 3; ++k) {
                                pixel[k] += pixel_src[k] * kernel[kx + kernel_size_x / 2][ky + kernel_size_y / 2];;
                            }
                        }    
                    }
                }    
            }
            if (isGrayscale) {
                dst.at<uchar>(i, j) = pixel[0];
            } else {
                cv::Vec3b& pixel_dst = dst.at<cv::Vec3b>(i, j);
                for (int k = 0; k < 3; ++k)
                    pixel_dst[k] = pixel[k];
            }
        }
    }   
}