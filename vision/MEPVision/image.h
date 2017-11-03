#ifndef IMAGE_H
#define IMAGE_H

#include <opencv2/core/mat.hpp>

struct Image
{
    Image();
    Image(cv::Mat _img);
    Image(const Image& other);
    Image(Image&& other);
    Image& operator=(const Image& other);
    Image& operator=(Image&& other);
    void clear();

    cv::Mat img;
};

#endif // IMAGE_H
