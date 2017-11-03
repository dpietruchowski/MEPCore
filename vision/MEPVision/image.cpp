#include "image.h"

#include <iostream>

Image::Image()
{ }

Image::Image(cv::Mat _img): img(_img)
{

}

Image::Image(const Image &other): img(other.img.clone())
{
    //std::cout << "Image copy constructor" << std::endl;
}

Image::Image(Image &&other): img(other.img)
{
    other.img.release();
    //std::cout << "Image move constructor" << std::endl;
}

Image& Image::operator=(const Image &other)
{
    img = other.img;
    //std::cout << "Image copy assignment" << std::endl;
    return *this;
}

Image& Image::operator=(Image &&other)
{
    img = other.img;
    other.img.release();
    //std::cout << "Image move assignment" << std::endl;
    return *this;
}

void Image::clear()
{
    img.release();
}
