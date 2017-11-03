#include "functions.h"

#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace cv;

namespace {

void reconstruction(const cv::Mat& src, const cv::Mat& mask, cv::Mat& dst) {
    Mat invSrc;
    bitwise_not(src, invSrc);
    Mat invMask;
    bitwise_not(mask, invMask);
    Mat element = getStructuringElement(MORPH_ELLIPSE, Size(5,5));

    morphologyEx(invSrc, dst, MORPH_DILATE, element,Point(-1,-1), 1);
    bitwise_and(dst, invMask, dst);
    Mat prev = dst.clone();
    morphologyEx(dst, dst, MORPH_DILATE, element,Point(-1,-1), 1);
    bitwise_and(dst, invMask, dst);
    Mat tmp;
    bitwise_xor(dst, prev, tmp);
    int pixels = countNonZero(tmp);
    while(pixels != 0)
    {
        prev = dst.clone();
        morphologyEx(dst, dst, MORPH_DILATE, element,Point(-1,-1), 1);
        bitwise_and(dst, invMask, dst);
        bitwise_xor(dst, prev, tmp);
        pixels = countNonZero(tmp);
    }

    bitwise_not(dst, dst);
}

Mat createMask(int rows, int cols, int type) {
    Mat mask;
    mask = Mat(rows, cols, type);
    Point rook_points[1][20];
    rook_points[0][0] = Point( 0, 0 );
    rook_points[0][1] = Point( mask.cols, 0 );
    rook_points[0][2] = Point( mask.cols, mask.rows );
    rook_points[0][3] = Point( 0, mask.rows );
    const Point* ppt[1] = { rook_points[0] };
    int npt[] = { 4 };
    fillPoly(mask, ppt, npt, 1, 255);
    rectangle(mask, Point(0,0), Point(mask.cols-1, mask.rows-1), 0, 2);
    return mask;
}

}

Image erosion(const Args &src)
{
    if (src.size() != 1)
    {
        std::string exception = "Zla liczba argumentow";
        throw exception;
    }
    const Mat& src1 = src[0]->img;
    Mat element = getStructuringElement(MORPH_RECT,
                                        Size( 2*10 + 1, 2*10+1 ),
                                        Point( 10, 10 ) );
    Image image;
    erode(src1, image.img, element);
    return image;
}

Image dilation(const Args &src)
{
    if (src.size() != 1)
    {
        std::string exception = "Zla liczba argumentow";
        throw exception;
    }
    const Mat& src1 = src[0]->img;
    Mat element = getStructuringElement(MORPH_RECT,
                                        Size( 2*10 + 1, 2*10+1 ),
                                        Point( 10, 10 ) );
    Image image;
    dilate(src1, image.img, element);
    return image;
}

Image open(const Args &src)
{
    if (src.size() != 1)
    {
        std::string exception = "Zla liczba argumentow";
        throw exception;
    }
    const Mat& src1 = src[0]->img;
    Mat element = getStructuringElement(MORPH_RECT,
                                        Size( 2*10 + 1, 2*10+1 ),
                                        Point( 10, 10 ) );
    Image image;
    morphologyEx(src1, image.img, MORPH_OPEN, element);
    return image;
}

Image close(const Args &src)
{
    if (src.size() != 1)
    {
        std::string exception = "Zla liczba argumentow";
        throw exception;
    }
    const Mat& src1 = src[0]->img;
    Mat element = getStructuringElement(MORPH_RECT,
                                        Size( 2*10 + 1, 2*10+1 ),
                                        Point( 10, 10 ) );
    Image image;
    morphologyEx(src1, image.img, MORPH_CLOSE, element);
    return image;
}

Image blackHat(const Args &src)
{
    if (src.size() != 1)
    {
        std::string exception = "Zla liczba argumentow";
        throw exception;
    }
    const Mat& src1 = src[0]->img;
    Mat element = getStructuringElement(MORPH_RECT,
                                        Size( 2*10 + 1, 2*10+1 ),
                                        Point( 10, 10 ) );
    Image image;
    morphologyEx(src1, image.img, MORPH_BLACKHAT, element);
    return image;
}

Image gradient(const Args &src)
{
    if (src.size() != 1)
    {
        std::string exception = "Zla liczba argumentow";
        throw exception;
    }
    const Mat& src1 = src[0]->img;
    Mat element = getStructuringElement(MORPH_RECT,
                                        Size( 2*10 + 1, 2*10+1 ),
                                        Point( 10, 10 ) );
    Image image;
    morphologyEx(src1, image.img, MORPH_GRADIENT, element);
    return image;
}

Image bitwiseAnd(const Args &src)
{
    if (src.size() != 2)
    {
        std::string exception = "Zla liczba argumentow";
        throw exception;
    }
    const Mat& src1 = src[0]->img;
    const Mat& src2 = src[1]->img;
    Image image;
    bitwise_and(src1,src2,image.img);
    return image;
}

Image bitwiseXor(const Args &src)
{
    if (src.size() != 2)
    {
        std::string exception = "Zla liczba argumentow";
        throw exception;
    }
    const Mat& src1 = src[0]->img;
    const Mat& src2 = src[1]->img;
    Image image;
    bitwise_xor(src1,src2,image.img);
    return image;
}

Image bitwiseOr(const Args &src)
{
    if (src.size() != 2)
    {
        std::string exception = "Zla liczba argumentow";
        throw exception;
    }
    const Mat& src1 = src[0]->img;
    const Mat& src2 = src[1]->img;
    Image image;
    bitwise_or(src1,src2,image.img);
    return image;
}

Image bitwiseNot(const Args &src)
{
    if (src.size() != 1)
    {
        std::string exception = "Zla liczba argumentow";
        throw exception;
    }
    const Mat& src1 = src[0]->img;
    Image image;
    bitwise_not(src1, image.img);
    return image;
}

Image absDiff(const Args &src)
{
    if (src.size() != 2)
    {
        std::string exception = "Zla liczba argumentow";
        throw exception;
    }
    const Mat& src1 = src[0]->img;
    const Mat& src2 = src[1]->img;
    Image image;
    absdiff(src1,src2,image.img);
    return image;
}

Image addF(const Args &src)
{
    if (src.size() != 2)
    {
        std::string exception = "Zla liczba argumentow";
        throw exception;
    }
    const Mat& src1 = src[0]->img;
    const Mat& src2 = src[1]->img;
    Image image;
    add(src1,src2,image.img);
    return image;
}

Image minF(const Args &src)
{
    if (src.size() != 2)
    {
        std::string exception = "Zla liczba argumentow";
        throw exception;
    }
    const Mat& src1 = src[0]->img;
    const Mat& src2 = src[1]->img;
    Image image;
    min(src1,src2,image.img);
    return image;
}

Image maxF(const Args &src)
{
    if (src.size() != 2)
    {
        std::string exception = "Zla liczba argumentow";
        throw exception;
    }
    const Mat& src1 = src[0]->img;
    const Mat& src2 = src[1]->img;
    Image image;
    max(src1,src2,image.img);
    return image;
}

Image diff(const Args &src)
{
    if (src.size() != 2)
    {
        std::string exception = "Zla liczba argumentow";
        throw exception;
    }
    const Mat& src1 = src[0]->img;
    const Mat& src2 = src[1]->img;
    Mat sumAB;
    bitwise_or(src1, src2, sumAB); // A sum B
    bitwise_not(sumAB, sumAB);

    Image image;
    bitwise_or(src1, sumAB, image.img); // roznica A - A sum B
    return image;
}

Image recall(const Args &src)
{
    if (src.size() != 2)
    {
        std::string exception = "Zla liczba argumentow";
        throw exception;
    }
    const Mat& src1 = src[0]->img;
    const Mat& src2 = src[1]->img;
    Image image;
    reconstruction(src1, src2, image.img);
    return image;
}

Image fillHoles(const Args &src)
{
    if (src.size() != 1)
    {
        std::string exception = "Zla liczba argumentow";
        throw exception;
    }
    const Mat& src1 = src[0]->img;

    Mat mask = createMask(src1.rows, src1.cols, CV_8U);
    Mat img = src1.clone();
    bitwise_not(img, img);
    Image image;
    reconstruction(mask, img, image.img);
    bitwise_not(image.img, image.img);

    return image;
}

Image borderConnected(const Args &src)
{
    if (src.size() != 1)
    {
        std::string exception = "Zla liczba argumentow";
        throw exception;
    }
    const Mat& src1 = src[0]->img;

    Mat mask = createMask(src1.rows, src1.cols, CV_8U);
    Mat img = src1.clone();

    Image image;
    reconstruction(mask, img, image.img);

    return image;
}

Image borderDisconnected(const Args &src)
{
    if (src.size() != 1)
    {
        std::string exception = "Zla liczba argumentow";
        throw exception;
    }
    const Mat& src1 = src[0]->img;
    Image image = borderConnected(src);
    Args imgs;
    Image imageSrc1(src1);
    imgs.emplace_back(&imageSrc1);
    imgs.emplace_back(&image);

    return diff(imgs);
}
