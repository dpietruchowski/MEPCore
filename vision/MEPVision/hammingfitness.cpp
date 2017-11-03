#include "hammingfitness.h"

#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc/imgproc.hpp>

HammingFitness::HammingFitness(const Image &reference): Fitness(reference)
{

}

uint HammingFitness::measure(const Image &input, const Image &reference) const
{
    cv::Mat A, B, C;
    cv::threshold(input.img, A, 125, 255, 0);
    cv::threshold(reference.img, B, 125, 255, 0);
    cv::extractChannel(A, A, 0);
    cv::extractChannel(B, B, 0);
    cv::bitwise_not(A, A);
    cv::bitwise_not(B, B);
    cv::bitwise_xor(A, B, C);
    int measure = cv::countNonZero(C); //czarne pixele
    if (countNonZero(A)  < countNonZero(B))
        measure *= 10;

    return measure;
}
